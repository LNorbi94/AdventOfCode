#include "DigitCounter.h"

#include <functional>
#include <sstream>
#include <iostream>
#include <optional>
#include <ranges>

#include "common/FileParser.h"
#include "common/StringManipulation.h"

DigitCounter::DigitCounter(const DigitType digitType) : m_numbers{
                                                            {"one", '1'},
                                                            {"two", '2'},
                                                            {"three", '3'},
                                                            {"four", '4'},
                                                            {"five", '5'},
                                                            {"six", '6'},
                                                            {"seven", '7'},
                                                            {"eight", '8'},
                                                            {"nine", '9'}},
                                                        m_digitType{digitType}
{
}

size_t DigitCounter::CountDigits(const std::filesystem::path &path)
{
    FileParser parser{path.string()};
    parser.ParseFile(std::bind_front(&DigitCounter::ParseLine, this));
    return m_sum;
}

size_t DigitCounter::CountDigits(const std::string &input)
{
    const auto lines = common::splitToMultipleString(input, '\n');
    std::ranges::for_each(lines, std::bind_front(&DigitCounter::ParseLine, this));
    return m_sum;
}

void DigitCounter::ParseLine(std::string_view line)
{
    auto firstNumber = std::optional<char>{};
    auto lastNumber = std::optional<char>{};

    for (auto i = 0; i < line.size(); ++i)
    {
        if (const auto oNumber = GetFirstNumber(line, i); oNumber.has_value())
        {
            if (!firstNumber.has_value())
            {
                firstNumber = oNumber;
            }
            lastNumber = oNumber;
        }
    }

    if (!firstNumber.has_value() || !lastNumber.has_value())
    {
        return;
    }

    std::stringstream ss;
    ss << firstNumber.value() << lastNumber.value();

    m_sum += std::stoi(ss.str());
}

std::optional<char> DigitCounter::GetFirstNumber(const std::string_view line, const int startIdx)
{
    if (m_digitType == DigitType::NormalOrSpelledOut)
    {
        auto oNumber = GetFirstSpelledOutNumber(line, startIdx);
        if (oNumber.has_value())
        {
            return m_numbers.at(*oNumber);
        }
    }

    if (isdigit(line[startIdx]))
    {
        return line[startIdx];
    }
    return std::optional<char>();
}

std::optional<std::string> DigitCounter::GetFirstSpelledOutNumber(const std::string_view line, const int startIdx)
{
    for (auto i = 0; i < 3; ++i)
    {
        std::string number{line.substr(startIdx, 3 + i)};
        if (m_numbers.contains(number))
        {
            return number;
        }
    }
    return {};
}
