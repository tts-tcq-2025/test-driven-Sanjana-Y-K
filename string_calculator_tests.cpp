#include <gtest/gtest.h>
#include "string_calculator.cpp"
TEST(TestStringCalculator, EmptyStringReturnsZero) {
    // Arrange
    std::string input = "";
    int expected_value = 0;

    // Act
    int actual_value = add(input);

    // Assert
    EXPECT_EQ(actual_value, expected_value);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
