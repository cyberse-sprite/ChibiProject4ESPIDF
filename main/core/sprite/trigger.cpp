#include "trigger.h"

std::string Trigger::triggered(std::string name)
{
    if (triggers.find(name)!=triggers.end()){
        return triggers[name]();
    }
    return "";
}

void Trigger::triggeredAll()
{
    for(const auto &item:triggers){
        item.second();
    }
}

void Trigger::addTricker(std::string name, std::function<std::string ()> func)
{
    triggers[name]=func;
}

void Trigger::removeTricker(std::string name)
{
    triggers.erase(name);
}

void Trigger::clearTrickers()
{
    triggers.clear();
}
