#include "StatementValidator.h"
#include "../Statements/AssignmentStatement.h"

StatementType StatementValidator::validate(string statement) {
    if (AssignmentStatement::isValid(statement)) {
        return ASSIGNMENT;
    } else {
        return INVALID;
    }
}
