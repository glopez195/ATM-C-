#ifndef BANK_H
#define BANK_H

#include <vector>
#include <iostream>
#include <iomanip>
#include <algorithm>
#include "Account.h"


class Bank {
public:
    bool addAccount(const Account &);

    void displayAccounts();

    Account* findAccount(int);

    bool deleteAccount(int);

private:
    std::vector<Account> accounts;
};

#endif