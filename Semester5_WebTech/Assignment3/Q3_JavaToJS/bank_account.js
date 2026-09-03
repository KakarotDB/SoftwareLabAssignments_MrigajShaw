class BankAccount {
    constructor(accountNumber, holderName, initialBalance, accountType) {
        this.accountNumber = accountNumber;
        this.holderName = holderName;
        this.balance = parseFloat(initialBalance);
        this.accountType = accountType;
        
        this.transactions = [];
        this.addTransaction(`Account created with balance ₹${this.balance}`);
    }

    deposit(amount) {
        let amt = parseFloat(amount);
        if (amt > 0) {
            this.balance += amt;
            this.addTransaction(`Deposited ₹${amt}. New balance: ₹${this.balance}`);
            return true;
        }
        return false;
    }
    withdraw(amount) {
        let amt = parseFloat(amount);
        if (amt > 0 && this.balance >= amt) {
            this.balance -= amt;
            this.addTransaction(`Withdrew ₹${amt}. New balance: ₹${this.balance}`);
            return true;
        }
        return false;
    }
    getBalance() {
        return this.balance;
    }

    displayInfo() {
        return `Account: ${this.accountNumber} | Holder: ${this.holderName} | Type: ${this.accountType} | Balance: ₹${this.balance}`;
    }
    
    addTransaction(details) {
        let date = new Date().toLocaleString();
        this.transactions.push({ date: date, details: details });
    }
}

class SavingsAccount extends BankAccount {
    constructor(accountNumber, holderName, initialBalance, interestRate) {
        super(accountNumber, holderName, initialBalance, "Savings");
        this.interestRate = parseFloat(interestRate);
    }

    getInterest() {
        return this.balance * (this.interestRate / 100);
    }

    addInterest() {
        let interest = this.getInterest();
        this.deposit(interest);
        this.addTransaction(`Interest added: ₹${interest.toFixed(2)} at ${this.interestRate}%`);
    }
}

class CurrentAccount extends BankAccount {
    constructor(accountNumber, holderName, initialBalance, overdraftLimit) {
        super(accountNumber, holderName, initialBalance, "Current");
        this.overdraftLimit = parseFloat(overdraftLimit);
    }

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

let currentBankAcc = null;

function createAccount() {
    const name = document.getElementById("holderName").value;
    const accNum = document.getElementById("accNum").value;
    const type = document.getElementById("accType").value;
    const initBal = document.getElementById("initBal").value;

    if (!name || !accNum || !initBal) {
        alert("Please fill all fields"); // Java equivalent: System.out.println("Error");
        return;
    }

    if (type === "Savings") {
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
    
    const tbody = document.getElementById("transactions-body");
    tbody.innerHTML = '';
    
    currentBankAcc.transactions.forEach(t => {
        let row = `<tr>
            <td>${t.date}</td>
            <td>${t.details}</td>
        </tr>`;
        tbody.innerHTML += row;
    });
}
