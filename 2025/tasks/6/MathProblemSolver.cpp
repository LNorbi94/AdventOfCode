#include "MathProblemSolver.h"

#include <sstream>
#include <algorithm>
#include <cctype>
#include <ranges>
#include <iostream>

namespace {
    size_t GetNumber(const std::vector<size_t>& column) {
        size_t number = 0;
        for (size_t digit : column) {
            number = number * 10 + digit;
        }
        return number;
    }
}

void MathProblemSolver::AddInput(const std::string &input)
{
    std::istringstream stream(input);
    std::string token;
    std::vector<std::string> tokens;

    // Split by tabs
    while (std::getline(stream, token, ' '))
    {
        if (token.empty())
            continue;
        tokens.push_back(token);
    }

    // Process each token
    for (size_t i = 0; i < tokens.size(); ++i)
    {
        const auto &token = tokens[i];

        if (token == "*")
        {
            // Multiply the problem at index i
            if (i < problems.size())
            {
                size_t product = 1;
                for (size_t num : problems[i])
                {
                    product *= num;
                }
                // Replace the problem with a single-element vector containing the product
                problems[i] = {product};
            }
        }
        else if (token == "+")
        {
            // Add the problems at index i (sum all numbers in that problem)
            if (i < problems.size())
            {
                size_t sum = 0;
                for (size_t num : problems[i])
                {
                    sum += num;
                }
                // Replace the problem with a single-element vector containing the sum
                problems[i] = {sum};
            }
        }
        else if (isNumber(token))
        {
            // Add number to the current problem (create new problem if needed)
            size_t num = parseNumber(token);
            if (i >= problems.size())
            {
                problems.resize(i + 1);
            }
            problems[i].push_back(num);
        }
    }
}

void MathProblemSolver::AddAlternativeInput(const std::string &input)
{
    for (size_t i = 0; i < input.size(); ++i)
    {
        const auto &token = input[i];

        if (token == '+' || token == '*')
        {
            operations.push_back(std::make_pair(i, token));
        }
        else if (std::isdigit(static_cast<unsigned char>(token)))
        {
            // Add number to the current problem (create new problem if needed)
            size_t num = (token - '0');
            if (i >= problems.size())
            {
                problems.resize(i + 1);
            }
            problems[i].push_back(num);
        }
    }
}

size_t MathProblemSolver::GetResult() const
{
    size_t total = 0;
    for (const auto& [i, operation] : std::views::enumerate(operations)) {
        const auto& [startIdx, operatorToUse] = operation;
        const auto endIdx = operations.size() > i + 1 ? operations[i + 1].first - 1 : problems.size();
        size_t subOperation = (operatorToUse == '+') ? 0 : 1;
        for(size_t col = startIdx; col < endIdx; ++col) {
            size_t number = GetNumber(problems[col]);
            if (operatorToUse == '+') {
                subOperation += number;
            } else if (operatorToUse == '*') {
                subOperation *= number;
            }
        }
        total += subOperation;
    }
    return total;
}

bool MathProblemSolver::isNumber(const std::string &str) const
{
    if (str.empty())
    {
        return false;
    }

    for (char c : str)
    {
        if (!std::isdigit(static_cast<unsigned char>(c)))
        {
            return false;
        }
    }
    return true;
}

size_t MathProblemSolver::parseNumber(const std::string &str) const
{
    return std::stoull(str);
}
