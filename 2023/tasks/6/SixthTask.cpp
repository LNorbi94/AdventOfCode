
#include "common/TaskSolver.h"
#include "common/StringManipulation.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include "SixthTask.h"
#include <filesystem>

namespace
{
    const std::filesystem::path inputFileName = "6.txt";
}

class Race
{
public:
    Race(const int64_t time, const int64_t recordDistance)
        : m_time{time}, m_recordDistance{recordDistance}
    {
    }

    int64_t numberOfWaysToWin() const
    {
        int64_t wins = 0;
        for (int64_t i = 1; i < m_time; ++i)
        {
            auto speed = i;
            auto distanceTravelled = (m_time - i) * speed;
            if (distanceTravelled > m_recordDistance)
            {
                ++wins;
            }
        }
        return wins;
    }

private:
    int64_t m_time = 0;
    int64_t m_recordDistance = 0;
};

class SixthTaskPartOneSolver
{
public:
    SixthTaskPartOneSolver(const std::string_view fileName)
    {
        std::ifstream stream{fileName.data()};

        std::string line;
        std::getline(stream, line);
        const auto times = common::extractNumbers<int>(line);
        std::getline(stream, line);
        const auto distances = common::extractNumbers<int>(line);

        std::vector<Race> races;
        for (auto i = 0; i < times.size(); ++i)
        {
            races.emplace_back(times[i], distances[i]);
        }

        auto solution = 1;
        for (const auto &race : races)
        {
            solution *= race.numberOfWaysToWin();
        }

        std::cout << solution << "\n";
    }
};

class SixthTaskPartTwoSolver
{
public:
    SixthTaskPartTwoSolver(const std::string_view fileName)
    {
        std::ifstream stream{fileName.data()};

        std::string line;
        std::getline(stream, line);
        const auto times = common::extractNumbers<int64_t>(line);
        std::getline(stream, line);
        const auto distances = common::extractNumbers<int64_t>(line);

        std::vector<Race> races;
        std::stringstream time;
        std::stringstream distance;
        for (auto i = 0; i < times.size(); ++i)
        {
            time << times[i];
            distance << distances[i];
        }
        races.emplace_back(std::stoll(time.str()), std::stoll(distance.str()));

        auto solution = 1;
        for (const auto &race : races)
        {
            solution *= race.numberOfWaysToWin();
        }

        std::cout << solution << "\n";
    }
};

void SixthTask::SolveFirstPart()
{
    SixthTaskPartOneSolver f{inputFileName.string()};
}

void SixthTask::SolveSecondPart()
{
    SixthTaskPartTwoSolver f{inputFileName.string()};
}
