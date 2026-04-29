#include "BankAccount.h"

double averageBalance(BankAccount* acc, int size) {
    double sum = 0;
    for (int i = 0;i < size;i++) {
        sum += acc[i].getBalance();
    }
    return sum / size;
}

void lowBalance(BankAccount* acc, int size) {
    cout << "\nLow Balance Accounts:\n";
    for (int i = 0;i < size;i++) {
        if (acc[i].getBalance() < BankAccount::minBalance) {
            acc[i].display();
        }
    }
}

void highestBalance(BankAccount* acc, int size) {
    int index = 0;

    for (int i = 1;i < size;i++) {
        if (acc[i].getBalance() > acc[index].getBalance()) {
            index = i;
        }
    }

    cout << "\nHighest Balance Account:\n";
    acc[index].display();
}

int main() {
    const int SIZE = 3;
    BankAccount accounts[SIZE];

    accounts[0].setName("Ali").setAccountNumber(101).setBalance(5000);
    accounts[1].setName("Sara").setAccountNumber(102).setBalance(800);
    accounts[2].setName("Ahmed").setAccountNumber(103).setBalance(12000);

    cout << "All Accounts\n";
    for (int i = 0;i < SIZE;i++) {
        accounts[i].display();
    }
    BankAccount::showTotalAccounts();

    cout << "\nAverage Balance: " << averageBalance(accounts, SIZE) << endl;
    lowBalance(accounts, SIZE);
    highestBalance(accounts, SIZE);

    return 0;
}