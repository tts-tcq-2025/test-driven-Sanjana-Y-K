#ifndef STRING_CALCULATOR_H_
#define STRING_CALCULATOR_H_

#include <exception>
#include <string>
#include <vector>

class NegativeNumberException : public std::exception {
 public:
  explicit NegativeNumberException(const std::vector<int>& negatives);
  const char* what() const noexcept override;

 private:
  std::string message_;
};

class StringCalculator {
 public:
  int Add(const std::string& input);

 private:
  std::vector<std::string> ParseDelimiters(const std::string& input, std::string& numbers_part);
  std::vector<std::string> ParseSingleCharDelimiter(const std::string& delimiter_part);
  std::vector<std::string> ParseMultiCharDelimiters(const std::string& delimiter_part);
  std::vector<int> ExtractNumbers(const std::string& numbers_str,
                                  const std::vector<std::string>& delimiters);
  std::vector<std::string> SplitNumbers(const std::string& input,
                                        const std::vector<std::string>& delimiters);
  int SumNumbers(const std::vector<int>& numbers);
};

#endif  // STRING_CALCULATOR_H_
