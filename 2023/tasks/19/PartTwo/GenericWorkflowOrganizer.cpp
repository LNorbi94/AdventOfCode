#include "GenericWorkflowOrganizer.h"

#include <queue>

#include "common/StringManipulation.h"
#include <numeric>

void GenericWorkflowOrganizer::addWorkflow(std::string_view line)
{
    const auto &[name, rule] = common::splitString(line, '{');
    m_workflows[name] = GenericWorkflow{rule.substr(0, rule.size() - 1)};
}

void GenericWorkflowOrganizer::determineAcceptedPartRatings()
{
    PartRatings partRatings;
    partRatings.setRule("in");
    std::queue<PartRatings> partRatingsToProcess;
    partRatingsToProcess.push(partRatings);
    while (!partRatingsToProcess.empty())
    {
        auto currentPartRatings = partRatingsToProcess.front();
        partRatingsToProcess.pop();
        const auto newRatings = m_workflows.at(currentPartRatings.getRule()).applyRule(currentPartRatings);
        for (const auto &newRating : newRatings)
        {
            if (newRating.getRule() == "A")
            {
                m_acceptedPartRatings.push_back(newRating);
            }
            else if (newRating.getRule() != "R")
            {
                partRatingsToProcess.push(newRating);
            }
        }
    }
}

int64_t GenericWorkflowOrganizer::getNumberOfCombinations() const
{
    int64_t combinations = 0;
    for (const auto &rating : m_acceptedPartRatings)
    {
        combinations += rating.getNumberOfCombinations();
    }
    return combinations;
}
