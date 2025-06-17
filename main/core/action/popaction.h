#ifndef POPACTION_H
#define POPACTION_H

#include "action.h"
#include "core/sprite/charactersprite.h"

class PopAction : public Action
{
    CharacterSprite* target;
    int cd;
    std::string emotion;
public:
    PopAction(CharacterSprite* target,std::string emotion);
    bool OneStep();
};

#endif // POPACTION_H
