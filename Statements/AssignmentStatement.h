/*
 * this class only check that variables names rules applied,
 * it doesn't check Expression Correctness
 */

#ifndef SIMPLE_INTERPRETER_ASSIGNMENTSTATEMENT_H
#define SIMPLE_INTERPRETER_ASSIGNMENTSTATEMENT_H

#include <string>
#include <bits/stdc++.h>
#include "Statement.h"

using namespace std;

class AssignmentStatement : public Statement {
private:
    unordered_map<string, double> variables;
    string variableName;
    string valueExpression;

public:
    AssignmentStatement(string statement, unordered_map<string, double> variables); // The constructor will set the variableName and the valueExpression.
    // The variableName cannot be a reserved word, this should be handled in the validation, not in this constructor.
    // The constructor here assumes that the statement is always correct.
    // The constructor needs the variables map, so that the execute method can put the new value in it.
    void execute();
    static bool isValid(string statement);
    const string &getVariableName() const;
    const string &getValueExpression() const;

};


#endif //SIMPLE_INTERPRETER_ASSIGNMENTSTATEMENT_H
