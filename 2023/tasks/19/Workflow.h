#pragma once

#include "Part.h"
#include "WorkflowRule.h"

#include <string>
#include <variant>
#include <vector>

class Workflow
{
public:
    Workflow() = default;
    Workflow(std::string_view input);

    std::variant<bool, std::string> processPart(const Part& part) const;

private:
    std::vector< WorkflowRule > m_rules;
};
