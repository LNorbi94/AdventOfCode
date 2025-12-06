#include "ThirdTask.h"

#include <filesystem>
#include <iostream>

#include "BatteryBank.h"
#include "UnlimitedBatteryBank.h"
#include <common/FileParser.h>
#include <common/StringManipulation.h>

#include <fstream>

namespace
{
    const std::filesystem::path inputFileName = "3.txt";
}

void ThirdTask::SolveFirstPart()
{
    FileParser parser(inputFileName.string());
    size_t joltage = 0;
    parser.ParseFile([&](const std::string& line)
        {
            BatteryBank bank(line);
            joltage += bank.getLargestJolt();
        });
    std::cout << joltage << "\n";
}

void ThirdTask::SolveSecondPart()
{
    FileParser parser(inputFileName.string());
    size_t joltage = 0;
    parser.ParseFile([&](const std::string& line)
        {
            UnlimitedBatteryBank bank(line);
            joltage += bank.getLargestJolt();
        });
    std::cout << joltage << "\n";
}
