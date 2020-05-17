#ifndef SIMPLE_INTERPRETER_EXPRESSIONEVALUATOR_H
#define SIMPLE_INTERPRETER_EXPRESSIONEVALUATOR_H

#include <string>

using namespace std;

class ExpressionEvaluator {
private:
    //TODO: The required stacks.
public:
    ExpressionEvaluator(string expression);
    double evaluate(); // For invalid expressions, throw an exception.
};


#endif //SIMPLE_INTERPRETER_EXPRESSIONEVALUATOR_H
