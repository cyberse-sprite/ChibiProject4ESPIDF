#include "line.h"
#include <vector>
#include <core/utils/textutils.h>
#include "archive.h"

Line::Line(std::string str) {
    std::vector<std::string> list=TextUtils::split(str,' ');
    for(const auto &temp:list){
        if(name==""){
            name=temp.substr(1,temp.size());
        }else{
            size_t pos2=temp.find('=');
            varis[temp.substr(0,pos2)]=Variable(temp.substr(pos2+1,temp.size()));
        }
    }
}

std::string Line::GetName()
{
    return name;
}

bool Line::GetIf(){
    std::string str=varis["if"].ToStr();
    if(str=="")return true;
    int p = str.find('=');
    std::string vari = str.substr(0, p);
    std::string value = str.substr(p + 1);
    if (value[0] == '\'')
    {
        return value.substr(1, value.size() - 2) == ARC->varis[vari].ToStr();
    }
    else
    {
        return stoi(value) == ARC->varis[vari].ToInt();
    }
    return false;
}
