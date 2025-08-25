#include "./string_calculator.h"

#include <algorithm>
#include <regex>
#include <string>

int StringCalculator::Add(const std::string& input) {
    if (input.empty()) return 0;

    std::string numbersPart = input;
    std::vector<std::string> delimiters = {",", "\n"};

    if (input.rfind("//", 0) == 0) {
        delimiters = ParseDelimiters(input, numbersPart);
    }

    auto nums = ExtractNumbers(numbersPart, delimiters);
    return SumNumbers(nums);
}

std::vector<std::string> StringCalculator::ParseDelimiters(const std::string& input, std::string& numbersPart) {

    std::vector<std::string> delimiters;
    size_t pos = input.find('\n');
    if (pos == std::string::npos) {
        numbersPart = "";
        return {","}; // fallback
    }
    std::string delimPart = input.substr(2, pos - 2);
    numbersPart = input.substr(pos + 1);

    if (!delimPart.empty() && delimPart[0] == '[') {
        std::regex re(R"(\[(.*?)\])");
        auto begin = std::sregex_iterator(delimPart.begin(), delimPart.end(), re);
        auto end = std::sregex_iterator();
        for (auto i = begin; i != end; ++i) {
            delimiters.push_back((*i)[1].str());
        }
    } else {
        delimiters.push_back(delimPart);
    }
    return delimiters;
}

std::vector<int> StringCalculator::ExtractNumbers(const std::string& numbers, const std::vector<std::string>& delimiters) {
 
    std::string temp = numbers;
    for (const auto& delim : delimiters) {
        if (delim.empty()) continue;
        size_t pos = 0;
        while ((pos = temp.find(delim, pos)) != std::string::npos) {
            temp.replace(pos, delim.size(), ",");
            pos += 1;
        }
    }

    std::vector<int> result;
    std::stringstream ss(temp);
    std::string token;
    std::vector<int> negatives;

    while (std::getline(ss, token, ',')) {
        if (token.empty()) continue;
        int num = std::stoi(token);
        if (num < 0) {
            negatives.push_back(num);
        } else if (num <= 1000) {
            result.push_back(num);
        }
    }

    if (!negatives.empty()) {
        std::stringstream msg;
        msg << "negatives not allowed: ";
        for (size_t i = 0; i < negatives.size(); ++i) {
            if (i > 0) msg << ", ";
            msg << negatives[i];
        }
        throw NegativeNumberException(msg.str());
    }
    return result;
}

int StringCalculator::SumNumbers(const std::vector<int>& numbers) {
    int sum = 0;
    for (int n : numbers) {
        sum += n;
    }
    return sum;
}
