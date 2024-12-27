#pragma once

#include "PartRatings.h"

#include <string>
#include <optional>

class GenericWorkflowRule
{
public:
    GenericWorkflowRule(char comparationBase, char comparator, int comparationValue, std::string valueOnAccept);
    GenericWorkflowRule(std::string valueOnAccept);

    PartRatings getAcceptedRankings(const PartRatings &partRatings) const;
    std::optional<PartRatings> getRejectedRankings(const PartRatings &partRatings) const;

private:
    void changePartRatings(PartRatings &partRatings, bool accepted) const;

    char m_comparator = '\0';
    char m_comparationBase = '\0';
    int m_comparationValue = 0;
    std::string m_valueOnAccept;
};
