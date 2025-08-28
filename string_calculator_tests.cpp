#include "./string_calculator.h"
#include <gtest/gtest.h>

TEST(StringCalculatorTest, EmptyInput) {
    StringCalculator calc;
    EXPECT_EQ(calc.Add(""), 0);
}

TEST(StringCalculatorTest, SingleNumber) {
    StringCalculator calc;
    EXPECT_EQ(calc.Add("1"), 1);
}

TEST(StringCalculatorTest, TwoNumbers) {
    StringCalculator calc;
    EXPECT_EQ(calc.Add("1,2"), 3);
}

TEST(StringCalculatorTest, UnknownAmountOfNumbers) {
    StringCalculator calc;
    EXPECT_EQ(calc.Add("1,2,3,4,5"), 15);
}

TEST(StringCalculatorTest, NewLineDelimited) {
    StringCalculator calc;
    EXPECT_EQ(calc.Add("1\n2,3"), 6);
}

TEST(StringCalculatorTest, CustomDelimiter) {
    StringCalculator calc;
    EXPECT_EQ(calc.Add("//;\n1;2"), 3);
}

TEST(StringCalculatorTest, ThrowsOnNegatives) {
    StringCalculator calc;
    EXPECT_THROW({
        try {
            calc.Add("1,-2,-3");
        } catch (const std::invalid_argument& e) {
            EXPECT_STREQ(e.what(), "negatives not allowed: -2, -3");
            throw;
        }
    }, std::invalid_argument);
}

TEST(StringCalculatorTest, IgnoreNumbersGreaterThan1000) {
    StringCalculator calc;
    EXPECT_EQ(calc.Add("2,1001"), 2);
}

TEST(StringCalculatorTest, DelimitersOfAnyLength) {
    StringCalculator calc;
    EXPECT_EQ(calc.Add("//[***]\n12***3"), 15);       
        
}
