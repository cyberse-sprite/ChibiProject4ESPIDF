#include "walkaction.h"
#include <ctime>
#include <random>


WalkAction::WalkAction(CharacterShadowSprite *target)
{
    this->target=target;
    x=target->x;
    cd=0;
}

bool WalkAction::OneStep()
{
    cd-=1;
    for(auto part:target->sprite->parts){
        part->oneStep();
    }
    if(cd<=0){
        std::default_random_engine e(time(NULL));
        std::uniform_int_distribution<int> u(32, 96);
        while(abs(x-target->x)<20){
            x=u(e);
        }
        cd=u(e);
    }else{
        int dis=x-target->x;
        if(dis>0){
            target->sprite->setOffset(6);
            target->x+=1;
        }else if(dis==0){
            target->sprite->setOffset(0);
        }else{
            target->sprite->setOffset(3);
            target->x-=1;
        }
    }
    return true;
}
