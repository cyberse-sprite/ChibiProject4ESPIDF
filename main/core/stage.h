#ifndef STAGE_H
#define STAGE_H

#include "core/action/action.h"
#include "core/sprite/container.h"

class Stage:public Container
{
    std::vector<Action*> actions;
public:
    Stage();
    void Fresh();
    void addAction(Action* action);
};

extern Stage* STAGE;

#endif // STAGE_H
