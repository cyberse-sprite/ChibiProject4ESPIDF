#ifndef FLOATACTION_H
#define FLOATACTION_H

#include "action.h"
#include "core/sprite/charactershadowsprite.h"

class FloatAction : public Action
{
    CharacterShadowSprite* target;
    int speed;
    int cd;
public:
    FloatAction(CharacterShadowSprite* target,int speed=2);
    bool OneStep();
};

#endif // FLOATACTION_H
