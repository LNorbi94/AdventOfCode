#include "source/FirstTask.h"
#include "source/SecondTask.h"

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
    solveFirstTask( "sample.txt" );
    solveFirstTask( "complete.txt" );
    solveSecondTask( "sample2.txt" );
    solveSecondTask( "complete.txt" );
    return 0;
}
