#ifndef STRING_CALCULATOR_H
#define STRING_CALCULATOR_H

#include <string>
#include <vector>

class StringCalculator {
public:
    int Add(const std::string& numbers);

private:
    std::string ExtractDelimiter(std::string& numbers);
    std::vector<std::string> Split(const std::string& input, const std::string& delimiter);
    std::vector<int> ParseNumbers(const std::string& numbers, const std::string& delimiter);
    void CheckNegatives(const std::vector<int>& nums);
};

#endif  // STRING_CALCULATOR_H
