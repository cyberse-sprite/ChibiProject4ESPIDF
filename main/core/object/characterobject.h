#ifndef CHARACTER_H
#define CHARACTER_H

#include "core/object/variableobject.h"
#include <list>
#include <map>
#include <string>

class CharacterObject:public VariableObject
{
public:
    std::string key;
    std::map<std::string,std::string> equips;
    std::list<std::string> scopes;
    CharacterObject(std::string key);
    void addEquip(std::string equip,std::string name);
    std::string getEquip(std::string key);
    void removeEquip(std::string name);
    //TODO 改变宠物的随机刷新模式
    void addScope(std::string name);
    void removeScope(std::string name);
    std::string getRowData();
};

#endif // CHARACTER_H
