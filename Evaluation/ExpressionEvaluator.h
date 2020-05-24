#ifndef SIMPLE_INTERPRETER_EXPRESSIONEVALUATOR_H
#define SIMPLE_INTERPRETER_EXPRESSIONEVALUATOR_H

#include <string>
#include <bits/stdc++.h>
#include "Value.h"
#include "Operator.h"

using namespace std;

class ExpressionEvaluator {
private:
    string expression;
    unordered_map<string, Value> variables;
    static Operator getOperatorFromToken(string token);
    static string getTokenFromOperator(Operator op);
    static bool isUnaryOperator(Operator op);
    static bool isOperation(char c);
    static bool isHigherOrEqualPriority(Operator op1, Operator op2);
    static bool isHigherPriority(Operator op1, Operator op2);
    static bool isLeftAssociative(Operator op);
    static int getPriority(Operator op);
    static Value performOperation(Value left, Value right, Operator op);
    string convertToPostfix();

public:
    ExpressionEvaluator(string expression, unordered_map<string, Value> variables);
    Value evaluate();
};


#endif //SIMPLE_INTERPRETER_EXPRESSIONEVALUATOR_H
