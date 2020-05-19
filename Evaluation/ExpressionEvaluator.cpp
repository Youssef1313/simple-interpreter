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
    cout << "DEBUG: " << postfix << endl;
    while (stream >> token) {
        if (token.length() == 1 && isOperation(token[0])) {
            if (stack.size() < 2) throw "Invalid expression. Missing an operand..";
            double num2 = stack.top(); // Remember, last-in-first-out. So, this is num2.
            stack.pop();
            double num1 = stack.top();
            stack.pop();
            stack.push(performOperation(num1, num2, token[0]));
        } else if (token.length() == 1 && token[0] == '@') {
            // We wish to refactor the code and add isUnaryOperator and performUnaryOperation methods.
            // But.. If it works, don't touch it.
            if (stack.size() < 1) throw "Invalid expression. Missing an operand....";
            double num = stack.top();
            stack.pop();
            stack.push(-num);
        } else if (token.length() == 1 && token[0] == '$') {
            if (stack.size() < 1) throw "Invalid expression. Missing an operand....";
        }
        else {
            // stof fails for an input like "--7". Manually fixing it.
            //bool isNegative = false;
            //int i = 0;
            //while (token[i] == '-') {
            //    isNegative = !isNegative;
            //    i++;
            //}
            //stack.push(std::stof(token.substr(i)) * (isNegative ? -1 : 1));
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
    for (int i = 0; i < expression.length(); i++) {
        if (expression[i] == ' ') continue;
        if (isUnaryOperator && expression[i] == '-') { // Unary operator
            // To distinguish it later, I'll push it as "@".
            while (!stack.empty() && isHigherPriority(stack.top(), '@')) {
                result.push_back(' ');
                result.push_back(stack.top());
                stack.pop();
            }
            stack.push('@');
            isPreviousAValue = false;
        } else if (isUnaryOperator && expression[i] == '+') { // Unary +
            while (!stack.empty() && isHigherPriority(stack.top(), '$')) {
                result.push_back(' ');
                result.push_back(stack.top());
                stack.pop();
            }
            stack.push('$');
            isPreviousAValue = false;
        }
        else if (isOperation(expression[i])) {
            isUnaryOperator = true;
            while (!stack.empty() && isHigherPriority(stack.top(), expression[i])) {
                result.push_back(' ');
                result.push_back(stack.top());
                stack.pop();
            }
            stack.push(expression[i]);
            isPreviousAValue = false;
        } else if (expression[i] == '(') {
            int j = i + 1;
            while (j < expression.size()) {
                if (expression[j] == ')') throw "Invalid expression. Expected expression inside parenthesis.";
                if (expression[j++] == ' ') continue;
                break;
            }
            stack.push(expression[i]);
            isUnaryOperator = true;
            isPreviousAValue = false;
        } else if (expression[i] == ')') {
            isUnaryOperator = false;
            if (i == 0 || stack.size() == 0) throw "Invalid expression. Unexpected token ')'.";
            while (stack.top() != '(') {
                result.push_back(' ');
                result.push_back(stack.top());
                stack.pop();
            }
            stack.pop();
            isPreviousAValue = false;
        } else {
            if (isPreviousAValue) throw "Invalid expression. Expected an operator.";
            isUnaryOperator = false;
            string number = " "; // space to be appended in result.
            while (isdigit(expression[i]) || expression[i] == '.') {
                number.push_back(expression[i++]);
            }
            i--; // prevent skipping a character.
            // TODO: Check valid number?
            result += number;
            isPreviousAValue = true;
        }
    }

    while (!stack.empty()) {
        if (!isOperation(stack.top()) && stack.top() != '@' && stack.top() != '$') throw "Invalid expression. Missing parenthesis.";
        result.push_back(' ');
        result.push_back(stack.top());
        stack.pop();
    }
    return result;
}

bool ExpressionEvaluator::isOperation(char c) {
    return c == '+' || c == '-' ||
           c == '*' || c == '/' ||
           c == '^';
}

bool ExpressionEvaluator::isHigherPriority(char op1, char op2) {
    return getPriority(op1) > getPriority(op2);
}
/*
* 5 + 7 (  )
 * 5 7 +
 */
int ExpressionEvaluator::getPriority(char op) {
    if (op == '(') return 0;
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    if (op == '^') return 3;
    if (op == '@' || op == '$') return 4;
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
