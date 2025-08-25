#ifndef STRING_CALCULATOR_H_
#define STRING_CALCULATOR_H_

#include <string>
#include <vector>
#include <stdexcept>

class NegativeNumberException : public std::runtime_error {
 public:
  explicit NegativeNumberException(const std::string& msg)
      : std::runtime_error(msg) {}
};

class StringCalculator {
 public:
  int Add(const std::string& numbers);

 private:
  std::vector<std::string> ParseDelimiters(const std::string& input,
                                           std::string& numbersPart);
  std::vector<int> ExtractNumbers(const std::string& numbers,
                                  const std::vector<std::string>& delimiters);
  int SumNumbers(const std::vector<int>& numbers);
};

#endif  // STRING_CALCULATOR_H_
