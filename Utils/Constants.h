#ifndef SIMPLE_INTERPRETER_CONSTANTS_H
#define SIMPLE_INTERPRETER_CONSTANTS_H

#include <string>

using namespace std;

// When a new keyword is added here, the HelperMethods::isKeyword MUST be updated.

const string IF_KEYWORD = "if";
const string LABEL_KEYWORD = "label";
const string TRUE_KEYWORD = "true";
const string FALSE_KEYWORD = "false";
const string GOTO_KEYWORD = "goto";


#endif //SIMPLE_INTERPRETER_CONSTANTS_H
