#include "DigitCounter.h"

#include <format>
#include <functional>
#include <optional>
#include <ranges>

#include "common/FileParser.h"
#include "common/StringManipulation.h"

DigitAdder::DigitAdder(const DigitType digitType) : m_numbers{
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

size_t DigitAdder::AddDigits(const std::filesystem::path &path)
{
    FileParser parser{path.string()};
    parser.ParseFile(std::bind_front(&DigitAdder::ParseLine, this));
    return m_sum;
}

size_t DigitAdder::AddDigits(const std::string &input)
{
    const auto lines = common::splitToMultipleString(input, '\n');
    std::ranges::for_each(lines, std::bind_front(&DigitAdder::ParseLine, this));
    return m_sum;
}

void DigitAdder::ParseLine(std::string_view line)
{
    auto oFirstNumber = std::optional<char>{};
    auto oLastNumber = std::optional<char>{};

    for (auto i = 0; i < line.size(); ++i)
    {
        if (const auto oNumber = GetFirstNumber(line, i); oNumber.has_value())
        {
            if (!oFirstNumber.has_value())
            {
                oFirstNumber = oNumber;
            }
            oLastNumber = oNumber;
        }
    }

    if (!oFirstNumber.has_value() || !oLastNumber.has_value())
    {
        return;
    }

    m_sum += std::stoi(std::format("{}{}", *oFirstNumber, *oLastNumber));
}

std::optional<char> DigitAdder::GetFirstNumber(const std::string_view line, const int startIdx)
{
    if (m_digitType == DigitType::NormalOrSpelledOut)
    {
        if (auto oNumber = GetFirstSpelledOutNumber(line, startIdx); oNumber.has_value())
        {
            return m_numbers.at(*oNumber);
        }
    }

    if (isdigit(line[startIdx]))
    {
        return line[startIdx];
    }

    return {};
}

std::optional<std::string> DigitAdder::GetFirstSpelledOutNumber(const std::string_view line, const int startIdx)
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
