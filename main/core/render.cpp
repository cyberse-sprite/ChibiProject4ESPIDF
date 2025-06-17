#include "render.h"
#include "stage.h"

Render::Render(int w,int h){
    width=w;
    height=h;
    canvas=new uint16_t[w*h];
}

void Render::drawImage(Image *img,int x, int y,int a,int r)
{
    int hor=a%3;
    int ver=(a-a%3)/3;
    x-=img->w*((float)hor/2);
    y-=img->h*((float)ver/2);
    if(img->type==0){
        drawImage565(img,x,y,r,a);
    }
}

void Render::drawImage565(Image *img, int x, int y, int a, int r)
{
    x+=img->x;
    y+=img->y;
    int sx=x;if(sx<0)sx=0;int ssx=sx;
    int sy=y;if(sy<0)sy=0;
    int tx=x+img->dw;if(tx>width)tx=width;
    int ty=y+img->dh;if(ty>height)ty=height;
    while(sy<ty){
        while(sx<tx){
            int t=sy*width+sx;
            int s=(sy-y)*img->dw+sx-x;
            RGBA color=RGBA(canvas[t])+RGBA(img->data[s],img->alpha[s]);
            canvas[t]=color.getColor();
            sx++;
        }
        sy++;
        sx=ssx;
    }
}

void Render::fresh()
{
    STAGE->paintEvent(new PaintEvent);
}

void Render::drawRect(int w, int h, int x, int y, uint16_t color)
{
    for(int i=0;i<w;i++){
        setPix(x+i,y,color);
        setPix(x+i,y+h-1,color);
    }
    for(int j=0;j<h;j++){
        setPix(x,y+j,color);
        setPix(x+w-1,y+j,color);
    }
}

void Render::drawPixChar(PixChar c, int x, int y,RGBA color)
{
    for(int j=0;j<12;j++){
        for(int i=0;i<12;i++){
            int n=(j*12+i);
            if(c.content[n]){
                canvas[(y+j)*width+x+i]=color.getColor();
            }
        }
    }
}

void Render::drawTextPix(std::string text, int x, int y, uint16_t color)
{
    int i=0;
    while(i<text.size()){
        if((unsigned char)text[i]>127){
            PixChar c=font.getPixChar(text.substr(i,3));
            drawPixChar(c,x,y,font.defaultColor);
            x+=12;
            i+=3;
        }else{
            x++;
            PixChar c=font.getPixChar((unsigned char)text[i]);
            drawPixChar(c,x,y,font.defaultColor);
            x+=(c.width-3);
            i++;
        }
    }
}

void Render::setPix(int x, int y, uint16_t pix)
{
    int target=y*width+x;
    if(target<0||target>(width*height))return;
    canvas[target]=pix;
}


