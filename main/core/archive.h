#ifndef ARCHIVE_H
#define ARCHIVE_H

#include "core/object/characterobject.h"
#include <map>
#include <string>
class Archive:public VariableObject
{
public:
    Archive();
    std::map<std::string,CharacterObject> characters;
    std::string getData();
    void setData(std::string data);
};

extern Archive* ARC;

#endif // ARCHIVE_H
