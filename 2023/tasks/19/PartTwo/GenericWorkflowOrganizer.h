#pragma once

#include "PartRatings.h"
#include "GenericWorkflow.h"

#include <map>
#include <string>

class GenericWorkflowOrganizer
{
public:
    void addWorkflow(std::string_view line);

    void determineAcceptedPartRatings();

    int64_t getNumberOfCombinations() const;

private:
    std::map<std::string, GenericWorkflow> m_workflows;
    std::vector<PartRatings> m_acceptedPartRatings;
};
