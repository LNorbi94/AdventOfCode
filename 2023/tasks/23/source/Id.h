#pragma once

struct Id {
    int row = 0;
    int column = 0;

    bool operator!=(const Id& otherId) const;
    bool operator==(const Id& otherId) const;
};
