#include "actuator.h"
#include "core/game.h"
#include "scriptfunction.h"

void Actuator::run()
{
    GAME->running=true;
    while (next())
    {
        if (cd != 0)
            break;
    }
    GAME->running=false;
}

bool Actuator::next()
{
    ScriptFunctionRes res = excu();
    if (res.next)
        scripts.top()->next();
    return res.res;
}

ScriptFunctionRes Actuator::excu()
{
    Line line = scripts.top()->getCurrent();
    if (line.GetIf())
        return ScriptFunction::call(this, line);
    return ScriptFunctionRes{true, true};
}

void Actuator::callScript(std::string label, std::string file)
{
    if (file == "" && scripts.size() > 0)
        file = scripts.top()->name;
    Script* s=new Script(file);
    s->jump(label);
    scripts.push(s);
}

void Actuator::callReturn(int depth)
{
    depth += 1;
    for (int i = 0; i < depth; i++)
    {
        if (scripts.size() <= 1)
            break;
        delete scripts.top();
        scripts.pop();
    }
}

void Actuator::jumpScript(std::string label, std::string file, int depth)
{
    callReturn(depth);
    callScript(label, file);
}

void Actuator::Trigger(std::string name)
{
    if (!canTrigger)
        return;
    if (events.find(name) == events.end())
        return;
    Target t = events[name];
    callScript(t.label, t.file);
    run();
}

void Actuator::Fresh()
{
    if (cd > 0)
    {
        cd--;
        if (cd <= 0)
        {
            run();
        }
    }
}
