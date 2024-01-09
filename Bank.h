#ifndef BANK_H
#define BANK_H

#include <vector>
#include <iostream>
#include <iomanip>
#include <algorithm>
#include "Account.h"

// The Bank class represents a bank with functionalities to manage accounts.
class Bank {
public:
    /**
     * Adds a new account to the bank.
     * @param account A constant reference to an Account object to be added.
     * @return A boolean indicating if the account was successfully added.
    */
    bool addAccount(const Account &account);

    // Displays all accounts in the bank.
    void displayAccounts();

    /**
     * Finds an account by its ID
     * @param id An integer representing the account's unique ID.
     * @returns A pointer to the Account object, or nullptr if not found
    */
    Account* findAccount(int id);

    /**
     * Displays accounts filtered by name
     * @param A constant reference to a string representing the account holder's name.
    */    
    void displayAccountsByName(const std::string &name);

    /**
     * Displays accounts filtered by balance greater than a specified amount
     * @param A constant reference to a double representing the minimum balance.     
    */    
    void displayAccountsByBalance(const double &balance);

    /**
     * Deletes an account by its ID.
     * @param id An integer representing the account's unique ID.
     * @return A boolean indicating if the account was successfully removed.
    */
    bool deleteAccount(int id);

    // Sorts accounts by account holder's name. Modifies the original vector
    void sortAccountsByName();

    // Sorts accounts by balance. Modifies the original vector
    void sortAccountsByBalance();

    // Sorts accounts by account ID. Modifies the original vector
    void sortAccountsById();

private:
    /**
     * Helper function to display a formatted list of accounts
     * @param accounts A constant reference to a vector of Account objects
    */
    void displayAccountsFormatted(const std::vector<Account> &accounts);

    std::vector<Account> accounts; // Container for storing bank accounts
};

#endif // BANK_H
