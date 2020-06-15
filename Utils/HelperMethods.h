#ifndef SIMPLE_INTERPRETER_HELPERMETHODS_H
#define SIMPLE_INTERPRETER_HELPERMETHODS_H

#include <string>

using namespace std;

class HelperMethods {
public:
    /**
     * @brief Checks if a given character can be contained in a variable name.
     * @param c The character to check.
     * @return Returns true if the character is alpha, digit, or underscore.
     */
    static bool isValidCharacter(char c);

    /**
     * @brief Checks if a given character can be contained in a variable name.
     * @param c The character to check.
     * @return Returns true if the character is alpha or underscore.
     */
    static bool isValidFirstCharacter(char c);

    /**
     * @brief Checks if a given character is a whitespace.
     * @param c The character to check.
     * @return Returns true if the character is either a space or a tab.
     */
    static bool isWhitespace(char c);

    /**
     * @brief Determines whether the beginning of a string matches a specified string.
     * @param toSearchIn The string to search in.
     * @param toSearchFor The string to search for.
     * @return true if @arg toSearchIn starts with @arg toSearchFor
     */
    static bool stringStartsWith(string toSearchIn, string toSearchFor);

    /**
     * @brief Increases the index starting with its given value until the first non-whitespace character.
     * @param str The string to operate on.
     * @param index a pointer to the integer that will be increased to the first non-whitespace character.
     */
    static void skipWhitespaces(string str, int *index);

    // TODO: Use this method to determine validity of variables and label names.
    /**
     * @brief Determines whether a given string is a keyword or not.
     * @param s The string to check.
     * @return true if @arg s is a keyword, false otherwise.
     */
    static bool isKeyword(string s);
};


#endif //SIMPLE_INTERPRETER_HELPERMETHODS_H
