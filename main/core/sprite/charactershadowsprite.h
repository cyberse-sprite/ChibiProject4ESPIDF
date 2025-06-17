#ifndef CHARACTERSHADOWSPRITE_H
#define CHARACTERSHADOWSPRITE_H

#include "container.h"
#include "core/sprite/charactersprite.h"

class CharacterShadowSprite : public Container
{
public:
    CharacterSprite* sprite;
    AnimationSprite* shadow;
    CharacterShadowSprite(CharacterSprite* c,int x=64,int y=95);
};

#endif // CHARACTERSHADOWSPRITE_H
