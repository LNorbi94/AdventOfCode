#include "EightTask.h"

#include <filesystem>
#include <iostream>

#include "CompletePlayground.h"
#include <common/FileParser.h>

namespace
{
    const std::filesystem::path inputFileName = "8.txt";
}

void EightTask::SolveFirstPart()
{
    std::vector<std::string> lines;
    FileParser parser(inputFileName.string());

    parser.ParseFile([&](const std::string &line)
                     { lines.push_back(line); });

    CompletePlayground playground(lines);
    playground.FindClosestJunctionBoxes(1000);
    std::cout << playground.MultiplyCircuitCount(3) << "\n";
}

void EightTask::SolveSecondPart()
{
    std::vector<std::string> lines;
    FileParser parser(inputFileName.string());

    parser.ParseFile([&](const std::string &line)
                     { lines.push_back(line); });

    CompletePlayground playground(lines);
    playground.MergeUntilOneCircuit();
}
