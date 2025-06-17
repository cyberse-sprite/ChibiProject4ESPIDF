#include "variable.h"
#include "core/archive.h"

Variable::Variable() {}

Variable::Variable(std::string str)
{
    SetContent(str);
}

void Variable::SetContent(std::string str)
{
    content=str;
    if(content[0]=='"'){
        content=content.substr(1,content.size()-2);
        type=VariableType::STR;
    }else if(content[0]=='['){
        content=content.substr(1,content.size()-2);
        type=VariableType::TAG;
    }else{
        type=VariableType::INT;
    }
}

int Variable::ToInt()
{
    if(type==VariableType::TAG){
        return ARC->varis[content].ToInt();
    }
    if(content==""){return 0;}
    return std::stoi(content);
}

std::string Variable::ToStr()
{
    if(type==VariableType::TAG){
        return ARC->varis[content].ToStr();
    }
    return content;
}

bool Variable::ToBool()
{
    if(type==VariableType::INT){
        return ToInt();
    }else if(type==VariableType::STR){
        return (content!="");
    }
    return false;
}

std::string Variable::getRowData()
{
    if(type==VariableType::STR){
        return "\""+content+"\"";
    }else if(type==VariableType::TAG){
        return "["+content+"]";
    }
    return content;
}

bool Variable::isType(VariableType value)
{
    return type==value;
}
