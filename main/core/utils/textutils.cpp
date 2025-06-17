#include "textutils.h"

std::vector<std::string> TextUtils::split(std::string str,char split){
    std::vector<std::string> res;
    std::string temp = "";

    for(char c:str){
        if(c==split){
            res.push_back(temp);
            temp="";
        }else if(c!='\r'){
            temp+=c;
        }
    }
    res.push_back(temp);
    return res;
}
