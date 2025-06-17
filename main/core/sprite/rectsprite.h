#ifndef RECTSPRITE_H
#define RECTSPRITE_H

#include "container.h"

class RectSprite : public Container
{
public:
    int width;
    int height;
    RectSprite();
    void setRect(int x,int y,int w,int h);
    void paintEvent(PaintEvent *event);
};

#endif // RECTSPRITE_H
