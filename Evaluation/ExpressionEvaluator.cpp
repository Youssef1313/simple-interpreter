#include <bits/stdc++.h>
#include "ExpressionEvaluator.h"

ExpressionEvaluator::ExpressionEvaluator(string expression, unordered_map<string, double> variables) {
    this->expression = expression;
    this->variables = variables;
}

double ExpressionEvaluator::evaluate() {
    string postfix = convertToPostfix();
    string token;
    istringstream stream(postfix);
    stack<double> stack;
    while (stream >> token) {
        if (token.length() == 1 && isOperation(token[0])) {
            if (stack.size() < 2) throw "Invalid expression. Missing an operand..";
            double num2 = stack.top(); // Remember, last-in-first-out. So, this is num2.
            stack.pop();
            double num1 = stack.top();
            stack.pop();
            stack.push(performOperation(num1, num2, token[0]));
        } else if (token.length() == 1 && token[0] == '@') {
            if (stack.size() < 1) throw "Invalid expression. Missing an operand....";
            double num = stack.top();
            stack.pop();
            stack.push(-num);
        } else if (token.length() == 1 && token[0] == '$') {
            if (stack.size() < 1) throw "Invalid expression. Missing an operand....";
        } else {
            stack.push(std::stof(token));
        }
    }
    if (stack.size() == 1) return stack.top();
    throw "Invalid expression.";
}

string ExpressionEvaluator::convertToPostfix() {
    // This variables keeps track when the + and - are unary operators and when they're binary operators.
    bool isUnaryOperator = true;
    bool isPreviousAValue = false;
    stack<char> stack;
    string result = "";
    for (int i = 0; i < (int)expression.length(); i++) {
        if (expression[i] == ' ') continue;
        if (isOperation(expression[i])) {
            char op = expression[i];
            if (isUnaryOperator) {
                // To distinguish it later, I'll push it as "@" or $.
                if (op == '+') op = '$';
                else if (op == '-') op = '@';
            }
            /* Why we use isHigherPriority for unary operators, and isHigherOrEqualPriority for binary?
             * Read the Shunting-yard algo at Wikipedia: https://en.wikipedia.org/wiki/Shunting-yard_algorithm
             *
             * and ((the operator at the top of the operator stack has greater precedence)
             *  or (the operator at the top of the operator stack has equal precedence and the token is left associative))
             *
             *  Unary operators are right-associative.
             */
            while (!stack.empty() &&
                   (isHigherPriority(stack.top(), op) ||
                    (isHigherOrEqualPriority(stack.top(), op) && isLeftAssociative(op)))
                    ) {
                result.push_back(' ');
                result.push_back(stack.top());
                stack.pop();
            }
            stack.push(op);
            isPreviousAValue = false;
            isUnaryOperator = true;
        } else if (expression[i] == '(') {
            int j = i + 1;
            while (j < (int)expression.size()) {
                if (expression[j] == ')') throw "Invalid expression. Expected expression inside parenthesis.";
                if (expression[j++] == ' ') continue;
                break;
            }
            stack.push(expression[i]);
            isUnaryOperator = true;
            isPreviousAValue = false;
        } else if (expression[i] == ')') {
            // Throw instead of trying to access top in an empty stack.
            if (stack.size() == 0) throw "Invalid expression. Unexpected token ')'.";
            while (stack.top() != '(') {
                // Throw instead of trying to pop in an empty stack.
                if (stack.size() == 0) throw "Invalid expression. Unexpected token ')'.";
                result.push_back(' ');
                result.push_back(stack.top());
                stack.pop();
            }
            stack.pop();
            isPreviousAValue = false;
            isUnaryOperator = false;
        } else {
            if (isPreviousAValue) throw "Invalid expression. Expected an operator.";
            if (isalpha(expression[i]) || expression[i] == '_') {
                string variableName = "";
                while (isdigit(expression[i]) || isalpha(expression[i]) || expression[i] == '_') {
                    variableName.push_back(expression[i++]);
                }
                i--; // prevent skipping a character.
                unordered_map<string, double>::const_iterator foundValue = variables.find(variableName);
                if (foundValue == variables.end()) {
                    throw "Undeclared variable '" + variableName + "'\n";
                } else {
                    result += " " + to_string(foundValue->second);
                }
            } else {
                string number = " "; // space to be appended in result.
                while (isdigit(expression[i]) || expression[i] == '.') {
                    number.push_back(expression[i++]);
                }
                i--; // prevent skipping a character.
                // TODO: Check valid number?
                result += number;
            }
            isPreviousAValue = true;
            isUnaryOperator = false;
        }
    }

    while (!stack.empty()) {
        if (!isOperation(stack.top()) && stack.top() != '@' && stack.top() != '$')
            throw "Invalid expression. Missing parenthesis.";
        result.push_back(' ');
        result.push_back(stack.top());
        stack.pop();
    }
    return result;
}

bool ExpressionEvaluator::isLeftAssociative(char op) {
    if (op == '^' || op == '@' || op == '$') return false;
    return true;
}

bool ExpressionEvaluator::isOperation(char c) {
    return c == '+' || c == '-' ||
           c == '*' || c == '/' ||
           c == '^';
}

bool ExpressionEvaluator::isHigherOrEqualPriority(char op1, char op2) {
    return getPriority(op1) >= getPriority(op2);
}

bool ExpressionEvaluator::isHigherPriority(char op1, char op2) {
    return getPriority(op1) > getPriority(op2);
}

int ExpressionEvaluator::getPriority(char op) {
    if (op == '(') return 0;
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    if (op == '@' || op == '$') return 3;
    if (op == '^') return 4;
    string errorMessage = "Unsupported operation '";
    errorMessage.push_back(op);
    errorMessage.push_back('\'');
    errorMessage.push_back('.');
    throw errorMessage;
}

double ExpressionEvaluator::performOperation(double num1, double num2, char op) {
    if (op == '+') return num1 + num2;
    if (op == '-') return num1 - num2;
    if (op == '*') return num1 * num2;
    if (op == '/') {
        if (num2 == 0) throw "Cannot divide by zero.";
        return num1 / num2;
    }
    if (op == '^') return pow(num1, num2);
    throw "Unsupported operator.";
}
