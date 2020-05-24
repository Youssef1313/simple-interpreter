/*
 * this class only check that variables names rules applied,
 * it doesn't check Expression Correctness
 */

#ifndef SIMPLE_INTERPRETER_ASSIGNMENTSTATEMENT_H
#define SIMPLE_INTERPRETER_ASSIGNMENTSTATEMENT_H

#include <string>
#include <bits/stdc++.h>
#include "Statement.h"
#include "../Evaluation/Value.h"

using namespace std;

class AssignmentStatement : public Statement {
private:
    string variableName;
    string valueExpression;

public:
    AssignmentStatement(string statement, unordered_map<string, Value> *variables);
    // Constructor will set variableName and valueExpression.
    // VariableName cannot be a reserved word, this should be handled in validation, not in this constructor.
    // Constructor here assumes that the statement is always correct.
    // Constructor needs variables map, so that execute method can put new value in it.

    void execute();
    static bool isValid(string statement);
    const string &getVariableName() const;
    const string &getValueExpression() const;

};


#endif //SIMPLE_INTERPRETER_ASSIGNMENTSTATEMENT_H
