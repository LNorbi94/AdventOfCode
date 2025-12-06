#pragma once

#include <cstdint>
#include <string>
#include <vector>

class MathProblemSolver
{
public:
    // Process a tab-separated string input.
    // - Numbers are added to the current problem (vector of numbers).
    // - "*" multiplies the problem at that token's index position.
    // - "+" adds the problems at that token's index position.
    void AddInput(const std::string &input);

    void AddAlternativeInput(const std::string &input);

    // Returns the sum of all problems' results.
    // Each problem's result is the sum of its numbers.
    size_t GetResult() const;

private:
    // Problems: each problem is a vector of numbers.
    std::vector<std::vector<size_t>> problems;
    std::vector<std::pair<size_t, char>> operations;
    

    // Helper to check if a string is a number.
    bool isNumber(const std::string &str) const;

    // Helper to parse a number from string.
    size_t parseNumber(const std::string &str) const;
};

