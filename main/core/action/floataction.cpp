#include "floataction.h"

FloatAction::FloatAction(CharacterShadowSprite* target,int speed)
{
    this->target=target;
    this->speed=speed;
    cd=0;
}

bool FloatAction::OneStep()
{
    cd+=1;
    cd=cd%(4*speed);
    if(cd%speed==0){
        target->shadow->oneStep();
        if(cd<2*speed){
            target->sprite->y-=1;
        }else{
            target->sprite->y+=1;
        }
    }
    return true;
}
