#include "Workflow.h"

#include <sstream>

Workflow::Workflow(std::string_view input)
{
    std::string nextRule;
    std::stringstream ss{ input.data() };
    while (std::getline(ss, nextRule, ',')) {
        if (nextRule.contains(':')) {
            const auto comparationBase = nextRule[0];
            const auto comparator = nextRule[1];

            const auto colonLocation = nextRule.find(':');
            const auto comparationValue = std::stoi(nextRule.substr(2, colonLocation - 2));
            const auto valueOnAccept = nextRule.substr(colonLocation + 1);
            m_rules.emplace_back(comparationBase, comparator, comparationValue, valueOnAccept);
        } else {
            m_rules.emplace_back(nextRule);
        }
    }
}

std::variant<bool, std::string> Workflow::processPart(const Part& part) const
{
    for (const auto& rule : m_rules) {
        auto result = rule.evaluatePart(part);
        if (result.has_value()) {
            if (result.value() == "A") {
                return true;
            } else if (result.value() == "R") {
                return false;
            } else {
                return result.value();
            }
        }
    }
    return false;
}
