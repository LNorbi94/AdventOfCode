#pragma once

struct Id {
    int column = 0;
    int row = 0;

    bool operator!=(const Id& otherId) const;
    bool operator==(const Id& otherId) const;
};
