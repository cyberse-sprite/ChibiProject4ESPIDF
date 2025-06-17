#include "stage.h"

Stage::Stage() {
}

void Stage::Fresh()
{
    triggeredAll();
    auto action=actions.begin();
    while(action!=actions.end()){
        bool res=(*action)->OneStep();
        if(res){
            action++;
        }else{
            action=actions.erase(action);
        }
    }
}

void Stage::addAction(Action *action)
{
    actions.push_back(action);
}
