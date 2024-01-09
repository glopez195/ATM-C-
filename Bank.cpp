#include "Bank.h"

const char FILLER = '-';
const short int COL_WIDTH = 20;

bool Bank::addAccount(const Account &account) {
    if(findAccount(account.getId()) != nullptr) return false;
    accounts.push_back(account);
    return true;
}

void Bank::displayAccounts() {
    displayAccountsFormatted(accounts);
}

void Bank::displayAccountsFormatted(const std::vector<Account>& accounts) {
    system("clear"); // Clear the console.    
    // Display the header
    // ... (header formatting code) ...
    std::cout << "\033[34m" << std::setfill('*') << std::setw(COL_WIDTH *3) << '*' << "\033[0m" << std::endl 
        << std::left << std::setfill(' ') << std::setw(COL_WIDTH) << "Account#" << std::setw(COL_WIDTH) 
        << "Name" << std::setw(COL_WIDTH) << std::right << "Balance" << std::endl 
        << "\033[34m" << std::setfill(FILLER) << std::setw(COL_WIDTH *3) << FILLER << "\033[0m" << std::endl;
    // Iterate over the accounts and display each one.
    for (const auto &acc : accounts) {
        // ... (account display code) ...
        std::cout << std::fixed << std::setprecision(2) << std::left << std::setfill(' ') << std::setw(COL_WIDTH) << acc.getId() << std::setw(COL_WIDTH) 
        << acc.getName() << std::setw(COL_WIDTH) << std::right << acc.getBalance() << std::endl << "\033[34m" << std::setfill(FILLER) << std::setw(COL_WIDTH *3) << FILLER << "\033[0m" << std::endl;        
    }
    std::cout << std::endl; // End of the account list.
}

Account* Bank::findAccount(int id) {
    for (auto &acc : accounts) {
        if (acc.getId() == id) {
            return &acc;
        }
    }
    return nullptr;
}

bool Bank::deleteAccount(int id) {
    if(!findAccount(id)) return false;
    accounts.erase(std::remove_if(accounts.begin(), accounts.end(),
                                    [id](const Account& acc) { return acc.getId() == id; }),
                    accounts.end());
    return true;
}

void Bank::displayAccountsByName(const std::string& name) {    
    std::vector<Account> filteredAccounts;
    for (const auto &acc : accounts) {
        if (acc.getName().find(name) != std::string::npos) {
            filteredAccounts.push_back(acc);
        }
    }
    displayAccountsFormatted(filteredAccounts);
}

void Bank::displayAccountsByBalance(const double& minBalance) {
    std::vector<Account> filteredAccounts;
    for (const auto &acc : accounts) {
        if (acc.getBalance() > minBalance) {
            filteredAccounts.push_back(acc);
        }
    }
    displayAccountsFormatted(filteredAccounts);
}

void Bank::sortAccountsByName(){
    std::sort(accounts.begin(), accounts.end(),
            [](const Account& a, const Account& b) { return a.getName() < b.getName(); });
}

void Bank::sortAccountsByBalance(){
    std::sort(accounts.begin(), accounts.end(),
            [](const Account& a, const Account& b) { return a.getBalance() < b.getBalance(); });
}

void Bank::sortAccountsById(){
    std::sort(accounts.begin(), accounts.end(),
            [](const Account& a, const Account& b) { return a.getId() < b.getId(); });
}
