#include "AssignmentStatement.h"

const string &AssignmentStatement::getVariableName() const {
    return variableName;
}

const string &AssignmentStatement::getValueExpression() const {
    return valueExpression;
}

AssignmentStatement::AssignmentStatement(string statement, unordered_map<string, double> variables)
        : Statement(statement, variables) {
    int i = 0;
    while (statement[i] == ' ') i++; // skip any whitespaces at beginning.
    variableName = "";
    while (statement[i] != ' ' && statement[i] != '=') variableName.push_back(statement[i++]);
    i++; // without this, i will be the index of a space or an equal sign.
    while (statement[i] == ' ' || statement[i] == '=') i++; // skip any whitespaces or an equal sign.
    valueExpression = statement.substr(i);
}

void AssignmentStatement::execute() {
    double variableValue = 0; // TODO: This is incorrect.
    // TODO: variableValue should be returned from expression evaluator.
    variables[variableName] = variableValue;
}

bool AssignmentStatement::isValid(string statement) {
    if (statement.length() == 0) return false;
    int i = 0;
    while (statement[i] == ' ') i++; // skip leading whitespaces.
    if (!isalpha(statement[i]) || !statement[i] == '_') return false; // variable must start with letter or underscore. (Same as python rules).
    string variableName = "";
    while (isalpha(statement[i]) || isdigit(statement[i]) || statement[i] == '_') {
        variableName.push_back(statement[i]);
        i++;
    }
    while (statement[i] == ' ') i++; // skip leading whitespaces.
    return statement[i] == '=';

}
