#include <argparse/argparse.hpp>

#include "TaskStore.h"

int main(int argc, char *argv[])
{
    TaskStore taskStore;
    argparse::ArgumentParser program("AoC2023");

    program.add_argument("-t", "--task")
        .default_value(std::string("21"))
        .help("specify the task to run.");

    try
    {
        program.parse_args(argc, argv);
    }
    catch (const std::exception &err)
    {
        std::cerr << err.what() << std::endl;
        std::cerr << program;
        return 1;
    }

    auto task = program.get<std::string>("--task");

    taskStore.GetTask(task)->SolveFirstPart();
    taskStore.GetTask(task)->SolveSecondPart();

    return 0;
}
