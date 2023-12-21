#pragma once

#include "Workflow.h"

#include <map>

class WorkflowOrganizer
{
public:
    void addWorkflow(std::string_view line);
    void addPart(std::string_view line);

    int getTotalPartsRanking() const;

private:
    std::map< std::string, Workflow > m_workflows;
    std::vector< Part > m_parts;
};
