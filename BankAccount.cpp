#include "BankAccount.h"

int BankAccount::totalAccounts = 0;
double BankAccount::minBalance = 1000;
BankAccount& BankAccount::setName(string n) {
    name = n;
    return *this;
}

BankAccount& BankAccount::setAccountNumber(int num) {
    accountNumber = num;
    return *this;
}

BankAccount& BankAccount::setBalance(double b) {
    balance = b;
    totalAccounts++;
    return *this;
}
string BankAccount::getName() {
    return name;
}
int BankAccount::getAccountNumber() {
    return accountNumber;
}
double BankAccount::getBalance() {
    return balance;
}
void BankAccount::display() {
    cout << "Name: " << name
        << "  Account No: " << accountNumber
        << "  Balance: " << balance << endl;
}
void BankAccount::showTotalAccounts() {
    cout << "Total Accounts: " << totalAccounts << endl;
}