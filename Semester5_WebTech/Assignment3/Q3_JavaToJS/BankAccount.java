// Java Bank Account Management System
import java.util.Scanner;

// Base class BankAccount
public class BankAccount {
    protected String accountNumber;
    protected String holderName;
    protected double balance;
    protected String accountType;

    public BankAccount(String accountNumber, String holderName, double initialBalance, String accountType) {
        this.accountNumber = accountNumber;
        this.holderName = holderName;
        this.balance = initialBalance;
        this.accountType = accountType;
    }

    public void deposit(double amount) {
        if (amount > 0) {
            balance += amount;
            System.out.println("Deposited: " + amount + ". New Balance: " + balance);
        } else {
            System.out.println("Invalid deposit amount.");
        }
    }

    public boolean withdraw(double amount) {
        if (amount > 0 && balance >= amount) {
            balance -= amount;
            System.out.println("Withdrew: " + amount + ". New Balance: " + balance);
            return true;
        } else {
            System.out.println("Insufficient balance or invalid amount.");
            return false;
        }
    }

    public double getBalance() {
        return balance;
    }

    public void displayInfo() {
        System.out.println("Account: " + accountNumber + " | Holder: " + holderName + " | Type: " + accountType + " | Balance: " + balance);
    }
}

// Subclass SavingsAccount
class SavingsAccount extends BankAccount {
    private double interestRate;

    public SavingsAccount(String accountNumber, String holderName, double initialBalance, double interestRate) {
        super(accountNumber, holderName, initialBalance, "Savings");
        this.interestRate = interestRate;
    }

    public double getInterest() {
        return balance * (interestRate / 100);
    }

    public void addInterest() {
        double interest = getInterest();
        deposit(interest);
        System.out.println("Interest added: " + interest);
    }
}

// Subclass CurrentAccount
class CurrentAccount extends BankAccount {
    private double overdraftLimit;

    public CurrentAccount(String accountNumber, String holderName, double initialBalance, double overdraftLimit) {
        super(accountNumber, holderName, initialBalance, "Current");
        this.overdraftLimit = overdraftLimit;
    }

    @Override
    public boolean withdraw(double amount) {
        if (amount > 0 && (balance + overdraftLimit) >= amount) {
            balance -= amount;
            System.out.println("Withdrew: " + amount + " (Current Account). New Balance: " + balance);
            return true;
        } else {
            System.out.println("Overdraft limit exceeded or invalid amount.");
            return false;
        }
    }
}

// Main class to run the program
class Main {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        System.out.println("Bank Account Management System");
        
        SavingsAccount sa = new SavingsAccount("SA001", "Mrigaj Shaw", 1000.0, 5.0);
        sa.displayInfo();
        sa.deposit(500);
        sa.withdraw(200);
        sa.addInterest();
        sa.displayInfo();
        
        System.out.println("---------");
        
        CurrentAccount ca = new CurrentAccount("CA001", "Mrigaj Shaw", 2000.0, 1000.0);
        ca.displayInfo();
        ca.withdraw(2500); // Should succeed due to overdraft
        ca.withdraw(1000); // Should fail
        ca.displayInfo();
        
        scanner.close();
    }
}
