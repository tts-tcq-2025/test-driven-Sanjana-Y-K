#pragma once

#include <string>
#include <vector>

// C++ header file for StringCalculator class
#ifdef __cplusplus
extern "C++" {


class StringCalculator {
 public:
  int Add(const std::string& numbers);

 private:
  struct DelimiterInfo {
    std::vector<std::string> customDelimiters;
    std::string numbersString;
  };

  DelimiterInfo ParseDelimiters(const std::string& input);
  std::vector<std::string> ParseBracketDelimiters(
      const std::string& delimSection);
  bool FindNextDelimiterPair(const std::string& section, size_t& pos,
                            size_t& open, size_t& close);
  std::string NormalizeDelimiters(
      const std::string& numbers,
      const std::vector<std::string>& customDelimiters);
  std::vector<int> ExtractNumbers(const std::string& normalizedString);
  void ValidateNumbers(const std::vector<int>& numbers);
  std::vector<int> CollectNegatives(const std::vector<int>& numbers);
  int CalculateSum(const std::vector<int>& numbers);
};

#ifdef __cplusplus
}
#endif
#endif
