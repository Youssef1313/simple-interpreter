#include "Parser.h"
#include "../Evaluation/Value.h"

Statement *Parser::parse(string statement, unordered_map<string, Value> *map) {
    try { return new AssignmentStatement(statement, map); } catch (string ex) {}
    try { return new IfStatement(statement, map); } catch (string ex) {}
    try {return new GotoStatement(statement,map);}catch(string ex) {}
    cout << "Invalid::" << statement << "::\n";
    throw string("Unexpected StatementType.\n");

}
