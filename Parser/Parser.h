//
// Created by Youssef on 16/05/2020.
//

#ifndef SIMPLE_INTERPRETER_PARSER_H
#define SIMPLE_INTERPRETER_PARSER_H

#include <string>
#include "../Statements/Statement.h"

using namespace std;

class Parser {
public:
    static Statement *parse(string statement);
    /*
     * The `parse` method should validate the provided statement by using the StatementValidator.
     * After knowing its type, return a pointer to object of Statement.
     * If the statement is INVALID, return NULL.
     * The Parser behaves like a factory of Statement.
     */

};


#endif //SIMPLE_INTERPRETER_PARSER_H
