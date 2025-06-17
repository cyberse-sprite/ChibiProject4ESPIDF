#ifndef SHEETASSETS_H
#define SHEETASSETS_H

#include "core/sprite/animationsprite.h"

class SheetAssets
{
    std::map<std::string,Sheet> items;
public:
    SheetAssets();
    Sheet* get(std::string name,int num=0);
    Sheet* load(std::string name);
    Sheet* getStep(int num);
};

extern SheetAssets* SHEET;

#endif // SHEETASSETS_H
