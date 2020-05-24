#ifndef SIMPLE_INTERPRETER_PARSER_H
#define SIMPLE_INTERPRETER_PARSER_H

#include <string>
#include "../Statements/Statement.h"
#include "StatementValidator.h"
#include "../Statements/AssignmentStatement.h"
#include "../Statements/IfStatement.h"
#include "../Evaluation/Value.h"


using namespace std;

class Parser {
public:
    /*
     * The `parse` method should validate the provided statement by using the StatementValidator.
     * After knowing its type, return a pointer to object of Statement.
     * If the statement is INVALID, return NULL.
     * The Parser behaves like a factory of Statement.
     */
    static Statement *parse(string statement, unordered_map<string, Value> *map);

};


#endif //SIMPLE_INTERPRETER_PARSER_H
