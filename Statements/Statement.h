#ifndef SIMPLE_INTERPRETER_STATEMENT_H
#define SIMPLE_INTERPRETER_STATEMENT_H
#include <string>

using namespace std;

class Statement {
private:
    string statement;

public:
    Statement(string statement);
    static bool isValid(string statement);
    virtual void execute() = 0;
};


#endif //SIMPLE_INTERPRETER_STATEMENT_H