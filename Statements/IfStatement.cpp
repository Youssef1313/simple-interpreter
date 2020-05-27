#include "IfStatement.h"
#include "../Parser/Parser.h"
#include "../Evaluation/ExpressionEvaluator.h"
#include <bits/stdc++.h>


bool IfStatement::isValid(const string &statement) {
    int ifCount, colonCount, if_Pos, colon_Pos;// counters for ifs and colons, they must equal each other.
    ifCount = colonCount = if_Pos = colon_Pos = 0;
    const string ifSub = "if ";
    const string colonSub = ": ";

    /* if "if" isn't at first then garbage was written so statement isn't valid */
    if (statement.find(ifSub, 0)) return false;

    while ((unsigned int) (if_Pos = statement.find(ifSub, if_Pos)) != (unsigned int) std::string::npos) {
        ifCount++;
        if_Pos += ifSub.size();
        if ((unsigned int) (colon_Pos = statement.find(colonSub, colon_Pos)) !=
            (unsigned int) std::string::npos) {
            colonCount++;
            colon_Pos += colonSub.size();
        }
    }
    if (!ifCount) return false;
    return ifCount == colonCount;
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
    int colon_Pos, if_Pos;
    string colonSub = ": ", ifSub = "if ";
    colon_Pos = statement.find(colonSub);
    if_Pos = statement.find(ifSub);
    int start = if_Pos + ifSub.size();
    conditionExpression = statement.substr(start, colon_Pos - start);
    conditioned_Statement = Parser::parse(statement.substr(colon_Pos + colonSub.size()), variables);
    if (!conditioned_Statement)
        throw string("Not valid conditioned statement\n");
}

const string &IfStatement::getConditionExpression() const {
    return conditionExpression;
}

Statement *IfStatement::getConditionedStatement() const {
    return conditioned_Statement;
}

