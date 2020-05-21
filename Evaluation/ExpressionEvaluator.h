#ifndef SIMPLE_INTERPRETER_EXPRESSIONEVALUATOR_H
#define SIMPLE_INTERPRETER_EXPRESSIONEVALUATOR_H

#include <string>
#include <bits/stdc++.h>

using namespace std;

class ExpressionEvaluator {
private:
    string expression;
    unordered_map<string, double> variables;
    bool isOperation(char c);
    string convertToPostfix();
    bool isHigherOrEqualPriority(char op1, char op2);
    bool isHigherPriority(char op1, char op2);
    bool isLeftAssociative(char op);
    int getPriority(char op);
    double performOperation(double num1, double num2, char op);

public:
    ExpressionEvaluator(string expression, unordered_map<string, double> variables);
    double evaluate();
};


#endif //SIMPLE_INTERPRETER_EXPRESSIONEVALUATOR_H
