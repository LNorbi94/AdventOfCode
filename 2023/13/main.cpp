
#include "TaskSolver.h"
#include "StringManipulation.h"

#include "source/Valley.h"

#include <regex>
#include <set>
#include <map>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stack>


class FirstTaskSolver
{
public:
    FirstTaskSolver(const std::string_view fileName)
    {
        std::ifstream stream{ fileName.data() };

        std::vector< Valley > valleys;
        Valley valley;
        std::string line;
        while (std::getline(stream, line)) {
            if (line.empty()) {
                valleys.push_back(valley);
                valley = Valley{};
            } else {
                valley.addRow(line);
            }
        }
        valleys.push_back(valley);

        auto solution = 0;
        for (const auto& valley : valleys) {
            solution += valley.mirrorScore();
        }
        std::cout << solution << "\n";
    }
};

class SecondTaskSolver
{
public:
    SecondTaskSolver(const std::string_view fileName)
    {
    }

};

void solveFirstTask(const std::string_view file)
{
    FirstTaskSolver f{ file };
}

void solveSecondTask(const std::string_view file)
{
    SecondTaskSolver f{ file };
}

int main()
{
    solveFirstTask("sample.txt");
    solveFirstTask("complete.txt");
    solveSecondTask("sample.txt");
    solveSecondTask("complete.txt");
}
