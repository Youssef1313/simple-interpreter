#include "GotoStatement.h"
#include "../Utils/Constants.h"
#include "../Utils/HelperMethods.h"

list<Statement *> *GotoStatement::fileData;
unordered_map<string, list<Statement *>::iterator> *GotoStatement::labelData;

GotoStatement::GotoStatement(string statement, unordered_map<string, Value> *variables) : Statement(statement,
                                                                                                    variables) {
    labelName = checkGoto(statement);
}

void GotoStatement::execute() {
    auto it = labelData->find(labelName);
    if (it == labelData->end())
        throw string("Label not found");
    auto statementIT = it->second;
    for (; statementIT != fileData->end(); statementIT++) {
        (*statementIT)->execute();
        if (typeid((*statementIT)) == typeid(GotoStatement))
            break;

    }
}

void GotoStatement::setFileData(list<Statement *> *fileData) {
    GotoStatement::fileData = fileData;
}

void GotoStatement::setLabelData(unordered_map<string, list<Statement *>::iterator> *labelData) {
    GotoStatement::labelData = labelData;
}


string GotoStatement::checkGoto(string statement) {
    int length = statement.length();
    if (length <= (int) GOTO_KEYWORD.length() + 1 || !HelperMethods::stringStartsWith(statement, GOTO_KEYWORD) ||
        !isspace(statement[GOTO_KEYWORD.length()])) {
        throw string("Not a goto statement.");
    }

    int gotoIndex = GOTO_KEYWORD.length() + 1;
    string variable = "";
    HelperMethods::skipWhitespaces(statement, &gotoIndex);

    while (gotoIndex < length && HelperMethods::isValidCharacter(statement[gotoIndex])) {
        variable.push_back(statement[gotoIndex++]);
    }
    HelperMethods::skipWhitespaces(statement, &gotoIndex);

    if (gotoIndex != length) {
        throw string("Invalid");
    }

    return variable;
}
