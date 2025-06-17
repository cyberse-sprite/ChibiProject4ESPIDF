#ifndef ACTUATOR_H
#define ACTUATOR_H

#include "core/script.h"
#include <stack>

struct Target{
    std::string label;
    std::string file;
};
struct ScriptFunctionRes;
class Actuator
{
public:
    int cd=0;
    bool canTrigger=true;
    std::stack<Script*> scripts;
    std::map<std::string,Target> events;
    void run();
    bool next();
    ScriptFunctionRes excu();
    //操作
    void callScript(std::string label,std::string file="");
    void callReturn(int depth=0);
    void jumpScript(std::string label,std::string file="",int depth=0);
    //
    void Trigger(std::string name);
    //
    void Fresh();
};

extern Actuator* ACT;

#endif // ACTUATOR_H
