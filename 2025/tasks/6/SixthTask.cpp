#include "SixthTask.h"

#include <filesystem>
#include <iostream>

#include "MathProblemSolver.h"
#include <common/FileParser.h>

namespace
{
    const std::filesystem::path inputFileName = "6.txt";
}

void SixthTask::SolveFirstPart()
{
    MathProblemSolver solver;
    FileParser parser(inputFileName.string());
    
    parser.ParseFile([&](const std::string &line)
    {
        solver.AddInput(line);
    });
    
    std::cout << solver.GetResult() << "\n";
}

void SixthTask::SolveSecondPart()
{
    MathProblemSolver solver;
    FileParser parser(inputFileName.string());

    parser.ParseFile([&](const std::string& line)
        {
            solver.AddAlternativeInput(line);
        });

    std::cout << solver.GetResult() << "\n";
}

