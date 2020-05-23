#include "Interpretation.h"
#include "Parser/Parser.h"

void Interpretation::process(string line) {
    Statement *statement = Parser::parse(line, &variables);
    if (statement != NULL) {
        statement->execute();
    }

}

unordered_map<string, double> Interpretation::getVariables() const {
    return variables;
}
