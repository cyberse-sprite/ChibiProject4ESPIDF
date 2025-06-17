#include "popaction.h"

PopAction::PopAction(CharacterSprite* target,std::string emotion) {
    this->target=target;
    this->emotion=emotion;
    cd=20;
}

bool PopAction::OneStep()
{
    if(cd==20){
        target->playPop();
    }else{
        target->pop->oneStep();
    }
    if(cd==17){
        target->playEmotion(emotion);
    }else if(cd<17){
        target->emotion->oneStep();
    }
    if(cd==1){
        target->removeChild(target->name+"_"+emotion);
        target->removeChild(target->name+"_pop");
    }
    cd--;
    if(cd)return true;
    return false;
}
