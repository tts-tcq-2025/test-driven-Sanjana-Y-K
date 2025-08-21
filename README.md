# TDD Driven StringCalculator

Build a StringCalculator functionality that can take up to two numbers, separated by commas, and will return their sum. 
for example “” or “1” or “1,2” as inputs.

> DO NOT jump into implementation! Read the example and the starting task below.

- For an empty string it will return 0
- Allow the Add method to handle an unknown amount of numbers
- Allow the Add method to handle new lines between numbers (instead of commas).
  - the following input is ok: “1\n2,3” (will equal 6)
  - the following input is NOT ok: “1,\n” (not need to prove it - just clarifying)
- Support different delimiters : to change a delimiter, the beginning of the string will contain a separate line that looks like this: “//[delimiter]\n[numbers…]” for example “//;\n1;2” should return three where the default delimiter is ‘;’ .
the first line is optional. all existing scenarios should still be supported
- Calling Method with a negative number will throw an exception “negatives not allowed” - and the negative that was passed. if there are multiple negatives, show all of them in the exception message.
- Numbers bigger than 1000 should be ignored, so adding 2 + 1001 = 2
- Delimiters can be of any length with the following format: “//[delimiter]\n” for example: “//[***]\n1***2***3” should return 6

## Tasks



Establish quality parameters:

- Ensure  maximum complexity (CCN) per function == 3

- Ensure 100% line and branch coverage at every step

  

Start Test-driven approach

1. Write the smallest possible failing test: give input `"" assert output to be 0 ` .
2. Write the minimum amount of code that'll make it pass.
3. Refactor any assumptions, continue to pass this test. Do not add any code without a corresponding test.

## Test specifications based on requirements

1. Empty String Input

Input: ""
Output: 0
Description: If the input string is empty, the Add method should return 0.

2. Single Number Input

Input: "1"
Output: 1
Description: If the input contains a single number, return that number.

3. Two Numbers Comma-Separated

Input: "1,2"
Output: 3
Description: Sum two numbers separated by commas.

4. Unknown Amount of Numbers

Input: "1,2,3,4,5"
Output: 15
Description: Add method should handle any number of comma-separated numbers.

6. New Line as Delimiter

Input: "1\n2,3"
Output: 6
Description: Allow newline characters (\n) as delimiters in addition to commas.

7. Invalid Input Case

Input: "1,\n"
Behavior: Not required to handle/prove invalid input behavior (clarified in requirements).

8. Support Custom Delimiters

Input: "//;\n1;2"
Output: 3
Description: If input starts with //[delimiter]\n, use the custom delimiter.

9. Negative Numbers Throw Exception

Input: "1,-2,-3"
Exception: Throw exception with message: "negatives not allowed: -2, -3"
Description: Negative numbers should cause an exception listing all negatives.

10. Ignore Numbers > 1000

Input: "2,1001"
Output: 2
Description: Numbers greater than 1000 should be ignored.

11. Delimiters of Any Length

Input: "//[***]\n1***2***3"
Output: 6
Description: Delimiters can be longer than one character, specified within //[delimiter]\n.

## GHERKIN language

Feature: String Calculator Add method

  Scenario: Empty string returns 0
    Given the input is an empty string ""
    When I call Add method
    Then the result should be 0

  Scenario: Single number returns the value itself
    Given the input is "1"
    When I call Add method
    Then the result should be 1

  Scenario: Two numbers comma separated returns their sum
    Given the input is "1,2"
    When I call Add method
    Then the result should be 3

  Scenario: Unknown amount of numbers returns their sum
    Given the input is "1,2,3,4,5"
    When I call Add method
    Then the result should be 15

  Scenario: New line between numbers is treated as delimiter
    Given the input is "1\n2,3"
    When I call Add method
    Then the result should be 6

  Scenario: Custom single-character delimiter specified
    Given the input is "//;\n1;2"
    When I call Add method
    Then the result should be 3

  Scenario: Negative numbers throw exception with all negatives listed
    Given the input is "1,-2,-3"
    When I call Add method
    Then an exception is thrown with message "negatives not allowed: -2, -3"

  Scenario: Numbers larger than 1000 are ignored
    Given the input is "2,1001"
    When I call Add method
    Then the result should be 2

  Scenario: Delimiters of any length specified with square brackets
    Given the input is "//[***]\n1***2***3"
    When I call Add method
    Then the result should be 6

## Delimiter format validation scenario is not needed as per requirements

| TestCaseID | Name                                          | Precondition               | Input                  | Action          | Expected Output                                          | Comment                                       |
| ---------- | --------------------------------------------- | -------------------------- | ---------------------- | --------------- | -------------------------------------------------------- | --------------------------------------------- |
| TC001      | Empty string returns 0                        | Calculator instance exists | `""`                   | Call Add method | `0`                                                      | Tests empty input handling                    |
| TC002      | Single number returns the value itself        | Calculator instance exists | `"1"`                  | Call Add method | `1`                                                      | Tests single number input                     |
| TC003      | Two numbers comma separated returns sum       | Calculator instance exists | `"1,2"`                | Call Add method | `3`                                                      | Tests two numbers separated by comma          |
| TC004      | Unknown amount of numbers returns their sum   | Calculator instance exists | `"1,2,3,4,5"`          | Call Add method | `15`                                                     | Tests multiple numbers separated by comma     |
| TC005      | New line between numbers is delimiter         | Calculator instance exists | `"1\n2,3"`             | Call Add method | `6`                                                      | Tests newline delimiter alongside comma       |
| TC006      | Custom single-character delimiter specified   | Calculator instance exists | `"//;\n1;2"`           | Call Add method | `3`                                                      | Tests custom single-character delimiter       |
| TC007      | Negative numbers throw exception              | Calculator instance exists | `"1,-2,-3"`            | Call Add method | Exception with message `"negatives not allowed: -2, -3"` | Validates exception with all negative numbers |
| TC008      | Numbers larger than 1000 are ignored          | Calculator instance exists | `"2,1001"`             | Call Add method | `2`                                                      | Tests ignoring numbers > 1000                 |
| TC009      | Delimiters of any length with square brackets | Calculator instance exists | `"//[***]\n1***2***3"` | Call Add method | `6`                                                      | Tests multi-character custom delimiter        |

