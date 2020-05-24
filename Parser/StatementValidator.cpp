#include "StatementValidator.h"
#include "../Statements/AssignmentStatement.h"
#include "../Statements/IfStatement.h"

StatementType StatementValidator::validate(string statement) {
    if (AssignmentStatement::isValid(statement)) {
        return ASSIGNMENT;
    } else if(IfStatement::isValid(statement))
        return IF;
    else {
        return INVALID;
    }
}
