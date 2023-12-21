#pragma once

#include "Part.h"

#include <string>
#include <optional>

class WorkflowRule
{
public:
    WorkflowRule(char comparationBase, char comparator, int comparationValue, std::string valueOnAccept);
    WorkflowRule(std::string valueOnAccept);

    std::optional<std::string> evaluatePart(const Part& part) const;

private:
    bool acceptsPart(const Part& part) const;

    char m_comparator = '\0';
    char m_comparationBase = '\0';
    int m_comparationValue = 0;
    std::string m_valueOnAccept;
};
