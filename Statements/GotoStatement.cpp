//
// Created by Zayton on 5/28/2020.
//

#include "GotoStatement.h"
#include "../HelperMethods.h"

list<Statement *> *GotoStatement::fileData;
unordered_map<string, list<Statement *>::iterator> *GotoStatement::labelData;

GotoStatement::GotoStatement(string statement, unordered_map<string, Value> *variables) : Statement(statement,
                                                                                                    variables) {
    labelName = checkGoto(statement);
}

void GotoStatement::execute() {
    //cout << "Executing goto\n";
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
    int gotoIndex = 0;
    string variable = "";
    if (length > 5 && statement[0] == 'g' && statement[1] == 'o' && statement[2] == 't' && statement[3] == 'o'
        && statement[4] == ' ') {
        gotoIndex = 4;
    } else {
        throw string("Not goto statement");
    }
    while (gotoIndex < length && statement[gotoIndex] == ' ') gotoIndex++;
    while (gotoIndex < length && HelperMethods::isValidCharacter(statement[gotoIndex])) {
        variable.push_back(statement[gotoIndex]);
        gotoIndex++;
    }
    while (gotoIndex < length && statement[gotoIndex] == ' ') gotoIndex++;

    if (gotoIndex != length) {
        throw string("Invalid");
    }

    // goto     la bel
    // 012345
    // variable = statement.substr(gotoIndex + 1, length - gotoIndex - 1);

    // variable.erase(remove(variable.begin(), variable.end(), ' '), variable.end());
    return variable;
}
