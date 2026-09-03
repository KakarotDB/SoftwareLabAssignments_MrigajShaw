/**
 * Bank Account Management System - JavaScript Conversion
 * Written for Viva explanation
 */

// JS: class BankAccount
// Java equivalent: public class BankAccount { ... }
class BankAccount {
    // JS Constructor
    // Java equivalent: public BankAccount(String accountNumber, String holderName, double initialBalance, String accountType)
    constructor(accountNumber, holderName, initialBalance, accountType) {
        // JS: this.field = value; (Dynamic typing, no prior declaration needed)
        // Java: protected String accountNumber; this.accountNumber = accountNumber;
        this.accountNumber = accountNumber;
        this.holderName = holderName;
        this.balance = parseFloat(initialBalance);
        this.accountType = accountType;
        
        // Extra JS feature: Array to keep track of transactions
        // Java equivalent: ArrayList<String> transactions = new ArrayList<>();
        this.transactions = [];
        this.addTransaction(`Account created with balance ₹${this.balance}`);
    }

    // JS Method
    // Java equivalent: public void deposit(double amount)
    deposit(amount) {
        let amt = parseFloat(amount);
        if (amt > 0) {
            this.balance += amt;
            this.addTransaction(`Deposited ₹${amt}. New balance: ₹${this.balance}`);
            return true;
        }
        return false;
    }

    // JS Method
    // Java equivalent: public boolean withdraw(double amount)
    withdraw(amount) {
        let amt = parseFloat(amount);
        if (amt > 0 && this.balance >= amt) {
            this.balance -= amt;
            this.addTransaction(`Withdrew ₹${amt}. New balance: ₹${this.balance}`);
            return true;
        }
        return false;
    }

    // JS Method
    // Java equivalent: public double getBalance()
    getBalance() {
        return this.balance;
    }

    // JS Method
    // Java equivalent: public void displayInfo()
    displayInfo() {
        return `Account: ${this.accountNumber} | Holder: ${this.holderName} | Type: ${this.accountType} | Balance: ₹${this.balance}`;
    }
    
    // JS custom method
    addTransaction(details) {
        let date = new Date().toLocaleString();
        this.transactions.push({ date: date, details: details });
    }
}

// JS Inheritance: class SavingsAccount extends BankAccount
// Java equivalent: class SavingsAccount extends BankAccount
class SavingsAccount extends BankAccount {
    // JS Constructor
    // Java equivalent: public SavingsAccount(String accountNumber, String holderName, double initialBalance, double interestRate)
    constructor(accountNumber, holderName, initialBalance, interestRate) {
        // JS: super() call must be before this.
        // Java: super(accountNumber, holderName, initialBalance, "Savings");
        super(accountNumber, holderName, initialBalance, "Savings");
        this.interestRate = parseFloat(interestRate);
    }

    // JS Method
    // Java equivalent: public double getInterest()
    getInterest() {
        return this.balance * (this.interestRate / 100);
    }

    // JS Method
    // Java equivalent: public void addInterest()
    addInterest() {
        let interest = this.getInterest();
        this.deposit(interest);
        this.addTransaction(`Interest added: ₹${interest.toFixed(2)} at ${this.interestRate}%`);
    }
}

// JS Inheritance: class CurrentAccount extends BankAccount
// Java equivalent: class CurrentAccount extends BankAccount
class CurrentAccount extends BankAccount {
    // JS Constructor
    // Java equivalent: public CurrentAccount(String accountNumber, String holderName, double initialBalance, double overdraftLimit)
    constructor(accountNumber, holderName, initialBalance, overdraftLimit) {
        super(accountNumber, holderName, initialBalance, "Current");
        this.overdraftLimit = parseFloat(overdraftLimit);
    }

    // JS Overriding Method
    // Java equivalent: @Override public boolean withdraw(double amount)
    withdraw(amount) {
        let amt = parseFloat(amount);
        if (amt > 0 && (this.balance + this.overdraftLimit) >= amt) {
            this.balance -= amt;
            this.addTransaction(`Withdrew ₹${amt} (Current Account). New balance: ₹${this.balance}`);
            return true;
        }
        return false;
    }
}

// Global variable to hold the current account
// Java equivalent: BankAccount currentAccount = null;
let currentBankAcc = null;

// UI Interaction Logic

function createAccount() {
    // JS DOM interaction
    // Java equivalent: Scanner.nextLine()
    const name = document.getElementById("holderName").value;
    const accNum = document.getElementById("accNum").value;
    const type = document.getElementById("accType").value;
    const initBal = document.getElementById("initBal").value;

    if (!name || !accNum || !initBal) {
        alert("Please fill all fields"); // Java equivalent: System.out.println("Error");
        return;
    }

    if (type === "Savings") {
        // Java equivalent: currentBankAcc = new SavingsAccount(...);
        currentBankAcc = new SavingsAccount(accNum, name, initBal, 5.0); // 5% interest
    } else {
        currentBankAcc = new CurrentAccount(accNum, name, initBal, 1000.0); // 1000 overdraft
    }

    document.getElementById("create-section").style.display = "none";
    document.getElementById("action-section").style.display = "block";
    
    updateUI();
}

function depositAmount() {
    const amt = document.getElementById("amount").value;
    if (amt && currentBankAcc) {
        if(currentBankAcc.deposit(amt)) {
            document.getElementById("amount").value = '';
            updateUI();
        } else {
            alert("Invalid deposit amount.");
        }
    }
}

function withdrawAmount() {
    const amt = document.getElementById("amount").value;
    if (amt && currentBankAcc) {
        if (currentBankAcc.withdraw(amt)) {
            document.getElementById("amount").value = '';
            updateUI();
        } else {
            alert("Insufficient balance or limit exceeded.");
        }
    }
}

function updateUI() {
    if (!currentBankAcc) return;
    
    document.getElementById("acc-info-name").innerText = currentBankAcc.holderName;
    document.getElementById("acc-info-num").innerText = currentBankAcc.accountNumber;
    document.getElementById("acc-info-type").innerText = currentBankAcc.accountType;
    document.getElementById("acc-info-bal").innerText = `₹${currentBankAcc.balance.toFixed(2)}`;
    
    // Update transactions table
    const tbody = document.getElementById("transactions-body");
    tbody.innerHTML = '';
    
    // JS Array iteration
    // Java equivalent: for(String t : transactions) { ... }
    currentBankAcc.transactions.forEach(t => {
        let row = `<tr>
            <td>${t.date}</td>
            <td>${t.details}</td>
        </tr>`;
        tbody.innerHTML += row;
    });
}
