import java.io.IOException;
import java.math.BigDecimal;
import java.sql.*;
import java.util.ArrayList;
import jakarta.servlet.*;            // use javax.servlet.* for Tomcat 9
import jakarta.servlet.annotation.WebServlet;
import jakarta.servlet.http.*;

@WebServlet("/expense")
public class ExpenseServlet extends HttpServlet {
    protected void doPost(HttpServletRequest req, HttpServletResponse resp)
            throws ServletException, IOException {

        // 1. Read form data
        String item = req.getParameter("item_name");
        String category = req.getParameter("category");
        BigDecimal amount = new BigDecimal(req.getParameter("amount"));
        Date date = Date.valueOf(req.getParameter("expense_date"));  // format yyyy-MM-dd
        String mode = req.getParameter("payment_mode");

        ArrayList<String[]> rows = new ArrayList<>();

        try {
            // 2. Connect to Postgres
            Class.forName("org.postgresql.Driver");
            Connection con = DriverManager.getConnection(
                "jdbc:postgresql://localhost:5432/web_tech_assignments", "postgres", );

            // 3. Insert (note the quotes around the table name)
            PreparedStatement ps = con.prepareStatement(
                "INSERT INTO \"2024CSB041\" (item_name, category, amount, expense_date, payment_mode) VALUES (?,?,?,?,?)");
            ps.setString(1, item);
            ps.setString(2, category);
            ps.setBigDecimal(3, amount);
            ps.setDate(4, date);
            ps.setString(5, mode);
            ps.executeUpdate();

            // 4. Fetch all rows
            ResultSet rs = con.createStatement().executeQuery(
                "SELECT * FROM \"2024CSB041\" ORDER BY expense_id");
            while (rs.next()) {
                rows.add(new String[]{
                    rs.getString("expense_id"), rs.getString("item_name"),
                    rs.getString("category"), rs.getString("amount"),
                    rs.getString("expense_date"), rs.getString("payment_mode")
                });
            }
            con.close();
        } catch (Exception e) {
            throw new ServletException(e);
        }

        // 5. Send rows to the JSP
        req.setAttribute("rows", rows);
        req.getRequestDispatcher("result.jsp").forward(req, resp);
    }
}
