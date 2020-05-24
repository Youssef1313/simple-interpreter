#include <math.h>
#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "../Evaluation/ExpressionEvaluator.h"
#include "../Evaluation/Value.h"

TEST(EvaluationTests, EvaluationTest) {
    unordered_map<string, Value> map;

    ASSERT_EQ(ExpressionEvaluator("4", map).evaluate().toString(), to_string(4));
    ASSERT_EQ(ExpressionEvaluator("(4)", map).evaluate().toString(), to_string((4)));
    ASSERT_EQ(ExpressionEvaluator("+4", map).evaluate().toString(), to_string(+4));
    ASSERT_EQ(ExpressionEvaluator("(+4)", map).evaluate().toString(), to_string((+4)));
    ASSERT_EQ(ExpressionEvaluator("-4", map).evaluate().toString(), to_string(-4));
    ASSERT_EQ(ExpressionEvaluator("(-4)", map).evaluate().toString(), to_string((-4)));
    ASSERT_EQ(ExpressionEvaluator("(--4)", map).evaluate().toString(), to_string(- -4));
    ASSERT_EQ(ExpressionEvaluator("(---4)", map).evaluate().toString(), to_string((- - -4)));
    ASSERT_EQ(ExpressionEvaluator("5--(--4)", map).evaluate().toString(), to_string(5 - -(- -4)));
    ASSERT_EQ(ExpressionEvaluator("5+(+4)", map).evaluate().toString(), to_string(5 + (+4)));
    ASSERT_EQ(ExpressionEvaluator("5++4", map).evaluate().toString(), to_string(5 + +4));
    ASSERT_EQ(ExpressionEvaluator("5+4", map).evaluate().toString(), to_string(5 + 4));
    ASSERT_EQ(ExpressionEvaluator("5---3", map).evaluate().toString(), to_string(5 - - -3));
    ASSERT_EQ(ExpressionEvaluator("5----3", map).evaluate().toString(), to_string(5 - - - -3));
    ASSERT_EQ(ExpressionEvaluator("5+(-2)", map).evaluate().toString(), to_string(5 + (-2)));
    ASSERT_EQ(ExpressionEvaluator("(5*3+-7*2+-0.5*10)/(6*2+-2.5*4)^2", map).evaluate().toString(),
              to_string((5 * 3 + -7 * 2 + -0.5 * 10) / pow((6 * 2 + -2.5 * 4), 2)));
    ASSERT_EQ(ExpressionEvaluator("(-1 + --5)*5/6+(2*-5)", map).evaluate().toString(),
              to_string((-1 + - -5) * 5 / 6 + (2 * -5)));
    ASSERT_EQ(ExpressionEvaluator("(--.5)*(-(-0.5)) + +10 / -(2)", map).evaluate().toString(),
              to_string((- -.5) * (-(-0.5)) + +10 / -(2)));
    ASSERT_EQ(ExpressionEvaluator("(--.5)*(-(-0.5)) + +10 / -(--2)", map).evaluate().toString(),
              to_string((- -.5) * (-(-0.5)) + +10 / -(- -2)));
    ASSERT_EQ(ExpressionEvaluator("5 - -(-3- +(2))", map).evaluate().toString(), to_string(5 - -(-3 - +(2))));
    ASSERT_EQ(ExpressionEvaluator("(-1 + - - --5) * 5 / 6 + (2* --5)", map).evaluate().toString(),
              to_string((-1 + - - - -5) * 5 / 6 + (2 * - -5)));
    ASSERT_EQ(ExpressionEvaluator("5 + - - 7", map).evaluate().toString(), to_string(5 + - -7));
    ASSERT_EQ(ExpressionEvaluator("7 - (--5)", map).evaluate().toString(), to_string(7 - (- -5)));
    ASSERT_EQ(ExpressionEvaluator("-2-3+3", map).evaluate().toString(), to_string(-2 - 3 + 3));
    ASSERT_EQ(ExpressionEvaluator("1 -- (-(-2 - 3 + 3)) * (-((2 + 2) - 3))", map).evaluate().toString(),
              to_string(1 - -(-(-2 - 3 + 3)) * (-((2 + 2) - 3))));
    ASSERT_EQ(ExpressionEvaluator("-+-3", map).evaluate().toString(), to_string(- + -3));
    ASSERT_EQ(ExpressionEvaluator("+-+3", map).evaluate().toString(), to_string(+ - +3));
    ASSERT_EQ(ExpressionEvaluator("+-3", map).evaluate().toString(), to_string(+ -3));
    ASSERT_EQ(ExpressionEvaluator("-+3", map).evaluate().toString(), to_string(- +3));
    ASSERT_EQ(ExpressionEvaluator("2^1^3", map).evaluate().toString(), to_string(pow(2, pow(1, 3))));
    ASSERT_EQ(ExpressionEvaluator("-2^3", map).evaluate().toString(), to_string(-pow(2, 3)));
    ASSERT_EQ(ExpressionEvaluator("-2^2", map).evaluate().toString(), to_string(-pow(2, 2)));
    ASSERT_EQ(ExpressionEvaluator("(-2)^2", map).evaluate().toString(), to_string(pow(-2, 2)));
/*
 * To be added.
 * 5 + 7 ( )                                -> ERROR.
 * 5 5 + 5 -                                -> ERROR.
 */
}