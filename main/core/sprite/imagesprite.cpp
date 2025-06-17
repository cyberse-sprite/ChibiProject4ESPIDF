#include "imagesprite.h"
#include "core/render.h"

ImageSprite::ImageSprite(Image* image,std::string n, Container *parent):Container(n,parent) {
    this->image=image;
}

void ImageSprite::paintEvent(PaintEvent *event)
{
    if(!visible)return;
    RENDER->drawImage(image,event->x+x,event->y+y,this->anchor);
    Container::paintEvent(event);
}
