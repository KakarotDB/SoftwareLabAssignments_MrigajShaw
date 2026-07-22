#include <ctime> // Required for generating the timestamp
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>

using namespace std;

int main() {
    float totals[4][6] = {0}; // 4 regions, each with six salesmen
    ifstream inFile("./sales_data.csv");
    ofstream outFile("report.txt");

    if (!inFile.is_open()) {
        cerr << "Error : Couldn't open data file" << endl;
        return -1;
    }

    string header;
    getline(inFile, header);

    float ProductPrices[8][2] = {
        {0, 350.00}, {1, 200.00}, {2, 178.20}, {3, 199.99},
        {4, 457.24}, {5, 599.00}, {6, 999.99}, {7, 800.00},
    };

    int r, s, u;
    string p;
    string token;

    while (getline(inFile, token, ',')) {
        r = stoi(token);

        getline(inFile, token, ',');
        s = stoi(token);

        getline(inFile, token, ',');
        p = token;

        getline(inFile, token);
        u = stoi(token);

        if (r >= 1 && r <= 4 && s >= 1 && s <= 6) {
            // find_first_not_of(" ") safely handles spaces if your CSV looks
            // like "1, 1, A, 5"
            char productChar = p[p.find_first_not_of(" ")];
            int productIndex = productChar - 'A';

            float price = ProductPrices[productIndex][1];
            totals[r - 1][s - 1] += price * u;
        }
    }

    inFile.close();

    time_t now = time(nullptr);
    tm *localTime = localtime(&now);

    outFile << "============================================\n";
    outFile << "               ABC COMPANY                  \n";
    outFile << "          MONTHLY SALES REPORT              \n";
    outFile << "============================================\n";
    outFile << "Generated on: " << put_time(localTime, "%B %d, %Y at %I:%M %p")
            << "\n\n";

    for (int i = 0; i < 4; i++) {
        outFile << "|                REGION " << (i + 1)
                << "                  |\n";
        outFile << "+------------------------------------------+\n";
        outFile << left << setw(20) << "  Salesman" << " | " << right
                << setw(18) << "Sales Amount  " << "\n";
        outFile << "--------------------------------------------\n";

        float regionTotal = 0.00;
        for (int j = 0; j < 6; j++) {
            outFile << "  Salesman " << left << setw(9) << (j + 1) << "| "
                    << "Rs. " << right << setw(10) << fixed << setprecision(2)
                    << totals[i][j] << "/-\n";
            regionTotal += totals[i][j];
        }
        outFile << "--------------------------------------------\n";
        outFile << left << setw(21) << "  TOTAL SALES" << "| "
                << "Rs. " << right << setw(10) << regionTotal << "/-\n";
        outFile << "+------------------------------------------+\n";
        outFile << right << setw(29) << "- Page " << (i + 1) << " -\n\n\n";
    }

    outFile.close();

    cout << "Report generated successfully!\n";

    return 0;
}
