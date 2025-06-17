#ifndef MOVEACTION_H
#define MOVEACTION_H

#include "action.h"
#include "core/sprite/container.h"

class MoveAction : public Action
{
    Container* target;
    int x;
    int y;
    int x_step;
    int y_step;
public:
    MoveAction(Container* target,int x,int y,int time=1);
    bool OneStep();
};

#endif // MOVEACTION_H
