#include <fstream>
#include <functional>
#include <iostream>
#include <optional>
#include <set>
#include <sstream>
#include <string>
#include <map>
#include <regex>

class Game
{
public:
    Game( int id ) : m_id{ id }
    {}

    void addRound( int red, int green, int blue )
    {
        if (red > MaxRedCubes || green > MaxGreenCubes || blue > MaxBlueCubes) {
            m_gamePossible = false;
        }

        if (red > m_minimumRedCubes) {
            m_minimumRedCubes = red;
        }

        if (green > m_minimumGreenCubes) {
            m_minimumGreenCubes = green;
        }

        if (blue > m_minimumBlueCubes) {
            m_minimumBlueCubes = blue;
        }
    }

    bool isGamePossible() const
    {
        return m_gamePossible;
    }

    int getId() const
    {
        return m_id;
    }

    int getPower() const
    {
        return m_minimumRedCubes * m_minimumBlueCubes * m_minimumGreenCubes;
    }

private:
    static int MaxRedCubes;
    static int MaxGreenCubes;
    static int MaxBlueCubes;

    int m_id = 0;
    bool m_gamePossible = true;

    int m_minimumRedCubes = 0;
    int m_minimumGreenCubes = 0;
    int m_minimumBlueCubes = 0;
};

int Game::MaxRedCubes = 12;
int Game::MaxGreenCubes = 13;
int Game::MaxBlueCubes = 14;

void readLineByLine( const std::string_view file, const std::function<void( const std::string& )>& parser )
{
    std::ifstream stream{ file.data() };
    std::string line;
    while ( std::getline( stream, line ) ) {
        parser(line);
    }
}

int extractColor( const std::string& round, const std::string_view color )
{
    std::stringstream ss;
    ss << "\\d*\\s" << color;
    std::regex r{ ss.str() };

    auto begin = std::sregex_iterator( round.begin(), round.end(), r );
    auto end = std::sregex_iterator();

    if ( begin != end ) {
        auto match = begin->str();
        ss.str("");
        for( const auto& ch : match ) {
            if (ch != ' ') {
                ss << ch;
            } else {
                break;
            }
        }
        return std::stoi( ss.str() );
    } else {
        return 0;
    }
}

void solveFirstTask( const std::string_view input )
{
    std::vector<Game> games;
    int id = 1;
    readLineByLine( input, [ &games, &id ] ( const std::string& line ) {
        Game g{ id++ };

        std::regex regex{ "(\\d+\\s\\w+,\\s)*\\d+\\s\\w+(;)*" };
        auto begin = std::sregex_iterator(line.begin(), line.end(), regex);
        auto end = std::sregex_iterator();
        for (auto& i = begin; i != end; ++i) {
            auto b = i->str();
            std::cout << b << "\n";

            auto blue = extractColor( b, "blue" );
            auto red = extractColor( b, "red" );
            auto green = extractColor( b, "green" );

            g.addRound( red, green, blue );
        }

        games.push_back( g );
    });
    int sumOfPossibleGames = 0;
    for (const auto& game : games) {
        if (game.isGamePossible()) {
            sumOfPossibleGames += game.getId();
        }
    }
    std::cout << sumOfPossibleGames << "\n";
}

void solveSecondTask( const std::string_view input )
{
    std::vector<Game> games;
    int id = 1;
    readLineByLine( input, [ &games, &id ] ( const std::string& line ) {
        Game g{ id++ };

        std::regex regex{ "(\\d+\\s\\w+,\\s)*\\d+\\s\\w+(;)*" };
        auto begin = std::sregex_iterator(line.begin(), line.end(), regex);
        auto end = std::sregex_iterator();
        for (auto& i = begin; i != end; ++i) {
            auto b = i->str();
            std::cout << b << "\n";

            auto blue = extractColor( b, "blue" );
            auto red = extractColor( b, "red" );
            auto green = extractColor( b, "green" );

            g.addRound( red, green, blue );
        }

        games.push_back( g );
    });
    int sumOfPossibleGames = 0;
    for (const auto& game : games) {
            sumOfPossibleGames += game.getPower();
    }
    std::cout << sumOfPossibleGames << "\n";
}

int main( int argc, char** argv )
{
    solveFirstTask( "sample_input.txt" );
    solveFirstTask( "input.txt" );
    solveSecondTask( "sample_input2.txt" );
    solveSecondTask( "input.txt" );
    return 0;
}
