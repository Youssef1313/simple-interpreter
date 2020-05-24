#ifndef SIMPLE_INTERPRETER_STATEMENT_H
#define SIMPLE_INTERPRETER_STATEMENT_H

#include <bits/stdc++.h>
#include <string>
#include "../Evaluation/Value.h"

using namespace std;

class Statement {
protected:
    string statement;
    unordered_map<string, Value> *variables;
    Statement(string statement, unordered_map<string, Value> *variables);

public:
    virtual void execute() = 0;
};


#endif //SIMPLE_INTERPRETER_STATEMENT_H