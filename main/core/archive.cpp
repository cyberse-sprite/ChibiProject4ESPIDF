#include "archive.h"
#include "core/actuator.h"

Archive::Archive() {
}

std::string Archive::getData()
{
    std::string data="";
    for(auto vari:varis){
        std::string line="@setVari name=\""+vari.first+"\" value="+vari.second.getRowData();
        data+=line+"\n";
    }
    for(auto character:characters){
        std::string line="@setCharacter name=\""+character.first+"\" value=\""+character.second.getRowData()+"\"";
        data+=line+"\n";
    }
    return data;
}

void Archive::setData(std::string data)
{
    // Actuator a("saves/data");
    // a.Run();
}
