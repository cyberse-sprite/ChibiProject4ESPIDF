#include "sheetassets.h"
#include "inf/file.h"
#include "core/utils/textutils.h"

SheetAssets::SheetAssets()
{
    Sheet sheet;
    for(int i=0;i<1;i++){
        sheet.frames.push_back(Frame{i,0,0,1});
    }
    items.insert(std::make_pair("",sheet));
}

Sheet *SheetAssets::get(std::string name,int num){
    auto i=items.find(name);
    if(i!=items.end()){
        return &(i->second);
    }
    if(name=="step")return getStep(num);
    return load(name);
}

Sheet* SheetAssets::load(std::string name)
{
    Sheet s;
    File file;
    file.open("sheet/"+name,"r");
    while(!file.end()){
        std::vector<std::string> items=TextUtils::split(file.readLine(),',');
        if(items.size()<4)continue;
        s.frames.push_back(Frame{stoi(items[0]),stoi(items[1]),stoi(items[2]),stoi(items[3])});
    }
    file.close();
    items.insert(std::make_pair(name,s));
    return &items.at(name);
}

Sheet *SheetAssets::getStep(int num)
{
    std::string name="step_"+std::to_string(num);
    auto i=items.find(name);
    if(i!=items.end()){
        return &(i->second);
    }
    Sheet* sheet=&items[name];
    for(int i=0;i<num;i++){
        sheet->frames.push_back(Frame{i,0,0,1});
    }
    return sheet;
}
