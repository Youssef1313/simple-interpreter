#include "Interpretation.h"
#include "Parser/Parser.h"
#include "Utils/HelperMethods.h"

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
            throw string("The label Variable has been defined before");
        }
    }

//    if (typeid(*statement) == typeid(GotoStatement)) {
//        ((GotoStatement *) statement)->setFileData(&fileData);
//        ((GotoStatement *) statement)->setLabelData(&labelData);
//    }
    statement->execute();


}

string Interpretation::checkLabel(string statement, string *labelName) {
    int length = statement.length();
    string variable;
    if (length <= 5 || !HelperMethods::stringStartsWith(statement, "label") || !isspace(statement[5])) {
        return statement;
    }

    int index = 6;
    HelperMethods::skipWhitespaces(statement, &index);

    while (HelperMethods::isValidCharacter(statement[index])) {
        variable.push_back(statement[index]);
        index++;
    }
    *labelName = variable;

    HelperMethods::skipWhitespaces(statement, &index);

    if (index == length || statement[index] != ':') throw string("Invalid label.");
    index++;
    HelperMethods::skipWhitespaces(statement, &index);

    if (index == length) throw string("Empty label.");
    return statement.substr(index);

}

unordered_map<string, Value> Interpretation::getVariables() const {
    return variables;
}

Interpretation::Interpretation() {
    GotoStatement::setLabelData(&labelData);
    GotoStatement::setFileData(&fileData);
}
