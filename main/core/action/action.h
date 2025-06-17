#ifndef ACTION_H
#define ACTION_H

class Action
{
public:
    Action();
    virtual bool OneStep()=0;
};

#endif // ACTION_H
