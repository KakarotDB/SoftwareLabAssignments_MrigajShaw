#include <iostream>

namespace BankingSystem {
class BankManager;

class BankAccount {
    std::string m_name;
    int m_accountNumber;
    double m_currentBalance;

  public:
    BankAccount(std::string name, int accountNumber, double currentBalance,
                BankManager &manager);
    friend class BankManager;
};

class BankManager {
    static int countAccounts;
    static int sufficientAmount;

  public:
    void display(BankAccount account) const {
        std::cout << "Name : " << account.m_name << std::endl
                  << "Account Number : " << account.m_accountNumber << std::endl
                  << "Current Balance : " << account.m_currentBalance
                  << std::endl;
    }
    void displayCountAccounts() const {
        std::cout << "Count of accounts = " << countAccounts << std::endl;
    }
    void addAccount() { countAccounts++; }

    bool hasSufficientBalance(BankAccount &account) {
        return account.m_currentBalance >= sufficientAmount;
    }
};
int BankManager::countAccounts = 0;
int BankManager::sufficientAmount = 10000;

BankAccount::BankAccount(std::string name, int accountNumber,
                         double currentBalance, BankManager &manager)
    : m_name(name), m_accountNumber(accountNumber) {
    manager.addAccount();
    if (currentBalance <= 0)
        m_currentBalance = 0;
    else
        m_currentBalance = currentBalance;
}

} // namespace BankingSystem

int main() {
    using namespace std;
    using namespace BankingSystem;

    BankManager manager;
    BankAccount b("Mrigaj", 1, 1000, manager);
    manager.display(b);
    manager.displayCountAccounts();

    BankAccount b1("Rahul", 2, 2000, manager);
    manager.display(b1);
    manager.displayCountAccounts();
    cout << "Does bank account 1 have sufficient balance ?" << endl;
    cout << boolalpha << manager.hasSufficientBalance(b) << endl;
    return 0;
}
