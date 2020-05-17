#ifndef SIMPLE_INTERPRETER_STATEMENTVALIDATOR_H
#define SIMPLE_INTERPRETER_STATEMENTVALIDATOR_H

#include <string>
#include "StatementType.h"

using namespace std;

class StatementValidator {
public:
    static StatementType validate(string statement);
};


#endif //SIMPLE_INTERPRETER_STATEMENTVALIDATOR_H
