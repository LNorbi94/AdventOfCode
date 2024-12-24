#include "Part.h"

int Part::getCategory(char category) const
{
    switch (category)
    {
    case 'x':
        return x;
    case 'm':
        return m;
    case 'a':
        return a;
    case 's':
        return s;
    default:
        break;
    }
    return -1;
}

void Part::setCategory(char category, int value)
{
    switch (category)
    {
    case 'x':
        x = value;
        break;
    case 'm':
        m = value;
        break;
    case 'a':
        a = value;
        break;
    case 's':
        s = value;
        break;
    default:
        break;
    }
}

int Part::getTotalRating() const
{
    return x + m + a + s;
}
