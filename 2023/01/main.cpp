#include <fstream>
#include <functional>
#include <iostream>
#include <optional>
#include <set>
#include <sstream>
#include <string>
#include <map>

void readLineByLine( const std::string_view file, const std::function<void( const std::string& )>& parser )
{
    std::ifstream stream{ file.data() };
    std::string line;
    while ( std::getline( stream, line ) ) {
        parser(line);
    }
}

void solveFirstTask( const std::string_view input )
{
    int sumOfCalibration = 0;
    readLineByLine( input, [&sumOfCalibration] ( const std::string& line ) {
        auto firstNumber = std::optional<char>{};
        auto lastNumber = std::optional<char>{};

        for ( const auto& ch : line ) {
            if ( isdigit( ch ) ) {
                if (!firstNumber.has_value()) {
                    firstNumber = ch;
                }
                lastNumber = ch;
            }
        }

        std::stringstream ss;
        ss << firstNumber.value() << lastNumber.value();

        sumOfCalibration += std::stoi(ss.str());
    });
    std::cout << sumOfCalibration << "\n";
}

std::optional< std::string > isANumber( const std::string_view line, const int i )
{
    static std::set< std::string > numbers = {
        "one",
        "two",
        "three",
        "four",
        "five",
        "six",
        "seven",
        "eight",
        "nine"
    };

    if (line.size() > i + 2) {
        std::stringstream ss;
        ss << line[i] << line[i + 1] << line[i + 2];
        if (numbers.contains(ss.str())) {
            return ss.str();
        }

        if (line.size() > i + 3) {
            ss << line[i + 3];
            if (numbers.contains(ss.str())) {
                return ss.str();
            }
            if (line.size() > i + 4) {
                ss << line[i + 4];
                if (numbers.contains(ss.str())) {
                    return ss.str();
                }
            }
        }
    }
    return {};
}

void solveSecondTask( const std::string_view input )
{
    // 3-5
    static std::map< std::string, char > numbers = {
        { "one", '1' },
        { "two", '2' },
        { "three", '3' },
        { "four", '4' },
        { "five", '5' },
        { "six", '6' },
        { "seven", '7' },
        { "eight", '8' },
        { "nine", '9' }
    };

    int sumOfCalibration = 0;
    readLineByLine( input, [&sumOfCalibration] ( const std::string& line ) {
        auto firstNumber = std::optional<char>{};
        auto lastNumber = std::optional<char>{};

        for ( auto i = 0; i < line.size(); ++i ) {
            auto number = isANumber(line, i);

            if (number.has_value()) {
                if (!firstNumber.has_value()) {
                    firstNumber = numbers[*number];
                }
                lastNumber = numbers[*number];
                i += (number.value().size() - 2);
                continue;
            }

            if ( isdigit( line[i] ) ) {
                if (!firstNumber.has_value()) {
                    firstNumber = line[i];
                }
                lastNumber = line[i];
            }
        }

        std::stringstream ss;
        ss << firstNumber.value() << lastNumber.value();

        sumOfCalibration += std::stoi(ss.str());
    });
    std::cout << sumOfCalibration << "\n";
}

int main( int argc, char** argv )
{
    solveFirstTask( "sample_input.txt" );
    solveFirstTask( "input.txt" );
    solveSecondTask( "sample_input2.txt" );
    solveSecondTask( "input.txt" );
    return 0;
}
