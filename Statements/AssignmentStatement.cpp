#include "AssignmentStatement.h"
#include "../Evaluation/ExpressionEvaluator.h"

const string &AssignmentStatement::getVariableName() const {
    return variableName;
}

const string &AssignmentStatement::getValueExpression() const {
    return valueExpression;
}

int AssignmentStatement::fillVariableName(int i) {
    while (isalpha(statement[i]) || isdigit(statement[i]) || statement[i] == '_')
        variableName.push_back(statement[i++]);
    return i;
}

int AssignmentStatement::getEqualCharAndFillVariableName() {
    int i = 0;
    if (!isalpha(statement[i]) && statement[i] != '_')
        throw string("Variable name must start with a letter or an underscore.");

    i = fillVariableName(i);

    while (statement[i] == ' ') i++; // skip whitespaces.
    if(statement[i] != '=') throw string("Assignment statement must have '=' character after variable name.\n");
    return i;

}

AssignmentStatement::AssignmentStatement(string statement, unordered_map<string, Value> *variables)
        : Statement(statement, variables) {
    int i = getEqualCharAndFillVariableName() + 1;// without this, 'i' will be the index of an equal sign.
    while (statement[i] == ' ') i++; // skip any whitespaces.
    valueExpression = statement.substr(i);
}

void AssignmentStatement::execute() {
    ExpressionEvaluator evaluator(valueExpression, *variables);
    Value variableValue = evaluator.evaluate();
    auto it = variables->find(variableName);
    if (it == variables->end()) {
        variables->emplace(variableName, variableValue);
    } else {
        it->second = variableValue;
    }
}

