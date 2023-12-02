#include "SecondTask.h"

#include <sstream>
#include <optional>

SecondTask::SecondTask( std::string_view inputFile )
    : TaskSolver{ inputFile }
    , m_numbers {
        { "one", '1' },
        { "two", '2' },
        { "three", '3' },
        { "four", '4' },
        { "five", '5' },
        { "six", '6' },
        { "seven", '7' },
        { "eight", '8' },
        { "nine", '9' }
    }
{
}

void SecondTask::parseLine( std::string_view line )
{
    auto firstNumber = std::optional<char>{};
    auto lastNumber = std::optional<char>{};

    for ( auto i = 0; i < line.size(); ++i ) {
        auto number = getNumberWord( line, i );

        if ( number.has_value() ) {
            if ( !firstNumber.has_value() ) {
                firstNumber = m_numbers[ *number ];
            }
            lastNumber = m_numbers[ *number ];
            i += ( number->size() - 2 );
            continue;
        }

        if ( isdigit( line[i] ) ) {
            if (!firstNumber.has_value()) {
                firstNumber = line[i];
            }
            lastNumber = line[i];
        }
    }

    if ( !firstNumber.has_value() || !lastNumber.has_value() ) {
        return;
    }

    std::stringstream ss;
    ss << firstNumber.value() << lastNumber.value();

    m_solution += std::stoi(ss.str());
}

std::optional< std::string > SecondTask::getNumberWord( const std::string_view line, const int i )
{
    if ( line.size() > i + 2 ) {
        std::stringstream ss;
        ss << line[i] << line[i + 1] << line[i + 2];
        if (m_numbers.contains(ss.str())) {
            return ss.str();
        }

        if ( line.size() > i + 3 ) {
            ss << line[i + 3];
            if (m_numbers.contains(ss.str())) {
                return ss.str();
            }
            if ( line.size() > i + 4 ) {
                ss << line[i + 4];
                if (m_numbers.contains(ss.str())) {
                    return ss.str();
                }
            }
        }
    }
    return {};
}
