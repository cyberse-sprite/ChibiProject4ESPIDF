#include "moveaction.h"
#include "math.h"

MoveAction::MoveAction(Container* target,int x,int y,int time) {
    this->target=target;
    this->x=x;
    this->y=y;
    this->x_step=std::ceil(abs(x-target->x)/time);
    this->y_step=std::ceil(abs(y-target->y)/time);
}

bool MoveAction::OneStep()
{
    int x_dis=x-target->x;
    int y_dis=y-target->y;
    if(x_dis){
        if(abs(x_dis)<x_step){
            target->x=x;
        }else{
            target->x+=x_dis/abs(x_dis)*x_step;
        }
    }
    if(y_dis){
        if(abs(y_dis)<y_step){
            target->y=y;
        }else{
            target->y+=y_dis/abs(y_dis)*y_step;
        }
    }
    return x_dis||y_dis;
}
