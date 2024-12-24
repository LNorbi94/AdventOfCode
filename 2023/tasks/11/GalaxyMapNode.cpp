#include "GalaxyMapNode.h"

GalaxyMapNode::GalaxyMapNode(Id id, const char type)
    : Node{ std::move(id) }
{
    switch (type) {
        case '#':
            m_type = NodeType::Galaxy;
            break;
        case '.':
            m_type = NodeType::EmptySpace;
            break;
    }
}

void GalaxyMapNode::setLength(int length)
{
    if (length != m_length) {
        m_length = length;
    }
}

int GalaxyMapNode::length() const
{
    return m_length;
}

NodeType GalaxyMapNode::getType() const
{
    return m_type;
}
