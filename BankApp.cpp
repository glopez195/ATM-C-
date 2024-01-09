#include <iostream>
#include <vector>
#include <algorithm>
#include "Account.cpp"
#include "Bank.cpp"
#include "Utility.cpp"

// Constants defining the expected length of account numbers and PINs.
const int ACCOUNT_LENGTH = 7;
const int PIN_LENGTH = 4;

// Utility object for various helper functions like input validation.
Utility utility;

/**
 * Function: clientMenu
 * Purpose: Handles the menu and actions for a bank client.
 * Parameters:
 *   - Bank &bank: Reference to the Bank object, facilitating account operations.
 * 
 * Description: 
 *   This function provides a menu for the client to perform various operations 
 *   such as checking balance, depositing money, and withdrawing money. It also 
 *   handles PIN verification and account selection for the client.
 */
void clientMenu(Bank &bank) {
    // Client PIN authentication
    std::string pin;
    std::cout << "Enter your 4 digit pin: ";
    std::cin >> pin;
    if(!utility.verifyNumber(pin, PIN_LENGTH)) return; // Validates the PIN length.

    // Dummy account for fast testing purposes. In a real scenario, this would be replaced
    // by an account lookup based on the authenticated client.
    Account* account = bank.findAccount(1111111);
    if (account == nullptr) {
        std::cout << "\033[31mAccount not found.\n\033[0m";
        return; // Exit if account is not found.
    }

    // Client operations menu
    int choice;
    std::cout << "1. Check Balance\n2. Deposit Money\n3. Withdraw Money\nEnter choice: ";
    choice = utility.getNumber(); // Utility function to get a valid number.
    system("clear"); // Clears the console for clean output.

    double amount; // Variable to store the amount for transactions.
    switch (choice) {
        case 1:
            // Display the current account balance.
            std::cout << "Your balance is: \033[32m$" << account->getBalance() << "\n\033[0m";
            break;
        case 2:
            // Handle deposit operation.
            std::cout << "Enter deposit amount: ";
            std::cin >> amount;
            account->deposit(amount); // Deposit the specified amount.
            break;
        case 3:
            // Handle withdrawal operation.
            std::cout << "Enter withdrawal amount: ";
            std::cin >> amount;
            if (!account->withdraw(amount)) {
                std::cout << "\033[31mInsufficient funds.\n\033[0m";
            }
            break;
        default:
            // Handle invalid choice.
            std::cout << "\033[31mInvalid choice.\n\033[0m";
    }
}


/** 
 * This function presents a menu to the banker, allowing them to perform
 * various administrative operations such as managing accounts, searching
 * by name or balance, and sorting accounts.
 * @param bank Reference to the Bank object for managing accounts. 
 */
void bankerMenu(Bank &bank) {
    int choice;
    std::cout << "1. Display all customers\n2. Delete an account\n3. Add a new account\n"
              << "4. Search by name\n5. Search by balance greater than\n"
              << "6. Sort accounts by name\n7. Sort accounts by balance\n"
              << "8. Sort accounts by ID\nEnter choice: ";
    choice = utility.getNumber(); // Gets the choice of the banker

    // Variables to hold account details
    std::string accountId, searchName, name;
    double balance;

    switch (choice) {
        case 1:
            // Display all bank accounts
            bank.displayAccounts();
            break;
        case 2:
            // Delete an account by its ID
            std::cout << "Enter account ID to delete: ";
            std::cin >> accountId;
            if(utility.verifyNumber(accountId, ACCOUNT_LENGTH)) {
                if(bank.deleteAccount(std::stoi(accountId)))
                    std::cout << "\033[32mAccount successfully deleted.\n\033[0m";
                else
                    std::cout << "\033[31mAccount not found.\n\033[0m";
            }
            break;
        case 3:
            // Add a new account
            std::cout << "Enter new account ID (7 digits): ";
            std::cin >> accountId;
            if(utility.verifyNumber(accountId, ACCOUNT_LENGTH)) {
                std::cout << "Enter initial Balance: ";
                balance = utility.getAmount();
                if(balance >= 0) {
                    std::cout << "Enter the Name of the Client: ";
                    utility.clearCinBuffer();
                    std::getline(std::cin, name);
                    bank.addAccount(Account(std::stoi(accountId), balance, name));
                } else {
                    std::cout << "\033[31mInvalid amount.\n\033[0m";
                }
            }
            break;
        case 4:
            // Search accounts by name
            std::cout << "Enter name to search: ";
            utility.clearCinBuffer();
            std::getline(std::cin, searchName);
            if (!searchName.empty()) {
                bank.displayAccountsByName(searchName);
            } else {
                std::cout << "\033[31mName cannot be empty.\n\033[0m";
            }
            break;
        case 5:
            // Search accounts by a minimum balance
            std::cout << "Enter minimum balance: ";
            balance = utility.getAmount();
            if(balance >= 0) {
                bank.displayAccountsByBalance(balance);
            } else {
                std::cout << "\033[31mInvalid amount.\n\033[0m";
            }
            break;
        case 6:
            // Sort and display accounts by name
            bank.sortAccountsByName();
            bank.displayAccounts();
            break;
        case 7:
            // Sort and display accounts by balance
            bank.sortAccountsByBalance();
            bank.displayAccounts();
            break;
        case 8:
            // Sort and display accounts by ID
            bank.sortAccountsById();
            bank.displayAccounts();
            break;
        default:
            // Handle invalid choice
            std::cout << "\033[31mInvalid choice.\n\033[0m";
    }
}

/**
 * Entry point for the Dummy Bank application.
 *
 * This function sets up a simple banking application with predefined accounts.
 * It allows users to interact with the bank system as either a client or a banker.
 */
int main() {
    // Instantiate a bank object to manage various accounts.
    Bank bank;

    // Add sample accounts to the bank for demonstration purposes.
    bank.addAccount(Account(1111111, 1040.45, "Alex Johnson")); // Account 1
    bank.addAccount(Account(3456547, 100000, "Samantha Green")); // Account 2
    bank.addAccount(Account(6455742, 100, "Jordan Smith")); // Account 3
    bank.addAccount(Account(9823454, 0.04, "Taylor Davis")); // Account 4
    bank.addAccount(Account(5423244, 500, "Morgan Lee")); // Account 5
    bank.addAccount(Account(9823413, 5050, "Casey Brown")); // Account 6

    // Variable to store user's role choice.
    int userType;

    // Clear the console and display the welcome message.
    system("clear");
    std::cout << "\033[34m\t\tWelcome to Dummy Bank! \033[0m\n"
              << "Which role would you like to sign in as:\n1. Client \n2. Banker\n\n";
    std::cin >> userType; // Read user's choice.
    system("clear"); // Clear the console for clean output.

    // Main interaction loop based on user role.
    switch (userType) {
        case 1: // Client Role
            while (true) {
                clientMenu(bank); // Execute client-specific actions.
                std::cout << "Would you like to continue? Y or N \n";
                char selection;
                std::cin >> selection;
                if (selection != 'y' && selection != 'Y') break; // Exit loop if no longer continue.
                system("clear"); // Clear the console.
            }
            break;
        case 2: // Banker Role
            while (true) {
                bankerMenu(bank); // Execute banker-specific actions.
                std::cout << "Would you like to continue? Y or N\n";
                char selection;
                std::cin >> selection;
                if (selection != 'y' && selection != 'Y') break; // Exit loop if no longer continue.
                system("clear"); // Clear the console.
            }
            break;
        default: // Invalid Choice
            std::cout << "\033[31m Invalid choice.\n \033[0m"; // Display error for invalid choice.
    }

    // End of the application.
    std::cout << "\033[34mGOODBYE...\n\033[0m";
    return 0; // Return success status.
}
