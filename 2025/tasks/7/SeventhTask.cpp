#include "SeventhTask.h"

#include <filesystem>
#include <iostream>

#include "BeamSplitter.h"
#include <common/FileParser.h>

namespace
{
    const std::filesystem::path inputFileName = "7.txt";
}

void SeventhTask::SolveFirstPart()
{
    std::vector<std::string> lines;
    FileParser parser(inputFileName.string());

    parser.ParseFile([&](const std::string &line)
                     { lines.push_back(line); });

    BeamSplitter splitter;
    splitter.ProcessLines(lines);

    std::cout << splitter.GetSplitCount() << "\n";
}

void SeventhTask::SolveSecondPart()
{
    std::vector<std::string> lines;
    FileParser parser(inputFileName.string());

    parser.ParseFile([&](const std::string &line)
                     { lines.push_back(line); });

    BeamSplitter splitter;
    splitter.ProcessQuantumLines(lines);

    std::cout << splitter.GetNumberOfTimelines() << "\n";
}
