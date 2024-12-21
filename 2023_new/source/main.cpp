#include "TaskStore.h"

int main()
{
    TaskStore taskStore;
    taskStore.GetTask("1")->SolveFirstTask("1.txt");
    taskStore.GetTask("1")->SolveSecondTask("1.txt");
    return 0;
}
