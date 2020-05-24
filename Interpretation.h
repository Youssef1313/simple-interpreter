#ifndef SIMPLE_INTERPRETER_INTERPRETATION_H
#define SIMPLE_INTERPRETER_INTERPRETATION_H

#include <bits/stdc++.h>
#include <string>
#include "Evaluation/Value.h"

using namespace std;

class Interpretation {
private:
    unordered_map<string, Value> variables;
public:
    /*
     * Parse the line, then call execute on the returned statement.
     */
    void process(string line);
    unordered_map<string, Value> getVariables() const;
};


#endif //SIMPLE_INTERPRETER_INTERPRETATION_H
