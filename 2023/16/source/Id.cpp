#include "Id.h"

bool Id::operator!=(const Id& otherId) const
{
    return column != otherId.column || row != otherId.row;
}

bool Id::operator==(const Id& otherId) const
{
    return column == otherId.column && row == otherId.row;
}
