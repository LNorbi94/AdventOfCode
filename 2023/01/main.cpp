#include "FirstTask.h"
#include "SecondTask.h"

static void solveFirstTask( const std::string_view input )
{
    FirstTask t{ input };
    t.solveTask();
}

void solveSecondTask( const std::string_view input )
{
    SecondTask t{ input };
    t.solveTask();
}

int main( int argc, char** argv )
{
    solveFirstTask( "sample_input.txt" );
    solveFirstTask( "input.txt" );
    solveSecondTask( "sample_input2.txt" );
    solveSecondTask( "input.txt" );
    return 0;
}
