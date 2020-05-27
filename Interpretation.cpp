#include "Interpretation.h"
#include "Parser/Parser.h"

void Interpretation::process(string line) {
    // Ignore leading whitespaces.
    int startingIndex = 0;
    while (line[startingIndex] == ' ') startingIndex++;

    // Read until a comment is encountered.
    int endingIndex = startingIndex;
    while (line[endingIndex] != '#') endingIndex++;

    // If line is empty, return.
    if (startingIndex == endingIndex) return;

    // Get the line without the leading whitespaces and without the comment.
    line = line.substr(startingIndex, endingIndex - startingIndex);

    Statement *statement = Parser::parse(line, &variables);
    if (statement != NULL) {
        statement->execute();
    }

}

unordered_map<string, Value> Interpretation::getVariables() const {
    return variables;
}
