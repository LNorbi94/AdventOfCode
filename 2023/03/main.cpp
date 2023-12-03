
#include <fstream>
#include <iostream>
#include <regex>
#include <string>
#include <set>
#include <vector>

bool isSymbol( const char ch )
{
    static std::set symbols = {
        '!', '"', '#', '$', '%', '&', '(', ')', '*', '+', ',', '-',  '/', ':', ';', '<', '=', '>', '?', '@', '[', '\\', ']', '^', '_', '`', '{', '|', '}', '~', '\''
    };
    return std::any_of( symbols.cbegin(), symbols.cend(), [ch] (const auto& symbol) { return symbol == ch; } );
}

void solveFirstTask( const std::string_view fileName)
{
    std::ifstream stream{ fileName.data() };

    std::string line;
    std::vector< std::string > lines;
    while ( std::getline( stream, line ) ) {
        lines.push_back( line );
    }

    int solution = 0;
    for (auto i = 0; i < lines.size(); ++i) {
        std::regex r{ "\\d+" };
        auto begin = std::sregex_iterator( lines[i].begin(), lines[i].end(), r );
        auto end = std::sregex_iterator();
        for (auto& number = begin; begin != end; ++number) {
            auto checkFrom = number->position( 0 ) - 1;
            auto checkUntil = checkFrom + number->length() + 1;

            if (checkFrom < 0) {
                checkFrom = 0;
            }
            if (checkUntil >= lines[i].size()) {
                checkUntil = lines[i].size() - 1;
            }

            for ( auto j = checkFrom; j <= checkUntil; ++j ) {
                // below, on line, under line
                if ( i - 1 >= 0 ) {
                    auto ch = lines[i - 1][j];
                    if ( isSymbol(ch) ) {
                        solution += std::stoi( number->str() );
                        break;
                    }
                }

                auto ch = lines[i][j];
                if ( isSymbol(ch) ) {
                    solution += std::stoi( number->str() );
                    break;
                }
                
                if ( i + 1 < lines.size() ) {
                    ch = lines[i + 1][j];
                    if ( isSymbol(ch) ) {
                        solution += std::stoi( number->str() );
                        break;
                    }
                }
            }
        }
    }

    std::cout << solution << "\n";
}

void solveSecondTask( const std::string_view fileName )
{
    std::ifstream stream{ fileName.data() };

    std::string line;
    std::vector< std::string > lines;
    while ( std::getline( stream, line ) ) {
        lines.push_back( line );
    }

    int solution = 0;
    for (auto i = 0; i < lines.size(); ++i) {
        for (auto j = 0; j < lines[i].size(); ++j) {
            if ( lines[i][j] != '*' ) {
                continue;
            }

            std::vector< int > gears;

            std::regex r{ "\\d+" };
            if ( i - 1 >= 0 ) {
                auto begin = std::sregex_iterator( lines[i - 1].begin(), lines[i - 1].end(), r );
                auto end = std::sregex_iterator();
                for (auto& number = begin; begin != end; ++number) {
                    auto checkFrom = number->position( 0 ) - 1;
                    auto checkUntil = checkFrom + number->length() + 1;

                    if ( j >= checkFrom && j <= checkUntil ) {
                        gears.emplace_back( std::stoi( number->str() ) );
                    }
                }
            }
            if ( i + 1 < lines.size() ) {
                auto begin = std::sregex_iterator( lines[i + 1].begin(), lines[i + 1].end(), r );
                auto end = std::sregex_iterator();
                for (auto& number = begin; begin != end; ++number) {
                    auto checkFrom = number->position( 0 ) - 1;
                    auto checkUntil = checkFrom + number->length() + 1;

                    if ( j >= checkFrom && j <= checkUntil ) {
                        gears.emplace_back( std::stoi( number->str() ) );
                    }
                }
            }
            auto begin = std::sregex_iterator( lines[i].begin(), lines[i].end(), r );
            auto end = std::sregex_iterator();
            for (auto& number = begin; begin != end; ++number) {
                auto checkFrom = number->position( 0 ) - 1;
                auto checkUntil = checkFrom + number->length() + 1;

                if ( j >= checkFrom && j <= checkUntil ) {
                    gears.emplace_back( std::stoi( number->str() ) );
                }
            }

            if (gears.size() == 2) {
                solution += (gears[0] * gears[1]);
            }
        }
    }

    std::cout << solution << "\n";
}

int main()
{
    solveFirstTask( "sample_input.txt" );
    solveFirstTask( "input.txt" );
    solveSecondTask( "sample_input.txt" );
    solveSecondTask( "input.txt" );
    return 0;
}