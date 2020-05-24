#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "../Statements/IfStatement.h"

TEST(IFStatementsTest, assumedValue){
    ASSERT_FALSE(IfStatement::isValid("sdsdfsdf if : "));
    ASSERT_FALSE(IfStatement::isValid("if: "));
    ASSERT_TRUE(IfStatement::isValid("   if : "));
}