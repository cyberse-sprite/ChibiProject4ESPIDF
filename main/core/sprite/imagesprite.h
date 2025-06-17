#ifndef IMAGESPRITE_H
#define IMAGESPRITE_H

#include "container.h"
#include "core/data/image.h"

class ImageSprite : public Container
{
public:
    ImageSprite(Image* image,std::string n="",Container* parent=nullptr);
    Image* image;
    void paintEvent(PaintEvent *event);
};

#endif // IMAGESPRITE_H
