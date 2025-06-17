#ifndef CHARACTERSPRITE_H
#define CHARACTERSPRITE_H

#include "container.h"
#include "core/object/characterobject.h"
#include "core/sprite/animationsprite.h"

class CharacterSprite : public Container
{
    CharacterObject* obj;
public:
    AnimationSprite* pop;
    AnimationSprite* emotion;
    std::list<AnimationSprite*> parts;
    CharacterSprite();
    CharacterSprite(CharacterObject* c,int x=0,int y=0);
    void init();
    void FreshParts();
    void playPop();
    void playEmotion(std::string name);
    void Selected();
    void setOffset(int offset);
};

#endif // CHARACTERSPRITE_H
