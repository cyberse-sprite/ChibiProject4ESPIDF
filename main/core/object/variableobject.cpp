#include "variableobject.h"

VariableObject::VariableObject() {}

int VariableObject::GetInt(std::string key,int value)
{
    if(varis.find(key)!=varis.end()){
        return varis[key].ToInt();
    }
    return value;
}

std::string VariableObject::GetStr(std::string key,std::string value)
{
    if(varis.find(key)!=varis.end()){
        return varis[key].ToStr();
    }
    return value;
}

std::string VariableObject::GetRaw(std::string key)
{
    if(varis.find(key)!=varis.end()){
        return varis[key].getRowData();
    }
    return "\"\"";
}
