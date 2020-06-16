#include "Interpretation.h"
#include "Parser/Parser.h"
#include "Utils/HelperMethods.h"
#include "Utils/Constants.h"

void Interpretation::process(string line) {
    // Ignore leading whitespaces.
    string labelName = "";
    char commentSymbol = '#';
    int startingIndex = 0;
    while (isspace(line[startingIndex])) startingIndex++;
    // Read until a comment is encountered.
    int endingIndex = startingIndex;
    while (endingIndex < (int) line.size() && line[endingIndex] != commentSymbol) endingIndex++;

    // If line is empty, return.
    if (startingIndex == endingIndex) return;

    // Get the line without the leading whitespaces and without the comment.
    line = line.substr(startingIndex, endingIndex - startingIndex);
    line = checkLabel(line, &labelName);
    Statement *statement = Parser::parse(line, &variables);

    fileData.push_back(statement);
    if ((labelName).length() != 0) {
        auto iter = labelData.find(labelName);
        if (iter == labelData.end()) {
            list<Statement *>::iterator it = --fileData.end();
            labelData.insert(pair<string, list<Statement *>::iterator>(labelName, it));
        } else {
            throw string("The label Variable has been defined before.");
        }
    }

    statement->execute();

}

string Interpretation::checkLabel(string statement, string *labelName) {
    int length = statement.length();

    // Make sure statement starts with "label" and followed by a whitespace before continuing.
    if (!HelperMethods::stringStartsWith(statement, LABEL_KEYWORD) || !isspace(statement[LABEL_KEYWORD.length()])) {
        return statement;
    }

    // Skip all whitespaces after "label "
    int index = LABEL_KEYWORD.length() + 1;
    HelperMethods::skipWhitespaces(statement, &index);

    // After "label " and any whitespaces, this is the start of the label name. Parse while the char is valid.
    string variable;
    while (HelperMethods::isValidCharacter(statement[index])) {
        variable.push_back(statement[index]);
        index++;
    }
    *labelName = variable;

    // Skip whitespaces, if any.
    HelperMethods::skipWhitespaces(statement, &index);

    // After label LABEL_NAME and any whitespaces, the ":" should be expected.
    if (index == length || statement[index] != ':') throw string("Invalid label.");

    // After the label name, ignore any whitespaces.
    index++;
    HelperMethods::skipWhitespaces(statement, &index);

    // At this point, the index should be at the beginning of the real statement. (label LABEL_NAME: real_statement)
    if (index == length) throw string("Expected a statement in the same line with label declaration.");
    return statement.substr(index);

}

unordered_map<string, Value> Interpretation::getVariables() const {
    return variables;
}

Interpretation::Interpretation() {
    GotoStatement::setLabelData(&labelData);
    GotoStatement::setFileData(&fileData);
}
