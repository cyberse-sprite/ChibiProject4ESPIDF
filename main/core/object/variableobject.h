#ifndef VARIABLEOBJECT_H
#define VARIABLEOBJECT_H

#include "core/variable.h"
#include <map>
#include <string>
class VariableObject
{
public:
    std::map<std::string,Variable> varis;
    VariableObject();
    int GetInt(std::string,int=0);
    std::string GetStr(std::string,std::string="");
    std::string GetRaw(std::string);
};

#endif // VARIABLEOBJECT_H
