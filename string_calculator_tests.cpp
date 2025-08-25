#include "string_calculator.h"
#include <cassert>
#include <iostream>

void TestEmptyStringReturnsZero() {
    StringCalculator calc;
    assert(calc.Add("") == 0);
}

void TestSingleNumberReturnsItself() {
    StringCalculator calc;
    assert(calc.Add("1") == 1);
}

void TestTwoNumbersCommaSeparated() {
    StringCalculator calc;
    assert(calc.Add("1,2") == 3);
}

void TestUnknownAmountOfNumbers() {
    StringCalculator calc;
    assert(calc.Add("1,2,3,4,5") == 15);
}

void TestNewLineDelimiter() {
    StringCalculator calc;
    assert(calc.Add("1\n2,3") == 6);
}

void TestCustomSingleCharDelimiter() {
    StringCalculator calc;
    assert(calc.Add("//;\n1;2") == 3);
}

void TestNegativeNumbersThrowException() {
    StringCalculator calc;
    try {
        calc.Add("1,-2,-3");
        assert(false); // Should not reach here
    } catch (const NegativeNumberException& e) {
        std::string expected = "negatives not allowed: -2, -3";
        assert(std::string(e.what()) == expected);
    }
}

void TestIgnoreNumbersGreaterThan1000() {
    StringCalculator calc;
    assert(calc.Add("2,1001") == 2);
}

void TestDelimitersOfAnyLength() {
    StringCalculator calc;

    assert(calc.Add("//[***]\n12***3") == 15);
}

int main() {
    TestEmptyStringReturnsZero();
    TestSingleNumberReturnsItself();
    TestTwoNumbersCommaSeparated();
    TestUnknownAmountOfNumbers();
    TestNewLineDelimiter();
    TestCustomSingleCharDelimiter();
    TestNegativeNumbersThrowException();
    TestIgnoreNumbersGreaterThan1000();
    TestDelimitersOfAnyLength();

    std::cout << "All tests passed!\n";
    return 0;
}
