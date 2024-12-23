
#include <array>
#include <regex>
#include <string>
#include <vector>

namespace common
{
    std::array< std::string, 2 > splitString(std::string_view string, char delimiter);
    std::vector< std::string > splitToMultipleString( std::string_view string, char delimiter );

    template< typename T >
    std::vector< T > extractNumbers( const std::string& text )
    {
        std::vector< T > numbers;
        std::regex r{ "-?\\d+" };
        auto begin = std::sregex_iterator( text.cbegin(), text.cend(), r );
        auto end = std::sregex_iterator();
        for (auto& number = begin; begin != end; ++number) {
            numbers.emplace_back( static_cast< T >( std::stoll( number->str() ) ) );
        }
        return numbers;
    }

    std::vector< std::string > extractWords(const std::string& text);
}
