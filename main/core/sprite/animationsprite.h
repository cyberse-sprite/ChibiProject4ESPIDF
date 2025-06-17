#ifndef SIMPLEANIMATIONSPRITE_H
#define SIMPLEANIMATIONSPRITE_H

#include "container.h"
#include "core/data/image.h"

struct Frame{
    int index;
    int x;
    int y;
    int time;
};

class Sheet{
public:
    std::vector<Frame> frames;
};

class AnimationSprite : public Container
{
public:
    int cd;
    int loop;
    int target;
    int frame_target;
    int speed;
    int offset;
    bool playing;
    Sheet* sheet;
    std::vector<Image*> textures;
    AnimationSprite(std::string name);
    ~AnimationSprite();
    AnimationSprite(Image*,Sheet*,std::string);
    void init();
    void LoadSheet(Sheet* sheet);
    void SetTextures(Image*);
    void PushTextures(Image*);
    void paintEvent(PaintEvent *event);
    void oneStep();
    void setOffset(int offset);
};

#endif // SIMPLEANIMATIONSPRITE_H
