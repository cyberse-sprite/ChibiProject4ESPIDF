#ifndef IMAGE_ASSETS_H
#define IMAGE_ASSETS_H

#include "core/data/image.h"
#include <map>
#include <string>

class ImageAssets
{
    std::map<std::string,Image*> items;
public:
    Image* get(std::string name);
    void add(std::string name,Image* image);
    Image* load(std::string name);
    void clear();
    void releaseImage(Image*);
};

extern ImageAssets* IMG;

#endif // ASSETS_H
