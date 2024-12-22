#pragma once

#include <functional>
#include <string>

class FileParser
{
public:
    FileParser(std::string_view inputFile);

    void ParseFile(std::function<void(const std::string &)> parseLine) const;

private:
    std::string m_fileName;
};
