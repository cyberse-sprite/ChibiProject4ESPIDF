#include "animationsprite.h"
#include "core/render.h"
#include "inf/log.h"

AnimationSprite::AnimationSprite(std::string name)
{
    this->name=name;
    init();
}

AnimationSprite::~AnimationSprite()
{
    STAGE->removeTricker(name);
}

AnimationSprite::AnimationSprite(Image *image,Sheet* sheet,std::string name)
{
    this->name=name;
    this->sheet=sheet;
    this->SetTextures(image);
    init();
}

void AnimationSprite::init()
{
    target=0;
    offset=0;
    frame_target=0;
    speed=1;
    cd=0;
    anchor=0;
    loop=-1;
    playing=true;
}

void AnimationSprite::LoadSheet(Sheet* sheet)
{
    this->sheet=sheet;
}

void AnimationSprite::SetTextures(Image * image)
{
    textures.clear();
    while(image!=nullptr){
        textures.push_back(image);
        image=image->next;
    }
}

void AnimationSprite::PushTextures(Image * image)
{
    textures.push_back(image);
}

void AnimationSprite::paintEvent(PaintEvent *event)
{
    if(!visible)return;
    RENDER->drawImage(textures[target],event->x+x,event->y+y,anchor);
    Container::paintEvent(event);
}

void AnimationSprite::oneStep()
{
    cd-=1;
    if(cd<=0&&loop!=0){
        frame_target+=1;
        if (frame_target>=sheet->frames.size()){
            loop-=1;
            frame_target=0;
        }
        if(loop!=0){
            Frame frame=sheet->frames[frame_target];
            target=(frame.index+offset)%textures.size();
            cd=frame.time*speed;
        }
    }
}

void AnimationSprite::setOffset(int offset)
{
    if(this->offset!=offset){cd=0;}
    this->offset=offset;
}



