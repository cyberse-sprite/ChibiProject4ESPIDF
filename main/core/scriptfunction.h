#ifndef SCRIPTFUNCTION_H
#define SCRIPTFUNCTION_H

#include "core/actuator.h"
struct ScriptFunctionRes{
    bool res;
    bool next;
};
class ScriptFunction
{
public:
    static ScriptFunctionRes call(Actuator* act,Line line);
};

#endif // SCRIPTFUNCTION_H
