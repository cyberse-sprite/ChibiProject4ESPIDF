#include "charactershadowsprite.h"
#include "core/assets/imageassets.h"
#include "core/assets/sheetassets.h"

CharacterShadowSprite::CharacterShadowSprite(CharacterSprite *c, int x, int y)
{
    this->anchor=7;
    this->sprite=c;
    shadow=new AnimationSprite(IMG->get("shadow_0"),SHEET->getStep(4),name+"_shadow");
    shadow->z=-99;
    shadow->x=0;
    shadow->y=2;
    shadow->anchor=7;
    pushChild(shadow);
    pushChild(this->sprite);
    this->x=x;
    this->y=y;
    addTricker("FreshPart",[this](){
        sprite->FreshParts();
        return "";
    });
}
