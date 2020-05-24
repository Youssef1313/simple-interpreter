#ifndef SIMPLE_INTERPRETER_IFSTATEMENT_H
#define SIMPLE_INTERPRETER_IFSTATEMENT_H


#include "Statement.h"
#include <string>
#include <iostream>


class IfStatement : public Statement {
private:
    string conditionExpression;
    Statement *conditioned_Statement;
public:
    IfStatement(const string &statement, unordered_map<string, Value> *variables);
    static bool isValid(const string& statement);
    void execute() override;
};


#endif //SIMPLE_INTERPRETER_IFSTATEMENT_H
