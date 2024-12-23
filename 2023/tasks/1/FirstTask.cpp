#include "FirstTask.h"

#include <filesystem>
#include <iostream>

#include "DigitAdder.h"

namespace
{
    const std::filesystem::path inputFileName = "1.txt";
}

void FirstTask::SolveFirstPart()
{
    DigitAdder adder;
    std::cout << adder.AddDigits(inputFileName) << "\n";
}

void FirstTask::SolveSecondPart()
{
    DigitAdder adder{DigitAdder::DigitType::NormalOrSpelledOut};
    std::cout << adder.AddDigits(inputFileName) << "\n";
}
