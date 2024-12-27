#include "WorkflowRule.h"

WorkflowRule::WorkflowRule(char comparationBase, char comparator, int comparationValue, std::string valueOnAccept)
    : m_comparationBase{ comparationBase }
    , m_comparator{ comparator }
    , m_comparationValue{ comparationValue }
    , m_valueOnAccept{ valueOnAccept }
{
}

WorkflowRule::WorkflowRule(std::string valueOnAccept)
    : m_valueOnAccept{ valueOnAccept }
{
}

std::optional<std::string> WorkflowRule::evaluatePart(const Part& part) const
{
    if (acceptsPart(part)) {
        return m_valueOnAccept;
    }
    return {};
}

bool WorkflowRule::acceptsPart(const Part& part) const
{
    switch (m_comparator)
    {
    case '<':
        return part.getCategory(m_comparationBase) < m_comparationValue;
    case '>':
        return part.getCategory(m_comparationBase) > m_comparationValue;
    default:
        break;
    }
    return true;
}
