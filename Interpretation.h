#ifndef SIMPLE_INTERPRETER_INTERPRETATION_H
#define SIMPLE_INTERPRETER_INTERPRETATION_H

#include <bits/stdc++.h>
#include <iostream>
#include <string>
#include "Evaluation/Value.h"
#include "Statements/Statement.h"
#include "Statements/GotoStatement.h"
using namespace std;

class Interpretation {
private:
    unordered_map<string, Value> variables;
    list<Statement*> fileData;
    unordered_map<string,list<Statement*>::iterator> labelData;

public:
    /*
     * Parse the line, then call execute on the returned statement.
     */
    void process(string line);
    unordered_map<string, Value> getVariables() const;
    Interpretation();
private:
    string checkLabel(string statement, string *labelName);

};


#endif //SIMPLE_INTERPRETER_INTERPRETATION_H
