#pragma once

#include <map>
#include <optional>
#include <string>
#include <filesystem>

class DigitCounter
{
public:
    enum class DigitType
    {
        Normal,
        NormalOrSpelledOut
    };

    DigitCounter(DigitType digitType = DigitType::Normal);

    size_t CountDigits(const std::filesystem::path &path);
    size_t CountDigits(const std::string &fileName);

private:
    void ParseLine(std::string_view line);
    std::optional<char> GetFirstNumber(std::string_view line, int startIdx);
    std::optional<std::string> GetFirstSpelledOutNumber(std::string_view line, int startIdx);

    DigitType m_digitType = DigitType::Normal;
    size_t m_sum = 0;
    const std::map<std::string, char> m_numbers;
};
