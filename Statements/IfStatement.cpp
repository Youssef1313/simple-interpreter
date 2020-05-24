#include "IfStatement.h"
#include "../Parser/Parser.h"
#include <bits/stdc++.h>


bool IfStatement::isValid(const string& statement) {
    int ifCount, colonCount, if_Pos, colon_Pos;// counters for ifs and colons, they must equal each other.
    ifCount = colonCount = if_Pos = colon_Pos = 0;
    const string ifSub = "if ";
    const string colonSub = ": ";
    int i = 0;
    while(statement[i] == ' ') i++;//skip spaces
    string no_spaces_statement = statement.substr(i);
    if(no_spaces_statement.find(ifSub, 0)) return false; //if there any characters instead of
    while((unsigned int)(if_Pos = no_spaces_statement.find(ifSub, if_Pos)) != (unsigned int)std::string::npos){
        ifCount++; if_Pos += ifSub.size();
        if ((unsigned int)(colon_Pos = no_spaces_statement.find(colonSub, colon_Pos)) != (unsigned int)std::string::npos){
            colonCount++; colon_Pos += colonSub.size();
        }
    }
    if(!ifCount) return false;
    return ifCount == colonCount;
}

void IfStatement::execute() {
        //TODO: call evaluator to check if statement is true, then check this second if
        if(conditioned_Statement) conditioned_Statement->execute();
}

IfStatement::IfStatement(const string &statement, unordered_map<string, Value> *variables) : Statement(statement,
                                                                                                        variables) {
    int colon_Pos, if_Pos;
    string colonSub = ": ", ifSub = "if ";
    colon_Pos = statement.find(colonSub);
    if_Pos = statement.find(ifSub);
    conditionExpression = statement.substr(if_Pos + ifSub.size(), colon_Pos-1);
    conditioned_Statement = Parser::parse(statement.substr(colon_Pos + colonSub.size()), variables);
}

