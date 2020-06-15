#ifndef SIMPLE_INTERPRETER_GOTOSTATEMENT_H
#define SIMPLE_INTERPRETER_GOTOSTATEMENT_H

#include <string>
#include "Statement.h"

using namespace std;

class GotoStatement : public Statement {
private:
    string labelName;
    static list<Statement *> *fileData;
    static unordered_map<string, list<Statement *>::iterator> *labelData;
public:
    GotoStatement(string statement, unordered_map<string, Value> *variables);

    void execute();

    static void setFileData(list<Statement *> *fileData);

    static void setLabelData(unordered_map<string, list<Statement *>::iterator> *labelData);

private:
    string checkGoto(string statement);

};


#endif //SIMPLE_INTERPRETER_GOTOSTATEMENT_H
