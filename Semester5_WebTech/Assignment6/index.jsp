<html>
<body>
  <h2>Add Expense</h2>
  <form action="expense" method="post">
    Item: <input type="text" name="item_name" required><br><br>
    Category: <input type="text" name="category" required><br><br>
    Amount: <input type="number" step="0.01" name="amount" required><br><br>
    Date: <input type="date" name="expense_date" required><br><br>
    Payment Mode: <input type="text" name="payment_mode" required><br><br>
    <input type="submit" value="Add Expense">
  </form>
</body>
</html>
