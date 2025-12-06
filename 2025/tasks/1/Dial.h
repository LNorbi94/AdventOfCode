#pragma once

#include <string>

class Dial
{
public:
    Dial();

    void runCommand(const std::string &command);

    [[nodiscard]] size_t zeroPositionReachedCount() const;
    [[nodiscard]] size_t zeroPositionReachedAfterCompletingCommandsCount() const;

private:
    void turnLeft(int numberOfTurns);
    void turnRight(int numberOfTurns);

    size_t value = 0;
    const size_t maxValue = 99;

    size_t zeroPositionReached = 0;
    size_t zeroPositionReachedAfterCompletingCommands = 0;
};