#ifndef ACCOUNT_H
#define ACCOUNT_H

class Account {
public:
    Account(int, double, std::string);
    int getId() const;
    std::string getName() const;
    double getBalance() const;
    void deposit(double);
    bool withdraw(double);

private:
    int id;
    double balance;
    std::string name;
};

#endif