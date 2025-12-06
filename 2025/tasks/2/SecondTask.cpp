#include "SecondTask.h"

#include <filesystem>
#include <iostream>

#include "IdRangeValidator.h"
#include <common/FileParser.h>
#include <common/StringManipulation.h>

#include <fstream>

namespace
{
    const std::filesystem::path inputFileName = "2.txt";
}

void SecondTask::SolveFirstPart()
{
    std::ifstream t(inputFileName);
    std::stringstream buffer;
    buffer << t.rdbuf();
    size_t invalidIdSum = 0;
    for (const auto &line : common::splitToMultipleString(buffer.str(), ','))
    {

        auto [from, to] = common::splitString(line, "-");
        IdRangeValidator validator(std::stoull(from), std::stoull(to));
        invalidIdSum += validator.getInvalidIdSum();
    }
    std::cout << invalidIdSum << "\n";
}

void SecondTask::SolveSecondPart()
{
}
