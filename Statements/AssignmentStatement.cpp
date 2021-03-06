#include "AssignmentStatement.h"
#include "../Evaluation/ExpressionEvaluator.h"
#include "../Utils/HelperMethods.h"


int AssignmentStatement::fillVariableName(int i) {
    while (HelperMethods::isValidCharacter(statement[i])) // alpha, digit, or underscore.
        variableName.push_back(statement[i++]);
    if (HelperMethods::isKeyword(variableName))
        throw string("Variable name cannot be a keyword.");
    return i;
}

int AssignmentStatement::getEqualCharAndFillVariableName() {
    int i = 0;

    if (!HelperMethods::isValidFirstCharacter(statement[i]))
        throw string("Variable name must start with a letter or an underscore.");

    i = fillVariableName(i);

    HelperMethods::skipWhitespaces(statement, &i);

    if (statement[i] != '=') throw string("Assignment statement must have '=' character after variable name.\n");

    return i;

}

AssignmentStatement::AssignmentStatement(string statement, unordered_map<string, Value> *variables)
        : Statement(statement, variables) {
    int i = getEqualCharAndFillVariableName() + 1; // without +1, 'i' will be the index of an equal sign.
    HelperMethods::skipWhitespaces(statement, &i);
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

