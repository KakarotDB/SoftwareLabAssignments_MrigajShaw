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

	while(getline(inFile, token, ',')) {
		r = stoi(token);
		
		getline(inFile, token, ',');
		s = stoi(token);

		getline(inFile, token, ',');
		p = token;

		getline(inFile, token);
		u = stoi(token);

		if(r >= 1 && r <= 4 && s >= 1 && s <= 6) {
			int productIndex = p[0] - 'A';

			float price = ProductPrices[productIndex][1];
			totals[r-1][s-1] += price * u;
		}
	
	}

    inFile.close();

    outFile << "ABC Company\n\n";

    for (int i = 0; i < 4; i++) {
        outFile << "Region " << (i + 1) << "\n";

        float regionTotal = 0.00;

        for (int j = 0; j < 6; j++) {
            outFile << "Salesman " << (j + 1) << " : Rs. " << fixed
                    << setprecision(2) << totals[i][j] << "/-\n";
            regionTotal += totals[i][j];
        }

        outFile << "\n";

        outFile << "Total sale at region " << (i + 1) << " : Rs " << regionTotal
                << "/-\n\n";
    }

    outFile.close();

    cout << "Report generated succesfully!\n";

    return 0;
}
