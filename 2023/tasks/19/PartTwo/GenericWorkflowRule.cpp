#include "GenericWorkflowRule.h"

GenericWorkflowRule::GenericWorkflowRule(char comparationBase, char comparator, int comparationValue, std::string valueOnAccept)
    : m_comparationBase{comparationBase}, m_comparator{comparator}, m_comparationValue{comparationValue}, m_valueOnAccept{valueOnAccept}
{
}

GenericWorkflowRule::GenericWorkflowRule(std::string valueOnAccept)
    : m_valueOnAccept{valueOnAccept}
{
}

PartRatings GenericWorkflowRule::getAcceptedRankings(const PartRatings &partRatings) const
{
    auto newPartRatings = partRatings;
    changePartRatings(newPartRatings, true);
    return newPartRatings;
}

std::optional<PartRatings> GenericWorkflowRule::getRejectedRankings(const PartRatings &partRatings) const
{
    if (m_comparator == '\0')
    {
        return std::nullopt;
    }

    auto newPartRatings = partRatings;
    changePartRatings(newPartRatings, false);
    return newPartRatings;
}

void GenericWorkflowRule::changePartRatings(PartRatings &partRatings, bool accepted) const
{
    switch (m_comparator)
    {
    case '<':
    {
        if (accepted)
        {
            partRatings.setRating(m_comparationBase, m_comparationValue - 1, PartRatings::RangeType::End);
            partRatings.setRule(m_valueOnAccept);
        }
        else
        {
            partRatings.setRating(m_comparationBase, m_comparationValue, PartRatings::RangeType::Start);
        }
        break;
    }
    case '>':
        if (accepted)
        {
            partRatings.setRating(m_comparationBase, m_comparationValue + 1, PartRatings::RangeType::Start);
            partRatings.setRule(m_valueOnAccept);
        }
        else
        {
            partRatings.setRating(m_comparationBase, m_comparationValue, PartRatings::RangeType::End);
        }
        break;
    default:
        partRatings.setRule(m_valueOnAccept);
        break;
    }
}
