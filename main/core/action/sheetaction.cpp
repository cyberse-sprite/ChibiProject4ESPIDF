#include "sheetaction.h"

SheetAction::SheetAction(AnimationSprite *target)
{
    this->target=target;
}

bool SheetAction::OneStep()
{
    this->target->oneStep();
    return this->target->playing;
}
