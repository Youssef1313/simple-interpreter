#include <bits/stdc++.h>
#include "IfStatement.h"
#include "../Parser/Parser.h"
#include "../Evaluation/ExpressionEvaluator.h"

int IfStatement::getColonPos() {
    // if "if" isn't at first then this statement isn't if statement.
    int ifPos = 0;
    for(; ifPos < (int)ifSub.size(); ++ifPos){}
    if(ifPos == (int) ifSub.size()){
        int colon_Pos;
        if ((unsigned int) (colon_Pos = statement.find(colonSub, ifSub.size())) !=
            (unsigned int) std::string::npos && !ifPos) {
            return colon_Pos;
        }
    }
    throw string("The given statement is not an if statement.\n");
}

void IfStatement::execute() {
    ExpressionEvaluator evaluator(conditionExpression, *variables);
    Value value = evaluator.evaluate();
    if (value.isBoolValue()) {
        if (value.getBoolValue())
            conditioned_Statement->execute();
    } else {
        throw string("if condition evaluate must return a boolean value.\n");
    }
}

IfStatement::IfStatement(const string &statement, unordered_map<string, Value> *variables) : Statement(statement,
                                                                                                      variables) {
    int colon_Pos = getColonPos();
    conditionExpression = statement.substr(ifSub.size(), colon_Pos - ifSub.size() );
    try{
        int i = colon_Pos + colonSub.size();
        while (statement[i] ==  ' ') i++;
        conditioned_Statement = Parser::parse(statement.substr(i), variables);
    } catch (string ex) {
        throw string("Not valid conditioned statement\n");
    }
}

const string &IfStatement::getConditionExpression() const {
    return conditionExpression;
}

Statement *IfStatement::getConditionedStatement() const {
    return conditioned_Statement;
}

