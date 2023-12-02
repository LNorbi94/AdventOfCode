#include "FirstTask.h"

#include <sstream>
#include <optional>

FirstTask::FirstTask( std::string_view inputFile )
        : TaskSolver{ inputFile }
{}

void FirstTask::parseLine( std::string_view line )
{
    auto firstNumber = std::optional<char>{};
    auto lastNumber = std::optional<char>{};

    for ( const auto& ch : line ) {
        if ( isdigit( ch ) ) {
            if ( !firstNumber.has_value() ) {
                firstNumber = ch;
            }
            lastNumber = ch;
        }
    }

    if ( !firstNumber.has_value() || !lastNumber.has_value() ) {
        return;
    }

    std::stringstream ss;
    ss << firstNumber.value() << lastNumber.value();

    m_solution += std::stoi(ss.str());
}
