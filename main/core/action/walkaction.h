#ifndef WALKACTION_H
#define WALKACTION_H

#include "action.h"
#include "core/sprite/charactershadowsprite.h"

class WalkAction : public Action
{
    int cd;
    int x;
    CharacterShadowSprite* target;
public:
    WalkAction(CharacterShadowSprite* target);
    bool OneStep();
};

#endif // WALKACTION_H
