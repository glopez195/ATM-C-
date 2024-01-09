#ifndef UTILITY_H
#define UTILITY_H

#include <iostream>
#include <limits>

/**
 * The Utility class provides utility functions for input validation
 * and manipulation in the context of a banking application.
 */
class Utility {
public:
    /**
     * Verifies if a given string represents a number of specified length.
     * 
     * @param input The string to be verified.
     * @param numberLen The expected length of the number.
     * @return true if input is a number with the specified length, false otherwise.
     */
    bool verifyNumber(const std::string& input, const int& numberLen);

    /**
     * Clears the input buffer to avoid any leftover input affecting subsequent reads.
     */
    void clearCinBuffer();

    /**
     * Reads an integer number from standard input.
     * 
     * @return The read integer.
     */
    int getNumber();

    /**
     * Checks if a string can be converted to a double without errors.
     * 
     * @param amount The string to check.
     * @return true if the string can be converted to a double, false otherwise.
     */
    bool isDouble(const std::string& amount);

    /**
     * Reads a double value from standard input. Ensures the validation of the input.
     * 
     * @return The read double value. Returns -1 if the input is not a valid double.
     */
    double getAmount();
};

#endif // UTILITY_H
