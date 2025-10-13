#include <gtest/gtest.h>
#include <string>
#include "StringCalculator.h"

namespace {
void ExpectNegativeException(const std::string& input, const std::string& expectedMessage) {
  StringCalculator calc;
  try {
    calc.Add(input);
    FAIL() << "Expected exception";
  } catch (const std::runtime_error& e) {
    EXPECT_STREQ(e.what(), expectedMessage.c_str());
  } catch (...) {
    FAIL() << "Expected std::runtime_error";
  }
}
}  // namespace

TEST(StringCalculatorTest, EmptyStringReturnsZero) {
  StringCalculator calc;
  EXPECT_EQ(calc.Add(""), 0);
}

TEST(StringCalculatorTest, SingleNumberReturnsValue) {
  StringCalculator calc;
  EXPECT_EQ(calc.Add("1"), 1);
}

TEST(StringCalculatorTest, TwoNumbersCommaDelimitedReturnsSum) {
  StringCalculator calc;
  EXPECT_EQ(calc.Add("1,2"), 3);
}

TEST(StringCalculatorTest, UnknownAmountOfNumbersCommaDelimited) {
  StringCalculator calc;
  EXPECT_EQ(calc.Add("1,2,3,4"), 10);
}

TEST(StringCalculatorTest, HandlesNewLinesBetweenNumbers) {
  StringCalculator calc;
  EXPECT_EQ(calc.Add("1\n2,3"), 6);
}

TEST(StringCalculatorTest, CustomSingleCharacterDelimiter) {
  StringCalculator calc;
  EXPECT_EQ(calc.Add("//;\n1;2"), 3);
}

TEST(StringCalculatorTest, CustomDelimiterOfAnyLength) {
  StringCalculator calc;
  EXPECT_EQ(calc.Add("//[***]\n1***2***3"), 6);
}

TEST(StringCalculatorTest, NegativeNumberThrowsExceptionSingle) {
  ExpectNegativeException("1,-2,3", "negatives not allowed: -2");
}

TEST(StringCalculatorTest, NegativeNumbersThrowExceptionMultiple) {
  ExpectNegativeException("1,-2,-3", "negatives not allowed: -2, -3");
}

TEST(StringCalculatorTest, NumbersGreaterThan1000AreIgnored) {
  StringCalculator calc;
  EXPECT_EQ(calc.Add("2,1001"), 2);
}

TEST(StringCalculatorTest, DelimiterAnyLengthWithNumbersGreaterThan1000) {
  StringCalculator calc;
  EXPECT_EQ(calc.Add("//[***]\n1***2***1001"), 3);
}

TEST(StringCalculatorTest, MultipleDelimiters) {
  StringCalculator calc;
  EXPECT_EQ(calc.Add("//[*][%]\n1*2%3"), 6);
}
