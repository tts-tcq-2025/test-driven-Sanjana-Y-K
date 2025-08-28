#include "string_calculator.h"
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>
#include <regex>
#include <algorithm>

int StringCalculator::Add(const std::string& numbers) {
    if (numbers.empty()) return 0;

    std::string input = numbers;
    std::string delimiter = ExtractDelimiter(input);

    auto parsedNumbers = ParseNumbers(input, delimiter);
    CheckNegatives(parsedNumbers);

    int sum = 0;
    for (int num : parsedNumbers) {
        if (num <= 1000) sum += num;
    }
    return sum;
}

std::string StringCalculator::ExtractDelimiter(std::string& numbers) {
    if (numbers.rfind("//", 0) == 0) {
        auto pos = numbers.find("\n");
        std::string delimiter = numbers.substr(2, pos - 2);
        numbers = numbers.substr(pos + 1);
        return delimiter;
    }
    return "[,\n]"; // regex class: split by comma or newline
}

std::vector<std::string> StringCalculator::Split(const std::string& input, const std::string& delimiter) {
    std::vector<std::string> tokens;

    std::regex reg(delimiter);
    std::sregex_token_iterator iter(input.begin(), input.end(), reg, -1);
    std::sregex_token_iterator end;

    for (; iter != end; ++iter) {
        if (!iter->str().empty()) tokens.push_back(iter->str());
    }
    return tokens;
}

std::vector<int> StringCalculator::ParseNumbers(const std::string& numbers, const std::string& delimiter) {
    auto tokens = Split(numbers, delimiter);
    std::vector<int> nums;

    for (const auto& tok : tokens) {
        nums.push_back(std::stoi(tok));
    }
    return nums;
}

void StringCalculator::CheckNegatives(const std::vector<int>& nums) {
    std::vector<int> negatives;
    for (int n : nums) {
        if (n < 0) negatives.push_back(n);
    }
    if (!negatives.empty()) {
        std::ostringstream oss;
        oss << "negatives not allowed:";
        for (size_t i = 0; i < negatives.size(); ++i) {
            oss << (i == 0 ? " " : ", ") << negatives[i];
        }
        throw std::invalid_argument(oss.str());
    }
}
