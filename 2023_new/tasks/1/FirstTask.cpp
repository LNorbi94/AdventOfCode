#include "FirstTask.h"

#include <filesystem>
#include <iostream>

#include "DigitCounter.h"

void FirstTask::SolveFirstTask(const std::string &inputFileName)
{
    DigitCounter counter;
    std::cout << counter.CountDigits(std::filesystem::path{inputFileName}) << "\n";
}

void FirstTask::SolveSecondTask(const std::string &inputFileName)
{
    DigitCounter counter{DigitCounter::DigitType::NormalOrSpelledOut};
    std::cout << counter.CountDigits(std::filesystem::path{inputFileName}) << "\n";
}
