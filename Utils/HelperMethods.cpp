#include <string>
#include "HelperMethods.h"
#include "Constants.h"

bool HelperMethods::isValidCharacter(char c) {
    return isdigit(c) || isalpha(c) || c == '_';
}

bool HelperMethods::stringStartsWith(string toSearchIn, string toSearchFor) {
    if (toSearchFor.length() > toSearchIn.length()) return false;
    int i = 0;
    for (char c : toSearchFor) {
        if (toSearchIn[i++] != c) return false;
    }
    return true;
}

void HelperMethods::skipWhitespaces(string str, int *index) {
    while (*index < (int) str.length() && isspace(str[*index])) (*index)++;
}

bool HelperMethods::isKeyword(string s) {
    return s == IF_KEYWORD ||
           s == LABEL_KEYWORD ||
           s == TRUE_KEYWORD ||
           s == FALSE_KEYWORD ||
           s == GOTO_KEYWORD;
}
