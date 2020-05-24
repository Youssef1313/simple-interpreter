#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "../Statements/IfStatement.h"
#include "../Parser/Parser.h"

TEST(IFStatementsTest, assumedValue){
    auto *map = new unordered_map<string, Value>;
    try{
        IfStatement ifStatement("   if asdffafa : adsfasff", map);
        ASSERT_EQ(ifStatement.getConditionExpression(), "asdffafa ");
    } catch (string string1) {
        cout << string1 ;
    }
    ASSERT_FALSE(IfStatement::isValid("sdsdfsdf if : "));
    ASSERT_FALSE(IfStatement::isValid("if: "));
    ASSERT_TRUE(IfStatement::isValid("   if : "));
    ASSERT_TRUE(IfStatement::isValid("   if asdffafa : adsfasffv"));
    ASSERT_EQ(Parser::parse("adsfasff", map), (Statement*)NULL);
    //ASSERT_EQ(ifStatement.getConditionedStatement(), (Statement*)NULL);


}