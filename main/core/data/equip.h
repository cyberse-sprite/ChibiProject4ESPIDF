#ifndef EQUIP_H
#define EQUIP_H

#include <list>
#include <string>
struct Part{
    std::string image;
    int z;
};

struct Equip
{
    std::string key;
    std::string name;
    std::list<Part> parts;

};

Equip LoadEquip(std::string);

#endif // EQUIP_H
