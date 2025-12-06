#include "FourthTask.h"

#include <filesystem>
#include <iostream>

#include "PaperStore.h"
#include <common/FileParser.h>

namespace
{
    const std::filesystem::path inputFileName = "4.txt";
}

void FourthTask::SolveFirstPart()
{
    std::vector<std::string> lines;
    FileParser parser(inputFileName.string());
    parser.ParseFile([&](const std::string &line)
                     { lines.push_back(line); });

    PaperStore store(lines);

    std::cout << store.GetAccessiblePapers() << "\n";
}

void FourthTask::SolveSecondPart()
{
    std::vector<std::string> lines;
    FileParser parser(inputFileName.string());
    parser.ParseFile([&](const std::string &line)
                     { lines.push_back(line); });

    PaperStore store(lines);

    std::cout << store.GetAccessiblePapersWithRemovedPaper() << "\n";
}
