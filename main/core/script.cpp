#include "script.h"
#include <core/utils/textutils.h>
#include "inf/file.h"

Script::Script(std::string name) {
    this->name=name;
    File file;
    bool ok=file.open(name,"r");
    if(!ok)return;
    while(!file.end()){
        std::string line=file.readLine();
        if(line[0]=='*'){
            tags[line.substr(1)]=lines.size();
        }else if(line[0]=='@'){
            lines.push_back(line);
        }
    }
    file.close();
}

bool Script::isEnd()
{
    return current>=lines.size();
}

void Script::next()
{
    if(!isEnd()){
        current++;
    }
}

void Script::jump(std::string label)
{
    if(tags.find(label)!=tags.end()){
        current=tags.at(label);
    }
}

Line Script::getCurrent()
{
    return Line(lines[current]);
}
