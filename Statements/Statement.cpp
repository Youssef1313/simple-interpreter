#include "Statement.h"

Statement::Statement(string statement, unordered_map<string, double> *variables) {
    this->statement = statement;
    this->variables = variables;
}
