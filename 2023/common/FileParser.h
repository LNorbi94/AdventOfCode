#pragma once

#include <string>

class FileParser
{
public:
    FileParser(std::string_view inputFile);

protected:
    virtual void parseLine(std::string_view line) = 0;
    void parseFile();

private:
    std::string m_fileName;
};
