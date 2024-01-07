#include "Account.h"

Account::Account(int new_id, double new_balance, std::string new_name)
{
    id = new_id;
    balance = new_balance;
    name = new_name;
}

int Account::getId() const {return id; }

std::string Account::getName() const {return name; }

double Account::getBalance() const { return balance; }

void Account::deposit(double amount) { balance += amount; }

bool Account::withdraw(double amount) {
    if (amount > balance) {
        return false;
    }
    balance -= amount;
    return true;
}