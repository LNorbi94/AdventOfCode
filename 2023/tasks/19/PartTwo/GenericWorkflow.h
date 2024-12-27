#pragma once

#include "PartRatings.h"
#include "GenericWorkflowRule.h"

#include <string>
#include <variant>
#include <vector>

class GenericWorkflow
{
public:
    GenericWorkflow() = default;
    GenericWorkflow(std::string_view input);

    std::vector<PartRatings> applyRule(const PartRatings &partRatings) const;

private:
    std::vector<GenericWorkflowRule> m_rules;
};
