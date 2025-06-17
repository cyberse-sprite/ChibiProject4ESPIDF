#include "equip.h"
#include "core/script.h"

Equip LoadEquip(std::string name)
{
    Script s("equip/"+name);
    Equip e{name,name};
    for(auto str:s.lines){
        Line line(str);
        e.parts.push_back(Part{line.GetStr("image"),line.GetInt("z")});
    }
    return e;
}
