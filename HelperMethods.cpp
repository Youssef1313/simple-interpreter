#include <string>
#include "HelperMethods.h"

bool HelperMethods::isValidCharacter(char c) {
    return isdigit(c) || isalpha(c) || c == '_';
}
