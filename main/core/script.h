#ifndef SCRIPT_H
#define SCRIPT_H

#include "core/line.h"
#include <map>
#include <string>
#include <vector>
class Script
{
public:
    Script(std::string name);
    std::string name;
    int current=0;
    std::map<std::string,int> tags;
    std::vector<std::string> lines;
    bool isEnd();
    void next();
    void jump(std::string label);
    Line getCurrent();
};

#endif // SCRIPT_H
