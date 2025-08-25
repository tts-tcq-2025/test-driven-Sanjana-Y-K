#include "./string_calculator.h"

#include <algorithm>
#include <cctype>
#include <cstdlib>
#include <regex>
#include <sstream>

NegativeNumberException::NegativeNumberException(const std::vector<int>& negatives) {
  message_ = "negatives not allowed: ";
  for (size_t i = 0; i < negatives.size(); ++i) {
    message_ += std::to_string(negatives[i]);
    if (i != negatives.size() - 1) {
      message_ += ", ";
    }
  }
}

const char* NegativeNumberException::what() const noexcept {
  return message_.c_str();
}

int StringCalculator::Add(const std::string& input) {
  if (input.empty()) {
    return 0;
  }

  std::string numbers_part;
  auto delimiters = ParseDelimiters(input, numbers_part);
  auto numbers = ExtractNumbers(numbers_part, delimiters);
  return SumNumbers(numbers);
}

// Parses delimiters and returns the list of delimiters; also sets numbers_part to the actual number string
std::vector<std::string> StringCalculator::ParseDelimiters(const std::string& input, std::string& numbers_part) {
  if (input.size() >= 2 && input[0] == '/' && input[1] == '/') {
    size_t newline_pos = input.find('\n');
    if (newline_pos == std::string::npos) {
      numbers_part = "";
      return {",", "\n"};
    }
    std::string delimiter_part = input.substr(2, newline_pos - 2);
    numbers_part = input.substr(newline_pos + 1);

    if (!delimiter_part.empty() && delimiter_part[0] == '[') {
      return ParseMultiCharDelimiters(delimiter_part);
    }
    return ParseSingleCharDelimiter(delimiter_part);
  } else {
    numbers_part = input;
    return {",", "\n"};
  }
}

// Parses single char delimiter like ";"
std::vector<std::string> StringCalculator::ParseSingleCharDelimiter(const std::string& delimiter_part) {
  if (delimiter_part.empty()) {
    return {","};  // default delimiter
  }
  return {delimiter_part};
}

// Parses multi-character delimiters specified in [delim1][delim2] format
std::vector<std::string> StringCalculator::ParseMultiCharDelimiters(const std::string& delimiter_part) {
  std::vector<std::string> delimiters;
  size_t start = 0;
  while (true) {
    size_t open_bracket = delimiter_part.find('[', start);
    if (open_bracket == std::string::npos) break;
    size_t close_bracket = delimiter_part.find(']', open_bracket);
    if (close_bracket == std::string::npos) break;
    delimiters.push_back(delimiter_part.substr(open_bracket + 1, close_bracket - open_bracket - 1));
    start = close_bracket + 1;
  }
  if (delimiters.empty()) {
    delimiters.push_back(",");  // fallback default
  }
  return delimiters;
}

// Extracts all numbers from the numbers_str using the delimiters
std::vector<int> StringCalculator::ExtractNumbers(const std::string& numbers_str,
                                                  const std::vector<std::string>& delimiters) {
  std::vector<std::string> tokens = SplitNumbers(numbers_str, delimiters);
  std::vector<int> numbers;
  std::vector<int> negatives;

  for (const auto& token : tokens) {
    if (token.empty()) continue;
    try {
      int num = std::stoi(token);
      if (num < 0) {
        negatives.push_back(num);
      } else if (num <= 1000) {
        numbers.push_back(num);
      }
    } catch (...) {
      // Ignore invalid number strings (optional: could throw)
    }
  }
  if (!negatives.empty()) {
    throw NegativeNumberException(negatives);
  }
  return numbers;
}

// Splits the input string by all delimiters (including multi-char)
std::vector<std::string> StringCalculator::SplitNumbers(const std::string& input,
                                                        const std::vector<std::string>& delimiters) {
  if (delimiters.empty()) return {input};

  // Build regex pattern to split by multiple delimiters
  std::string regex_pattern;
  for (size_t i = 0; i < delimiters.size(); ++i) {
    // Escape any regex special characters in delimiter
    std::string delim = std::regex_replace(delimiters[i], std::regex(R"([-[\]{}()*+?.,\^$|#\s])"), R"(\$&)");
    regex_pattern += delim;
    if (i != delimiters.size() - 1) {
      regex_pattern += "|";
    }
  }

  std::regex re(regex_pattern);
  std::sregex_token_iterator it(input.begin(), input.end(), re, -1);
  std::sregex_token_iterator end;

  std::vector<std::string> result;
  for (; it != end; ++it) {
    result.push_back(it->str());
  }
  return result;
}

// Sums the vector of numbers
int StringCalculator::SumNumbers(const std::vector<int>& numbers) {
  int sum = 0;
  for (int num : numbers) {
    sum += num;
  }
  return sum;
}
