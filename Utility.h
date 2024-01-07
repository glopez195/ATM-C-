#ifndef UTILITY_H
#define UTILITY_H

#include <iostream>
#include <limits>

class Utility{
    public:
        bool verifyNumber(const std::string&, const int&);
        void clearCinBuffer();
        int getNumber();
        bool isDouble(const std::string& amount);
        double getAmount();
    private:
};

#endif