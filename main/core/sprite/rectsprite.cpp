#include "rectsprite.h"
#include "core/render.h"


RectSprite::RectSprite() {
    this->height=0;
    this->width=0;
}

void RectSprite::setRect(int x, int y, int w, int h)
{
    this->x=x;
    this->y=y;
    width=w;
    height=h;
}

void RectSprite::paintEvent(PaintEvent *event)
{
    if(!visible)return;
    RENDER->drawRect(width,height,event->x+x,event->y+y);
}
