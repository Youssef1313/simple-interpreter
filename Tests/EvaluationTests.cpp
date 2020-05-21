#include <math.h>
#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "../Evaluation/ExpressionEvaluator.h"

TEST(EvaluationTests, EvaluationTest) {
    unordered_map<string, double> map;

    ASSERT_EQ(ExpressionEvaluator("4", map).evaluate(), 4);
    ASSERT_EQ(ExpressionEvaluator("(4)", map).evaluate(), (4));
    ASSERT_EQ(ExpressionEvaluator("+4", map).evaluate(), +4);
    ASSERT_EQ(ExpressionEvaluator("(+4)", map).evaluate(), (+4));
    ASSERT_EQ(ExpressionEvaluator("-4", map).evaluate(), -4);
    ASSERT_EQ(ExpressionEvaluator("(-4)", map).evaluate(), (-4));
    ASSERT_EQ(ExpressionEvaluator("(--4)", map).evaluate(), - -4);
    ASSERT_EQ(ExpressionEvaluator("(---4)", map).evaluate(), (- - -4));
    ASSERT_EQ(ExpressionEvaluator("5--(--4)", map).evaluate(), 5 - - (- -4));
    ASSERT_EQ(ExpressionEvaluator("5+(+4)", map).evaluate(), 5+(+4));
    ASSERT_EQ(ExpressionEvaluator("5++4", map).evaluate(), 5 + +4);
    ASSERT_EQ(ExpressionEvaluator("5+4", map).evaluate(), 5+4);
    ASSERT_EQ(ExpressionEvaluator("5---3", map).evaluate(), 5 - - -3);
    ASSERT_EQ(ExpressionEvaluator("5----3", map).evaluate(), 5 - - - -3);
    ASSERT_EQ(ExpressionEvaluator("5+(-2)", map).evaluate(), 5+(-2));
    ASSERT_EQ(ExpressionEvaluator("(5*3+-7*2+-0.5*10)/(6*2+-2.5*4)^2", map).evaluate(), (5*3+-7*2+-0.5*10)/pow((6*2+-2.5*4), 2));
    ASSERT_EQ(ExpressionEvaluator("(-1 + --5)*5/6+(2*-5)", map).evaluate(), (-1 + - -5)*5.0/6+(2*-5));
    ASSERT_EQ(ExpressionEvaluator("(--.5)*(-(-0.5)) + +10 / -(2)", map).evaluate(), (- -.5)*(-(-0.5)) + +10 / -(2));
    ASSERT_EQ(ExpressionEvaluator("(--.5)*(-(-0.5)) + +10 / -(--2)", map).evaluate(), (- -.5)*(-(-0.5)) + +10 / -(- -2));
    ASSERT_EQ(ExpressionEvaluator("5 - -(-3- +(2))", map).evaluate(), 5 - -(-3- +(2)));
    ASSERT_EQ(ExpressionEvaluator("(-1 + - - --5) * 5 / 6 + (2* --5)", map).evaluate(), (-1 + - - - -5) * 5.0 / 6 + (2* - -5));
    ASSERT_EQ(ExpressionEvaluator("5 + - - 7", map).evaluate(), 5 + - - 7);
    ASSERT_EQ(ExpressionEvaluator("7 - (--5)", map).evaluate(), 7 - (- -5));
    ASSERT_EQ(ExpressionEvaluator("-2-3+3", map).evaluate(), -2-3+3);
    ASSERT_EQ(ExpressionEvaluator("1 -- (-(-2 - 3 + 3)) * (-((2 + 2) - 3))", map).evaluate(), 1 - - (-(-2 - 3 + 3)) * (-((2 + 2) - 3)));
    ASSERT_EQ(ExpressionEvaluator("-+-3", map).evaluate(), -+-3);
    ASSERT_EQ(ExpressionEvaluator("+-+3", map).evaluate(), +-+3);
    ASSERT_EQ(ExpressionEvaluator("+-3", map).evaluate(), +-3);
    ASSERT_EQ(ExpressionEvaluator("-+3", map).evaluate(), -+3);
    ASSERT_EQ(ExpressionEvaluator("2^1^3", map).evaluate(), 2);
    ASSERT_EQ(ExpressionEvaluator("-2^3", map).evaluate(), -8);
    ASSERT_EQ(ExpressionEvaluator("-2^2", map).evaluate(), -4);
    ASSERT_EQ(ExpressionEvaluator("(-2)^2", map).evaluate(), 4);

/*
 * To be added.
 * 5 + 7 ( )                                -> ERROR.
 * 5 5 + 5 -                                -> ERROR.
 */
}