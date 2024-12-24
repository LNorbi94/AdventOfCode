#include "Hash.h"

Hash::Hash(const std::string_view string)
{
    calculateHash(string);
}

int64_t Hash::value() const
{
    return m_value;
}

void Hash::calculateHash(const std::string_view string)
{
    for (const auto& ch : string) {
        m_value += static_cast<int64_t>(ch);
        m_value *= 17;
        m_value = m_value % 256;
    }
}
