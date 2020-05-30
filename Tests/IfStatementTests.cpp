#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "../Statements/IfStatement.h"
#include "../Parser/Parser.h"

TEST(IFStatementsTest, assumedValue) {
    auto *map = new unordered_map<string, Value>;

    IfStatement ifStatement("if 3 > 2 : x = 3", map);
    ASSERT_EQ(ifStatement.getConditionExpression(), "3 > 2 ");
    if(ifStatement.getConditionedStatement() != nullptr) {
        ASSERT_EQ(ifStatement.getConditionedStatement()->getStatement(), "x = 3");
    }

    IfStatement ifStatement2("if 6>5 : if 6 == 6 : x = 3", map);
    ASSERT_EQ(ifStatement2.getConditionExpression(), "6>5 ");
    if(ifStatement2.getConditionedStatement() != nullptr) {
        ASSERT_EQ(ifStatement2.getConditionedStatement()->getStatement(), "if 6 == 6 : x = 3");
    }

    try{ IfStatement ifStatement1("Label A:if x>5 : x = 6", map); }
        catch (string ex) { ASSERT_EQ(ex, "The given statement is not an if statement.\n");}

    try { IfStatement ifStatement("if asdffafa : adsfasff", map); }
    catch (string string1) { ASSERT_EQ(string1, "Not valid conditioned statement\n"); }

    try{ IfStatement ifStatement3("if x_if:: x = 3", map); }
        catch (string ex) { ASSERT_EQ(ex, "Not valid conditioned statement\n");}

    //NOTE: parser test
    try{ Parser::parse("adsfasff", map);}
    catch (string ex) { ASSERT_EQ(ex, "Unexpected StatementType.\n"); }

}