#include "StringCalculator.h"
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <numeric>
#include <stdexcept>
#include <cstdlib>
#include <cstdio>

namespace {
void ReplaceAll(std::string* str, const std::string& from,
                const std::string& to) {
  size_t pos = 0;
  while ((pos = str->find(from, pos)) != std::string::npos) {
    str->replace(pos, from.length(), to);
    pos += to.length();
  }
}

void ReplaceAllChars(std::string* str, const std::string& chars, char to) {
  for (char c : chars) {
    std::replace(str->begin(), str->end(), c, to);
  }
}

std::string JoinNegatives(const std::vector<int>& negatives) {
  std::string msg = "negatives not allowed: ";
  char buf[32];
  for (size_t i = 0; i < negatives.size(); ++i) {
    std::snprintf(buf, sizeof(buf), "%d", negatives[i]);
    msg += buf;
    if (i + 1 < negatives.size()) {
      msg += ", ";
    }
  }
  return msg;
}
}  // namespace

// CCN: 2 (has one if condition)
int StringCalculator::Add(const std::string& numbers) {
  if (numbers.empty()) return 0;

  DelimiterInfo delimInfo = ParseDelimiters(numbers);
  std::string normalizedString = NormalizeDelimiters(
      delimInfo.numbersString, delimInfo.customDelimiters);
  std::vector<int> extractedNumbers = ExtractNumbers(normalizedString);
  ValidateNumbers(extractedNumbers);
  return CalculateSum(extractedNumbers);
}

// CCN: 3 (has two if conditions)
StringCalculator::DelimiterInfo StringCalculator::ParseDelimiters(
    const std::string& input) {
  DelimiterInfo result;

  if (input.rfind("//", 0) != 0) {
    result.numbersString = input;
    return result;
  }

  size_t delimEnd = input.find('\n');
  std::string delimSection = input.substr(2, delimEnd - 2);
  result.numbersString = input.substr(delimEnd + 1);

  if (delimSection[0] == '[') {
    result.customDelimiters = ParseBracketDelimiters(delimSection);
  } else {
    result.customDelimiters.push_back(std::string(1, delimSection[0]));
  }

  return result;
}

// CCN: 2 (has while loop)
std::vector<std::string> StringCalculator::ParseBracketDelimiters(
    const std::string& delimSection) {
  std::vector<std::string> delimiters;
  size_t pos = 0;
  size_t open, close;

  while (FindNextDelimiterPair(delimSection, pos, open, close)) {
    delimiters.push_back(delimSection.substr(open + 1, close - open - 1));
    pos = close + 1;
  }

  return delimiters;
}

// CCN: 2 (has if condition and position check)
bool StringCalculator::FindNextDelimiterPair(const std::string& section,
                                           size_t& pos, size_t& open,
                                           size_t& close) {
  if (pos >= section.length()) return false;

  open = section.find('[', pos);
  close = section.find(']', open);

  return (open != std::string::npos && close != std::string::npos);
}

// CCN: 1 (simple loop, no branching)
std::string StringCalculator::NormalizeDelimiters(
    const std::string& numbers,
    const std::vector<std::string>& customDelimiters) {
  std::string result = numbers;

  for (const auto& delimiter : customDelimiters) {
    ReplaceAll(&result, delimiter, ",");
  }

  ReplaceAllChars(&result, "\n", ',');
  return result;
}

// CCN: 3 (has while loop and if condition)
std::vector<int> StringCalculator::ExtractNumbers(
    const std::string& normalizedString) {
  std::vector<int> numbers;
  std::stringstream ss(normalizedString);
  std::string token;

  while (std::getline(ss, token, ',')) {
    if (token.empty()) continue;
    numbers.push_back(std::atoi(token.c_str()));
  }

  return numbers;
}

// CCN: 2 (has if condition for exception throwing)
void StringCalculator::ValidateNumbers(const std::vector<int>& numbers) {
  std::vector<int> negatives = CollectNegatives(numbers);

  if (!negatives.empty()) {
    throw std::runtime_error(JoinNegatives(negatives));
  }
}

// CCN: 1 (using STL algorithm, no explicit branching)
std::vector<int> StringCalculator::CollectNegatives(
    const std::vector<int>& numbers) {
  std::vector<int> negatives;
  std::copy_if(numbers.begin(), numbers.end(),
               std::back_inserter(negatives),
               [](int number) { return number < 0; });

  return negatives;
}

// CCN: 1 (using STL algorithm, no explicit branching)
int StringCalculator::CalculateSum(const std::vector<int>& numbers) {
  return std::accumulate(numbers.begin(), numbers.end(), 0,
                        [](int sum, int number) {
                          return (number <= 1000) ? sum + number : sum;
                        });
}
