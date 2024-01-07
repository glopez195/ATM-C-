#include <iostream>
#include <vector>
#include <algorithm>
#include "Account.cpp"
#include "Bank.cpp"
#include "Utility.cpp"

/*
    32 green  -  31 red  -  34 blue
    \033[32m  \033[0m
*/
const int ACCOUNT_LENGTH = 7;
const int PIN_LENGTH = 4;


Utility utility;

void clientMenu(Bank &bank) {
    std::string accountId;
    std::cout << "Enter your 4 digit pin: ";
    std::cin >> accountId;

    if(!utility.verifyNumber(accountId, PIN_LENGTH)) return;

    // Dummy account created in Main | assigned to user for fast testing
    Account* account = bank.findAccount(1111111);
    if (account == nullptr) {
        std::cout << "Account not found.\n";
        return;
    }

    int choice;
    std::cout << "1. Check Balance\n2. Deposit Money\n3. Withdraw Money\nEnter choice: ";
    choice = utility.getNumber();
    system("clear");
    double amount;
    switch (choice) {
        case 1:
            std::cout << "Your balance is: \033[32m " << account->getBalance() << "\033[0m\n"<< std::endl;
            break;
        case 2:
            std::cout << "Enter deposit amount: ";
            std::cin >> amount;
            account->deposit(amount);
            break;
        case 3:
            std::cout << "Enter withdrawal amount: ";
            std::cin >> amount;
            if (!account->withdraw(amount)) {
                std::cout << "\033[31mInsufficient funds.\033[0m\n\n";
            }
            break;
        default:
            std::cout << "\033[31mInvalid choice.\033[0m\n\n";
    }
}

void bankerMenu(Bank &bank) {
    int choice;
    std::cout << "1. Display all customers\n2. Delete an account\n3. Add a new account\nEnter choice: ";
    choice = utility.getNumber();

    std::string accountId;
    double balance;
    std::string name;
    switch (choice) {
        case 1:
            bank.displayAccounts();
            break;
        case 2:
            std::cout << "Enter account ID to delete: ";
            std::cin >> accountId;
            if(utility.verifyNumber(accountId, ACCOUNT_LENGTH))
            {
                if(bank.deleteAccount(std::stoi(accountId))) std::cout << "\033[32m Account succesfully deleted.\n \033[0m";
                else std::cout << "\033[31m Account not found.\n \033[0m";                
            }
            break;
        case 3:
            std::cout << "Enter new account ID (7 digits): ";
            std::cin >> accountId;
            if(!utility.verifyNumber(accountId, ACCOUNT_LENGTH)){
                break;
            }

            std::cout << "Enter initial Balance: ";
            if((balance = utility.getAmount()) < 0)
                std::cout << "\033[31m Invalid amount.\n\033[0m";
                break;
            
            std::cout << "Enter the Name of the Client: ";
            utility.clearCinBuffer();
            std::getline(std::cin, name);
            bank.addAccount(Account(std::stoi(accountId), balance, name));
            break;
        default:
            std::cout << "\033[31m Invalid choice.\n \033[0m";
    }
}

int main() {
    Bank bank;
    bank.addAccount(Account(1111111, 1040.45, "William Smith"));  // Sample account

    int userType;
    system("clear");
    std::cout << "\033[34m\t\tWelcome to Dummy Bank! \033[0m \nWhich role would like to sign in as:\n1. Client \n2. Banker\n\n";
    std::cin >> userType;
    system("clear");

    switch (userType) {
        case 1:
            while(true){
                clientMenu(bank);
                std::cout << "Would you like to continue? Y or N \n";
                char selection;
                std::cin >> selection;
                if(selection == 'y' || selection == 'Y')                
                    system("clear");                
                else
                    break;                
            }
                system("clear");
                std::cout<<"GOODBYE...\n";
            break;
        case 2:
            while(true){
                bankerMenu(bank);
                std::cout << "Would you like to continue? Y or N\n";
                char selection;
                std::cin >> selection;
                if(selection == 'y' || selection == 'Y')                
                    system("clear");                
                else
                    break;                
            }
                system("clear");
                std::cout<<"GOODBYE...\n";
            break;
        default:
            std::cout << "\033[31m Invalid choice.\n \033[0m";
    }

    return 0;
}

