#include "FileParser.h"

#include <fstream>

FileParser::FileParser(const std::string_view inputFile)
    : m_fileName{inputFile}
{
}

void FileParser::ParseFile(std::function<void(const std::string &)> parseLine) const
{
    std::ifstream stream{m_fileName};

    std::string line;
    while (std::getline(stream, line))
    {
        parseLine(line);
    }
}
