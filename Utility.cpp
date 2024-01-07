#include "Utility.h"

void Utility::clearCinBuffer() {
    // Clears any error flags
    std::cin.clear(); 

    // Ignores the maximum number of characters until a newline is found
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
}

bool Utility::verifyNumber(const std::string &input, const int& numberLen){    
    try
    {
        if (input.length() != numberLen) 
            throw "\033[31m Invalid Entry. \033[0m\n";
    
        for (char c : input) {
            if (!isdigit(c)) 
                throw "\033[31m Invalid Entry. \033[0m\n";
        }
        
    }

    catch (const char *e) 
    {  
        std::cerr << e << '\n';            
        clearCinBuffer();
        return false;
    }

    return true;    
}

int Utility::getNumber(){
    int entry;
    try
    {
        std::cin >> entry;        
    }
    catch(const char *e)
    {
        clearCinBuffer();
        return 0;
    }
    
    return entry;
}

bool Utility::isDouble(const std::string& amount) {
    try {
        size_t idx;
        double val = std::stod(amount, &idx);
        return idx == amount.size();
    } catch (const std::invalid_argument& e) {
        return false;
    } catch (const std::out_of_range& e) {
        return false;
    }
}

double Utility::getAmount(){
    std::string validAmount;
    clearCinBuffer();
    std::getline(std::cin, validAmount);
    if(isDouble(validAmount))
        return std::stod(validAmount);
    return -1;
}