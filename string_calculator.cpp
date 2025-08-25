#include "./string_calculator.h"

#include <algorithm>
#include <regex>
#include <string>

NegativeNumberException::NegativeNumberException(const std::vector<int>& negatives) {
  message_ = "negatives not allowed: ";
  for (size_t i = 0; i < negatives.size(); ++i) {
    message_ += std::to_string(negatives[i]);
    if (i + 1 < negatives.size()) {
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

std::vector<std::string> StringCalculator::ParseDelimiters(const std::string& input, std::string& numbers_part) {
  if (input.size() < 2 || input[0] != '/' || input[1] != '/') {
    numbers_part = input;
    return {",", "\n"};
  }
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
}

std::vector<std::string> StringCalculator::ParseSingleCharDelimiter(const std::string& delimiter_part) {
  if (delimiter_part.empty()) {
    return {","};
  }
  return {delimiter_part};
}

std::vector<std::string> StringCalculator::ParseMultiCharDelimiters(const std::string& delimiter_part) {
  std::vector<std::string> delimiters;
  size_t pos = 0;
  while (true) {
    size_t start = delimiter_part.find('[', pos);
    size_t end = delimiter_part.find(']', start);
    if (start == std::string::npos || end == std::string::npos) {
      break;
    }
    delimiters.push_back(delimiter_part.substr(start + 1, end - start - 1));
    pos = end + 1;
  }
  if (delimiters.empty()) {
    delimiters.push_back(",");  // fallback
  }
  return delimiters;
}

std::vector<int> StringCalculator::ExtractNumbers(const std::string& numbers_str,
                                                  const std::vector<std::string>& delimiters) {
  auto tokens = SplitNumbers(numbers_str, delimiters);
  std::vector<int> numbers;
  std::vector<int> negatives;

  for (const auto& token : tokens) {
    if (token.empty()) {
      continue;
    }
    int num = 0;
    if (TryParseInt(token, num)) {
      if (num < 0) {
        negatives.push_back(num);
      } else if (num <= 1000) {
        numbers.push_back(num);
      }
    }
  }

  if (!negatives.empty()) {
    throw NegativeNumberException(negatives);
  }
  return numbers;
}

bool StringCalculator::TryParseInt(const std::string& s, int& result) {
  try {
    size_t idx;
    result = std::stoi(s, &idx);
    return idx == s.size();
  } catch (...) {
    return false;
  }
}

std::vector<std::string> StringCalculator::SplitNumbers(const std::string& input,
                                                        const std::vector<std::string>& delimiters) {
  if (delimiters.empty()) {
    return {input};
  }

  std::string pattern;
  for (size_t i = 0; i < delimiters.size(); ++i) {
    std::string delim_escaped = EscapeRegex(delimiters[i]);
    pattern += delim_escaped;
    if (i + 1 < delimiters.size()) {
      pattern += "|";
    }
  }

  std::regex re(pattern);
  std::sregex_token_iterator it(input.begin(), input.end(), re, -1);
  std::sregex_token_iterator end;
  return {it, end};
}

std::string StringCalculator::EscapeRegex(const std::string& str) {
  static const std::regex special_chars(R"([-[\]{}()*+?.,\^$|#\s])");
  return std::regex_replace(str, special_chars, R"(\$&)");
}

int StringCalculator::SumNumbers(const std::vector<int>& numbers) {
  int sum = 0;
  for (int n : numbers) {
    sum += n;
  }
  return sum;
}
