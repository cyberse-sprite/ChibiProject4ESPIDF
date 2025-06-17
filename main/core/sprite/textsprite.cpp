#include "textsprite.h"
#include "core/render.h"

TextSprite::TextSprite() {}

TextSprite::TextSprite(std::string text)
{
    SetText(text);
}

void TextSprite::SetText(std::string text)
{
    this->text=text;
}

void TextSprite::paintEvent(PaintEvent *event)
{
    if(!visible)return;
    RENDER->drawTextPix(text,event->x+x,event->y+y);
    Container::paintEvent(event);
}
