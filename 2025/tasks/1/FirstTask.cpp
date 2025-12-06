#include "FirstTask.h"

#include <filesystem>
#include <iostream>

#include "Dial.h"
#include <common/FileParser.h>

namespace
{
    const std::filesystem::path inputFileName = "1.txt";
}

void FirstTask::SolveFirstPart()
{
    Dial dial;
    FileParser parser(inputFileName.string());
    parser.ParseFile([&](const std::string &line)
                     { dial.runCommand(line); });
    std::cout << dial.zeroPositionReachedAfterCompletingCommandsCount() << "\n";
}

void FirstTask::SolveSecondPart()
{
    Dial dial;
    FileParser parser(inputFileName.string());
    parser.ParseFile([&](const std::string &line)
                     { dial.runCommand(line); });
    std::cout << dial.zeroPositionReachedCount() << "\n";
}
