#ifndef RENDER_H
#define RENDER_H

#include "core/font.h"
#include "core/stage.h"
#include "data/image.h"
class Render
{
    Font font;
public:
    Render(int w,int h);
    Stage* stage;
    uint16_t* canvas;
    int width;
    int height;
    void drawImage(Image* img,int x=0,int y=0,int a=0,int r=0);
    void drawImage565(Image* img,int x,int y,int a,int r);
    void fresh();
    void drawRect(int w,int h,int x=0,int y=0,uint16_t color=0xffff);
    void drawPixChar(PixChar c,int x,int y,RGBA color);
    void drawTextPix(std::string text,int x=0,int y=0,uint16_t color=0x0000);
    void setPix(int x,int y,uint16_t pix);
};

extern Render* RENDER;

#endif // RENDER_H
