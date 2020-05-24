#include <bits/stdc++.h>
#include "ExpressionEvaluator.h"

using namespace std;

ExpressionEvaluator::ExpressionEvaluator(string expression, unordered_map<string, Value> variables) {
    this->expression = expression;
    this->variables = variables;
}

Operator ExpressionEvaluator::getOperatorFromToken(string token) { // This method is used in postfix evaluation.
    if (token == "$") return UNARY_PLUS;
    if (token == "@") return UNARY_MINUS;
    if (token == "+") return BINARY_PLUS;
    if (token == "-") return BINARY_MINUS;
    if (token == "*") return MULTIPLICATION;
    if (token == "/") return DIVISION;
    if (token == "^") return POWER;
    if (token == "&&") return LOGICAL_AND;
    if (token == "||") return LOGICAL_OR;
    if (token == ">") return GREATER_THAN;
    if (token == "<") return LESS_THAN;
    if (token == "==") return EQUALS;
    return UNKNOWN;
}

// This method is used in conversion from infix to postfix.
string ExpressionEvaluator::getTokenFromOperator(Operator op) {
    switch (op) {
        case UNARY_PLUS:
            return "$";
        case UNARY_MINUS:
            return "@";
        case BINARY_PLUS:
            return "+";
        case BINARY_MINUS:
            return "-";
        case MULTIPLICATION:
            return "*";
        case DIVISION:
            return "/";
        case POWER:
            return "^";
        case LOGICAL_AND:
            return "&&";
        case LOGICAL_OR:
            return "||";
        case GREATER_THAN:
            return ">";
        case LESS_THAN:
            return "<";
        case EQUALS:
            return "==";
        default:
            throw string("Unknown operator.\n");
    }
}

bool ExpressionEvaluator::isUnaryOperator(Operator op) {
    return op == UNARY_PLUS || op == UNARY_MINUS;
}

Value ExpressionEvaluator::evaluate() {
    string postfix = convertToPostfix();
    string token;
    istringstream stream(postfix);
    stack<Value> stack;
    while (stream >> token) {
        Operator op = getOperatorFromToken(token);
        if (op == UNKNOWN) { // The token isn't operator.
            if (token == "true") {
                stack.push(Value(true));
            } else if (token == "false") {
                stack.push(Value(false));
            } else if (token.find('.') != string::npos) { // double
                stack.push(Value(stof(token)));
            } else { // int
                stack.push(Value(stoi(token)));
            }
        } else if (isUnaryOperator(op)) {
            if (stack.size() < 1) throw "Invalid expression. Missing an operand.";
            Value top = stack.top();
            stack.pop();
            stack.push(performOperation(top, UNKNOWN, op));

        } else { // Binary operator.
            if (stack.size() < 2) throw "Invalid expression. Missing an operand.";
            Value operand2 = stack.top();
            stack.pop();
            Value operand1 = stack.top();
            stack.pop();
            stack.push(performOperation(operand1, operand2, op));
        }
    }
    if (stack.size() == 1) return stack.top();
    throw "Invalid expression.";
}

string ExpressionEvaluator::convertToPostfix() {
    // This variables keeps track when the + and - are unary operators and when they're binary operators.
    bool isUnaryOperator = true;
    bool isPreviousAValue = false;
    stack<Operator> stack;
    string result = "";
    for (int i = 0; i < (int) expression.length(); i++) {
        if (expression[i] == ' ') continue;
        if (isOperation(expression[i])) {
            Operator op = UNKNOWN;
            if (isUnaryOperator) {
                if (expression[i] == '+') op = UNARY_PLUS;
                else if (expression[i] == '-') op = UNARY_MINUS;
            }
            if (op == UNKNOWN) {
                op = getOperatorFromToken(expression.substr(i, 2));
                if (op != UNKNOWN) i++; // Skip the next char as it's part of the current operator.
                else {
                    op = getOperatorFromToken(string(1, expression[i]));
                }
            }
            if (op == UNKNOWN)
                throw "Unknown operator '" + string(1, expression[i]) + "'\n";

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
                result += getTokenFromOperator(stack.top());
                stack.pop();
            }
            stack.push(op);
            isPreviousAValue = false;
            isUnaryOperator = true;
        } else if (expression[i] == '(') {
            int j = i + 1;
            while (j < (int) expression.size()) {
                if (expression[j] == ')') throw string("Invalid expression. Expected expression inside parenthesis.\n");
                if (expression[j++] == ' ') continue;
                break;
            }
            stack.push(LEFT_PARENTHESIS);
            isUnaryOperator = true;
            isPreviousAValue = false;
        } else if (expression[i] == ')') {
            // Throw instead of trying to access top in an empty stack.
            if (stack.size() == 0) throw "Invalid expression. Unexpected token ')'.";
            while (stack.top() != LEFT_PARENTHESIS) {
                // Throw instead of trying to pop in an empty stack.
                if (stack.size() == 0) throw "Invalid expression. Unexpected token ')'.";
                result.push_back(' ');
                result += getTokenFromOperator(stack.top());
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
                unordered_map<string, Value>::const_iterator foundValue = variables.find(variableName);
                if (foundValue == variables.end()) {
                    if (variableName == "true" || variableName == "false") result += " " + variableName;
                    else throw "Undeclared variable '" + variableName + "'.\n";
                } else {
                    result += " " + foundValue->second.toString();
                }
            } else {
                string number = " "; // space to be appended in result.
                while (isdigit(expression[i]) || expression[i] == '.') {
                    number.push_back(expression[i++]);
                }
                i--; // prevent skipping a character.
                // TODO: Check valid number? "X = 5 + ." will generate an exception.
                result += number;
            }
            isPreviousAValue = true;
            isUnaryOperator = false;
        }
    }

    while (!stack.empty()) {
        if (stack.top() == LEFT_PARENTHESIS)
            throw "Invalid expression. Missing parenthesis.";
        result.push_back(' ');
        result += getTokenFromOperator(stack.top());
        stack.pop();
    }
    return result;
}

bool ExpressionEvaluator::isLeftAssociative(Operator op) {
    // return !isRightAssociative.
    return !(op == POWER || op == UNARY_PLUS || op == UNARY_MINUS);
}

bool ExpressionEvaluator::isOperation(char c) {
    /*
     * Currently, The '&' and '|' by itself isn't a correct operator.
     * We're checking that it's followed by another '&' or '|' while converting to postfix.
     * Later, if we supported bitwise-and operator, the '&' will become valid by itself.
     * In that case, this comment must be removed.
     */
    return c == '+' || c == '-' ||
           c == '*' || c == '/' ||
           c == '&' || c == '|' ||
           c == '<' || c == '>' ||
           c == '^' || c == '=';
}

bool ExpressionEvaluator::isHigherOrEqualPriority(Operator op1, Operator op2) {
    return getPriority(op1) >= getPriority(op2);
}

bool ExpressionEvaluator::isHigherPriority(Operator op1, Operator op2) {
    return getPriority(op1) > getPriority(op2);
}

int ExpressionEvaluator::getPriority(Operator op) {
    switch (op) {
        case LEFT_PARENTHESIS:
            return 0;
        case LOGICAL_OR:
            return 1;
        case LOGICAL_AND:
            return 2;
            // bitwise or will be 3 if added.
            // bitwise and will be 4 if added.
        case EQUALS:
            return 5;
        case LESS_THAN:
        case GREATER_THAN:
            return 6;
        case BINARY_PLUS:
        case BINARY_MINUS:
            return 7;
        case MULTIPLICATION:
        case DIVISION:
            return 8;
        case UNARY_MINUS:
        case UNARY_PLUS:
            return 9;
        case POWER:
            return 10;
        default:
            throw string("Unknown operator.\n");

    }
}

Value ExpressionEvaluator::performOperation(Value left, Value right, Operator op) {
    switch (op) {
        case UNARY_MINUS: {
            if (left.isBoolValue()) throw string("The unary `-` operator cannot be applied to a boolean.");
            return left.isIntValue() ? Value(-left.getIntValue()) : Value(-left.getDoubleValue());
        }
        case UNARY_PLUS: {
            if (left.isBoolValue()) throw string("The unary `+` operator cannot be applied to a boolean.");
            return left.isIntValue() ? Value(left.getIntValue()) : Value(left.getDoubleValue());
        }
        case BINARY_PLUS: {
            if (left.isBoolValue() || right.isBoolValue())
                throw string("The '+' operator cannot be applied to booleans.\n");
            if (left.isIntValue()) {
                if (right.isIntValue()) return Value(left.getIntValue() + right.getIntValue());
                return Value(left.getIntValue() + right.getDoubleValue());
            } else {
                if (right.isIntValue()) return Value(left.getDoubleValue() + right.getIntValue());
                return Value(left.getDoubleValue() + right.getDoubleValue());
            }
        }
        case BINARY_MINUS: {
            if (left.isBoolValue() || right.isBoolValue())
                throw string("The '-' operator cannot be applied to booleans.\n");
            if (left.isIntValue()) {
                if (right.isIntValue()) return Value(left.getIntValue() - right.getIntValue());
                return Value(left.getIntValue() - right.getDoubleValue());
            } else {
                if (right.isIntValue()) return Value(left.getDoubleValue() - right.getIntValue());
                return Value(left.getDoubleValue() - right.getDoubleValue());
            }
        }
        case MULTIPLICATION: {
            if (left.isBoolValue() || right.isBoolValue())
                throw string("The '*' operator cannot be applied to booleans.\n");
            if (left.isIntValue()) {
                if (right.isIntValue()) return Value(left.getIntValue() * right.getIntValue());
                return Value(left.getIntValue() * right.getDoubleValue());
            } else {
                if (right.isIntValue()) return Value(left.getDoubleValue() * right.getIntValue());
                return Value(left.getDoubleValue() * right.getDoubleValue());
            }
        }
        case DIVISION: {
            if (left.isBoolValue() || right.isBoolValue())
                throw string("The '/' operator cannot be applied to booleans.\n");
            if (right.isIntValue()) {
                if (right.getIntValue() == 0) throw string("Cannot divide by zero.\n");
                if (left.isIntValue()) return Value(left.getIntValue() / right.getIntValue());
                return Value(left.getDoubleValue() / right.getIntValue());
            } else {
                if (right.getDoubleValue() == 0) throw string("Cannot divide by zero.\n");
                if (left.isIntValue()) return Value(left.getIntValue() / right.getDoubleValue());
                return Value(left.getDoubleValue() / right.getDoubleValue());
            }
        }
        case POWER: {
            if (left.isBoolValue() || right.isBoolValue())
                throw string("The '^' operator cannot be applied to booleans.\n");
            double num1 = left.isIntValue() ? left.getIntValue() : left.getDoubleValue();
            double num2 = right.isIntValue() ? right.getIntValue() : right.getDoubleValue();
            return Value(pow(num1, num2));
        }
        case LOGICAL_AND: {
            if (left.isBoolValue() && right.isBoolValue()) {
                return Value(left.getBoolValue() && right.getBoolValue());
            } else {
                throw string("The '&&' operator can only be applied to booleans.\n");
            }
        }
        case LOGICAL_OR: {
            if (left.isBoolValue() && right.isBoolValue()) {
                return Value(left.getBoolValue() || right.getBoolValue());
            } else {
                throw string("The '||' operator can only be applied to booleans.\n");
            }
        }
        case GREATER_THAN: {
            if (left.isBoolValue() || right.isBoolValue())
                throw string("The '>' operator cannot be applied to booleans.\n");
            double num1 = left.isIntValue() ? left.getIntValue() : left.getDoubleValue();
            double num2 = right.isIntValue() ? right.getIntValue() : right.getDoubleValue();
            return Value(num1 > num2);
        }
        case LESS_THAN: {
            if (left.isBoolValue() || right.isBoolValue())
                throw string("The '<' operator cannot be applied to booleans.\n");
            double num1 = left.isIntValue() ? left.getIntValue() : left.getDoubleValue();
            double num2 = right.isIntValue() ? right.getIntValue() : right.getDoubleValue();
            return Value(num1 < num2);
        }
        case EQUALS: {
            // If both left and right are boolean, it's okay.
            if (left.isBoolValue() && right.isBoolValue())
                return Value(left.getBoolValue() == right.getBoolValue());

            // If one operand is boolean and the other is numeric, can't apply operator.
            if (left.isBoolValue() || right.isBoolValue())
                throw string("The '==' operator cannot be applied to operands of different types.\n");

            // Both are numeric operands.
            return Value((left.isIntValue() ? left.getIntValue() : left.getDoubleValue()) ==
                         (right.isIntValue() ? right.getIntValue() : right.getDoubleValue()));
        }
        default: {
            throw string("Unsupported operator.\n");
        }
    }


}
