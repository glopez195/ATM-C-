#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <string>

// The Account class represents a bank account with basic functionalities.
class Account {
public:
    /**
     * Constructor to create a new Account object
     * @param new_id An integer representing the unique ID of the account.
     * @param new_balance A double representing the initial balance of the account.
     * @param new_name A string representing the name of the account holder
    */
    Account(int new_id, double new_balance, std::string new_name);

    /**
     * Retrieves the account's ID.
     * @return An integer representing the account;s unique ID.
    */
    int getId() const;

    /**
     * Retrieves the name of the account holder
     * @return A string representing the name of the account holder
    */
    std::string getName() const;

    /**
     * Retrieves the current balance of the account
     * @return A douuble representing the current balance of the current account
    */
    double getBalance() const;

    /**
     * Deposits the specified amount into the account
     * @param A double representing the amouunt to be deposited
    */
    void deposit(double amount);

    /**
     * Attempts to withdraw the specified amount from the account.
     * If the amount if greater than the current balance the withdrawal fails.
     * @param A double representing the amount to be withdrawn.
     * @return true if the withdrawak is successful, false otherwise.
    */
    bool withdraw(double amount);

private:
    int id;               // Unique identifier for the account
    double balance;       // Current balance of the account
    std::string name;     // Name of the account holder
};

#endif // ACCOUNT_H
