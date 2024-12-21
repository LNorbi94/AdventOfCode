#include "FirstTask.h"

#include <filesystem>
#include <iostream>

#include "DigitCounter.h"

void FirstTask::SolveFirstTask(const std::string &inputFileName)
{
    DigitAdder counter;
    std::cout << counter.AddDigits(std::filesystem::path{inputFileName}) << "\n";
}

void FirstTask::SolveSecondTask(const std::string &inputFileName)
{
    DigitAdder counter{DigitAdder::DigitType::NormalOrSpelledOut};
    std::cout << counter.AddDigits(std::filesystem::path{inputFileName}) << "\n";
}
