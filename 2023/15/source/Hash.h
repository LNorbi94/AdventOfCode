#pragma once

#include <string>

class Hash
{
public:
    Hash(std::string_view string);

    int64_t value() const;

private:
    void calculateHash(std::string_view string);

    int64_t m_value = 0;
};
