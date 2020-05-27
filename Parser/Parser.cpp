#include "Parser.h"
#include "../Evaluation/Value.h"

Statement *Parser::parse(string statement, unordered_map<string, Value> *map) {
    StatementType statementType = StatementValidator::validate(statement);
    if (statementType == ASSIGNMENT) {
        return new AssignmentStatement(statement, map);
    } else if (statementType == INVALID) {
        return NULL;
    } else if (statementType == IF){
        return new IfStatement(statement, map);
    } else {
        throw string("Unexpected StatementType.\n");
    }
}
