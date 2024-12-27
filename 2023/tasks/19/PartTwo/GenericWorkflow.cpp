#include "GenericWorkflow.h"

#include <sstream>

GenericWorkflow::GenericWorkflow(std::string_view input)
{
    std::string nextRule;
    std::stringstream ss{input.data()};
    while (std::getline(ss, nextRule, ','))
    {
        if (nextRule.contains(':'))
        {
            const auto comparationBase = nextRule[0];
            const auto comparator = nextRule[1];

            const auto colonLocation = nextRule.find(':');
            const auto comparationValue = std::stoi(nextRule.substr(2, colonLocation - 2));
            const auto valueOnAccept = nextRule.substr(colonLocation + 1);
            m_rules.emplace_back(comparationBase, comparator, comparationValue, valueOnAccept);
        }
        else
        {
            m_rules.emplace_back(nextRule);
        }
    }
}

std::vector<PartRatings> GenericWorkflow::applyRule(const PartRatings &partRatings) const
{
    std::vector<PartRatings> splitPartRatings;
    auto nextPartRatingsToProcess = partRatings;
    for (const auto &rule : m_rules)
    {
        auto result = rule.getAcceptedRankings(nextPartRatingsToProcess);
        splitPartRatings.push_back(result);
        auto oRejectedRankings = rule.getRejectedRankings(nextPartRatingsToProcess);
        if (oRejectedRankings.has_value())
        {
            nextPartRatingsToProcess = oRejectedRankings.value();
        }
    }
    return splitPartRatings;
}
