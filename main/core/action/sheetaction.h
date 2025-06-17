#ifndef SHEETACTION_H
#define SHEETACTION_H

#include "action.h"
#include "core/sprite/animationsprite.h"

class SheetAction : public Action
{
    AnimationSprite* target;
public:
    SheetAction(AnimationSprite* target);
    bool OneStep();
};

#endif // SHEETACTION_H
