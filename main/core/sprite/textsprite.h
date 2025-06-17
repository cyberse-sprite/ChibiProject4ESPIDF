#ifndef TEXTSPRITE_H
#define TEXTSPRITE_H

#include "container.h"

class TextSprite : public Container
{
public:
    TextSprite();
    TextSprite(std::string text);
    std::string text;
    int start;
    int current;
    int width;
    int height;
    void SetText(std::string text);
    void paintEvent(PaintEvent *event);
};

#endif // TEXTSPRITE_H
