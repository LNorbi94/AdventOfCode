#pragma once

struct Part
{
    int x = 0;
    int m = 0;
    int a = 0;
    int s = 0;

    int getCategory(char category) const;
    void setCategory(char category, int value);
    int getTotalRating() const;
};
