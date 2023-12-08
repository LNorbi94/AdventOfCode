#include "StringManipulation.h"

#include <sstream>

std::array< std::string, 2 > common::splitString( const std::string_view string, const char delimiter )
{
    std::array< std::string, 2 > result;
    std::stringstream ss;
    for ( const auto& ch : string ) {
        if ( ch == delimiter ) {
            result[ 0 ] = ss.str();
            ss.str( "" );
        }
        ss << ch;
    }
    result[ 1 ] = ss.str();
    return result;
}

std::vector<std::string> common::extractWords(const std::string& text)
{
    std::vector< std::string > words;
    std::regex r{ "\\w+" };
    auto begin = std::sregex_iterator(text.cbegin(), text.cend(), r);
    auto end = std::sregex_iterator();
    for (auto& number = begin; begin != end; ++number) {
        words.emplace_back(number->str());
    }
    return words;
}
