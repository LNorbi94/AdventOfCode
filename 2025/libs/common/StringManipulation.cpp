#include "StringManipulation.h"

#include <sstream>

std::array<std::string, 2> common::splitString(const std::string &string, const std::string &delimiter)
{
    std::array<std::string, 2> result;
    const auto delimiterPos = string.find(delimiter);
    return {string.substr(0, delimiterPos), string.substr(delimiterPos + delimiter.size())};
}

std::vector<std::string> common::splitToMultipleString(std::string_view string, char delimiter)
{
    std::stringstream ss{string.data()};
    std::vector<std::string> words;
    std::string word;
    while (std::getline(ss, word, delimiter))
    {
        words.push_back(word);
    }
    return words;
}

std::vector<std::string> common::extractWords(const std::string &text)
{
    std::vector<std::string> words;
    std::regex r{"\\w+"};
    auto begin = std::sregex_iterator(text.cbegin(), text.cend(), r);
    auto end = std::sregex_iterator();
    for (auto &number = begin; begin != end; ++number)
    {
        words.emplace_back(number->str());
    }
    return words;
}
