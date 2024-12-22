#include "FirstTask.h"

#include <filesystem>
#include <iostream>

#include "DigitCounter.h"

namespace
{
    constexpr auto inputFileName = "1.txt";
}

void FirstTask::SolveFirstPart()
{
    DigitAdder counter;
    std::cout << counter.AddDigits(std::filesystem::path{inputFileName}) << "\n";
}

void FirstTask::SolveSecondPart()
{
    DigitAdder counter{DigitAdder::DigitType::NormalOrSpelledOut};
    std::cout << counter.AddDigits(std::filesystem::path{inputFileName}) << "\n";
}
