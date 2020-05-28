#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "../Statements/IfStatement.h"
#include "../Parser/Parser.h"

TEST(IFStatementsTest, assumedValue) {
    auto *map = new unordered_map<string, Value>;

    try {
        IfStatement ifStatement("if asdffafa : adsfasff", map);
        ASSERT_EQ(ifStatement.getConditionExpression(), "asdffafa ");
        if(ifStatement.getConditionedStatement() != nullptr){
            ASSERT_EQ(ifStatement.getConditionedStatement()->getStatement(), "adsfasff");
        }
    } catch (string string1) {
        cout << string1;
    }

    try{ Parser::parse("adsfasff", map);}
        catch (string ex) { ASSERT_EQ(ex, "Unexpected StatementType.\n"); }

    try{ IfStatement ifStatement1("Label A:if x>5 : x = 6", map); }
        catch (string ex) { ASSERT_EQ(ex, "The given statement is not an if statement.\n");}


    try { IfStatement ifStatement2("if x>5 : if x == 6 : x = y + 3", map); }
        catch (...) { cout << "\"if x>5 : if x == 6 : x = y + 3\" true if statement" << endl;}

    try{ IfStatement ifStatement3("if x_if:: x = 3", map); }
        catch (...) { cout << "\"if x_if:: x = 3\" should be true if statement" << endl ;}
}