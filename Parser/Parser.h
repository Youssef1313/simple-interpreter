#ifndef SIMPLE_INTERPRETER_PARSER_H
#define SIMPLE_INTERPRETER_PARSER_H

#include <string>
#include "../Statements/Statement.h"
#include "../Statements/AssignmentStatement.h"
#include "../Statements/IfStatement.h"
#include "../Evaluation/Value.h"
#include "../Statements//GotoStatement.h"


using namespace std;

class Parser {
public:
    /*
     *`parse` method validate provided statement using try-catch.
     * It will try to instantiate new statement and it will depend on
     * its throw which will determine if it is from this particular type
     * of statement or not.
     *
     * Parser behaves like a factory of Statement.
     */
    static Statement *parse(string statement, unordered_map<string, Value> *map);

};


#endif //SIMPLE_INTERPRETER_PARSER_H
