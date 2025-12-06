#include "Dial.h"
#include <iostream>

Dial::Dial() : value(50), maxValue(99)
{
}

void Dial::runCommand(const std::string &command)
{
    auto numberOfTurns = std::stoi(command.substr(1));
    if (command.front() == 'L')
    {
        turnLeft(numberOfTurns);
    }
    else if (command.front() == 'R')
    {
        turnRight(numberOfTurns);
    }

    if (value == 0)
    {
        ++zeroPositionReachedAfterCompletingCommands;
    }
}

size_t Dial::zeroPositionReachedCount() const
{
    return zeroPositionReached;
}

size_t Dial::zeroPositionReachedAfterCompletingCommandsCount() const
{
    return zeroPositionReachedAfterCompletingCommands;
}

void Dial::turnLeft(int numberOfTurns)
{
    if (numberOfTurns > value)
    {
        zeroPositionReached += (numberOfTurns) / maxValue;
        value = (value - numberOfTurns + maxValue) % maxValue + 1;
    }
    else
    {
        value -= numberOfTurns;
        if (value == 0)
        {
            ++zeroPositionReached;
        }
    }
}

void Dial::turnRight(int numberOfTurns)
{
    zeroPositionReached += numberOfTurns / maxValue;
    if (value + numberOfTurns > maxValue)
    {
        value = (value + numberOfTurns) % maxValue + 1;
    }
    else {
        value += numberOfTurns;
    }
}
