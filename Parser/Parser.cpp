#include "Parser.h"

Statement *Parser::parse(string statement, unordered_map<string, double> *map) {
    // Read until you find '#', then stop.
    // The '#' character means the rest of the line is a comment.
    int lengthBeforeComment = 0;
    while (statement[lengthBeforeComment] != '#' && lengthBeforeComment < (int)statement.length()) {
        lengthBeforeComment++;
    }

    statement = statement.substr(0, lengthBeforeComment); // substr takes starting index and length.
    StatementType statementType = StatementValidator::validate(statement);
    if (statementType == ASSIGNMENT) {
        return new AssignmentStatement(statement, map);
    } else if (statementType == INVALID) {
        return NULL;
    } else {
        throw string("Unexpected StatementType.\n");
    }
}
