#include "IModule.h"

void IModule::setModuleName(const std::string &name)
{
    moduleName = name;
}

void IModule::addInput(const std::string &)
{
}

std::vector<std::string> IModule::getInputs() const
{
    return {};
}
