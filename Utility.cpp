#include "Utility.h"

void Utility::clearCinBuffer() {
    std::cin.clear(); // Clears any error flags that may be set in cin.
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignores the remaining input.
}

bool Utility::verifyNumber(const std::string &input, const int& numberLen) {    
    try {
        if (input.length() != numberLen) {
            throw "\033[31m Invalid Entry. \033[0m\n"; // Throw exception if length mismatch.
        }
        for (char c : input) {
            if (!isdigit(c)) { // Check each character to ensure it's a digit.
                throw "\033[31m Invalid Entry. \033[0m\n"; // Throw exception if non-digit found.
            }
        }
    } catch (const char *e) {  
        std::cerr << e; // Output the error message to standard error.
        clearCinBuffer(); // Clear the input buffer to prevent further input errors.
        return false;
    }
    return true; // Return true if all checks pass.
}

int Utility::getNumber() {
    int entry;
    try {
        std::cin >> entry; // Attempt to read an integer from standard input.
    } catch (const char *e) {
        clearCinBuffer(); // Clear the input buffer in case of an error.
        return 0; // Return 0 in case of an error.
    }
    return entry; // Return the read integer.
}

bool Utility::isDouble(const std::string& amount) {
    try {
        size_t idx;
        double val = std::stod(amount, &idx); // Try converting the string to a double.
        return idx == amount.size(); // Check if the entire string was processed.
    } catch (const std::invalid_argument& e) {
        return false; // Return false if an invalid argument was passed.
    } catch (const std::out_of_range& e) {
        return false; // Return false if the converted value is out of the range of representable values.
    }
}

double Utility::getAmount() {
    std::string validAmount;
    clearCinBuffer(); // Clear the input buffer before reading.
    std::getline(std::cin, validAmount); // Read a line of input as a string.
    if (isDouble(validAmount)) { // Check if the input string is a valid double.
        return std::stod(validAmount); // Convert the string to a double and return.
    }
    return -1; // Return -1 if the input is not a valid double.
}
