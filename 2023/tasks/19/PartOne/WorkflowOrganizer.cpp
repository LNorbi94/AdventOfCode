#include "WorkflowOrganizer.h"

#include "common/StringManipulation.h"

void WorkflowOrganizer::addWorkflow(std::string_view line)
{
    const auto &[name, rule] = common::splitString(std::string(line), "{");
    m_workflows[name] = Workflow{rule.substr(0, rule.size() - 1)};
}

void WorkflowOrganizer::addPart(std::string_view line)
{
    Part p;
    for (const auto &value : common::splitToMultipleString(line.substr(1, line.size() - 1), ','))
    {
        const auto &[category, rank] = common::splitString(value, "=");
        p.setCategory(category[0], std::stoi(rank));
    }
    m_parts.emplace_back(p);
}

int WorkflowOrganizer::getTotalPartsRanking() const
{
    int totalPartsRanking = 0;
    for (const auto &part : m_parts)
    {
        std::optional<bool> isAccepted;
        std::string nextWorkflow = "in";
        while (!isAccepted.has_value())
        {
            const auto result = m_workflows.at(nextWorkflow).processPart(part);
            if (std::holds_alternative<bool>(result))
            {
                isAccepted = std::get<bool>(result);
            }
            else
            {
                nextWorkflow = std::get<std::string>(result);
            }
        }
        if (isAccepted.value())
        {
            totalPartsRanking += part.getTotalRating();
        }
    }
    return totalPartsRanking;
}
