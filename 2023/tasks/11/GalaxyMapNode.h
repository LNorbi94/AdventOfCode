#pragma once

#include "common/Graphs/Node.h"

#include "NodeType.h"

class GalaxyMapNode : public Node
{
public:
    GalaxyMapNode(Id id, const char type);

    void setLength(int length);
    int length() const;

    NodeType getType() const;

private:
    NodeType m_type = NodeType::Unknown;
    int m_length = 1;
};
