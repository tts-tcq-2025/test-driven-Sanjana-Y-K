#include "string_calculator.h"
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>
#include <regex>
#include <algorithm>

std::string EscapeRegex(const std::string& delimiter) {
  // Escape special regex characters
  std::string escaped;
  for (char ch : delimiter) {
    if (std::string("[](){}.*+?^$|\\").find(ch) != std::string::npos) {
      escaped += "\\";
    }
    escaped += ch;
  }
  return escaped;
}

int StringCalculator::Add(const std::string& numbers) {
  if (numbers.empty()) return 0;
  std::string input = numbers;
  std::string delimiter_regex = ExtractDelimiter(input);
  auto parsedNumbers = ParseNumbers(input, delimiter_regex);
  CheckNegatives(parsedNumbers);
  int sum = 0;
  for (int num : parsedNumbers) {
    if (num <= 1000) sum += num;
  }
  return sum;
}

std::string StringCalculator::ExtractDelimiter(std::string& numbers) {
  // Default for comma and newline: "[,\n]"
  if (numbers.rfind("//", 0) == 0) {
    auto pos = numbers.find('\n');
    std::string delimiters = numbers.substr(2, pos - 2);
    numbers = numbers.substr(pos + 1);
    // Multi-char delimiter in brackets
    if (!delimiters.empty() && delimiters.front() == '[' &&
        delimiters.back() == ']') {
      std::string delimiter = delimiters.substr(1, delimiters.size() - 2);
      return EscapeRegex(delimiter);
    } else {
      return EscapeRegex(delimiters);
    }
  }
  return "[,\n]";
}

std::vector<std::string> StringCalculator::Split(
    const std::string& input, const std::string& delimiter_regex) {
  std::vector<std::string> tokens;
  std::regex reg(delimiter_regex);
  std::sregex_token_iterator iter(input.begin(), input.end(), reg, -1);
  std::sregex_token_iterator end;
  for (; iter != end; ++iter) {
    if (!iter->str().empty()) tokens.push_back(iter->str());
  }
  return tokens;
}

std::vector<int> StringCalculator::ParseNumbers(
    const std::string& numbers, const std::string& delimiter_regex) {
  // If default delimiter: "[,\n]", use as a regex class.
  std::string regex_expr;
  if (delimiter_regex == "[,\n]") {
    regex_expr = "[,\n]";
  } else {
    regex_expr = delimiter_regex;
  }
  auto tokens = Split(numbers, regex_expr);
  std::vector<int> nums;
  for (const auto& tok : tokens) {
    if (!tok.empty()) {
      nums.push_back(std::stoi(tok));
    }
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
    oss << "negatives not allowed: ";
    for (size_t i = 0; i < negatives.size(); ++i) {
      oss << (i > 0 ? ", " : "") << negatives[i];
    }
    throw std::invalid_argument(oss.str());
  }
}
