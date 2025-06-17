#include "characterobject.h"

CharacterObject::CharacterObject(std::string key)
{
    this->key=key;
}

void CharacterObject::addEquip(std::string equip, std::string name)
{
    equips[name]=equip;
}

std::string CharacterObject::getEquip(std::string key)
{
    if(equips.find(key)!=equips.end()){
        return equips.at(key);
    }
    return "none";
}

void CharacterObject::removeEquip(std::string name)
{
    equips.erase(name);
}

void CharacterObject::addScope(std::string name)
{
    scopes.push_back(name);
}

void CharacterObject::removeScope(std::string name)
{
    scopes.remove(name);
}

std::string CharacterObject::getRowData()
{
    //TODO 写出完整还原规则
    return "";
}
