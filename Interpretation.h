//
// Created by Youssef on 16/05/2020.
//

#ifndef SIMPLE_INTERPRETER_INTERPRETATION_H
#define SIMPLE_INTERPRETER_INTERPRETATION_H

#include <bits/stdc++.h>
#include <string>

using namespace std;

class Interpretation {
private:
  unordered_map<string, double> variables;
public:
    pair<string, double> process(string line);
    /*
     * Parse the line, then call execute on the returned statement.
     */
};


#endif //SIMPLE_INTERPRETER_INTERPRETATION_H
