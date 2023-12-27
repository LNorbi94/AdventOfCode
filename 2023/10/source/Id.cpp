#include "Id.h"

#include <sstream>

Id::operator std::string() const
{
    std::stringstream ss;
    ss << column << ":" << row;
    return ss.str();
}
