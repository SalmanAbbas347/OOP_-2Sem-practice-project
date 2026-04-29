#ifndef BANKACCOUNT_H
#define BANKACCOUNT_H

#include <iostream>
#include <string>
using namespace std;

class BankAccount {
private:
    string name;
    int accountNumber;
    double balance;

public:
    static int totalAccounts;
    static double minBalance;

    BankAccount& setName(string n);
    BankAccount& setAccountNumber(int num);
    BankAccount& setBalance(double b);
    string getName();
    int getAccountNumber();
    double getBalance();

    void display();
    static void showTotalAccounts();
};

#endif