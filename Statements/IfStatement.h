#ifndef SIMPLE_INTERPRETER_IFSTATEMENT_H
#define SIMPLE_INTERPRETER_IFSTATEMENT_H


#include "Statement.h"
#include <string>
#include <iostream>


class IfStatement : public Statement {
private:
    string conditionExpression;
    Statement *conditioned_Statement;
    const string ifSub = "if ";
    const string colonSub = ":";

    size_t getColonPos();

public:
    IfStatement(const string &statement, unordered_map<string, Value> *variables);

    void execute() override;

    //getters are for test purposes.
    const string &getConditionExpression() const;

    Statement *getConditionedStatement() const;
};


#endif //SIMPLE_INTERPRETER_IFSTATEMENT_H
