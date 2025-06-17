#include "charactersprite.h"
#include "core/assets/imageassets.h"
#include "animationsprite.h"
#include "core/data/equip.h"
#include "core/assets/sheetassets.h"

CharacterSprite::CharacterSprite()
{
    addTricker("FreshPart",[this](){
        FreshParts();
        return "";
    });
}

CharacterSprite::CharacterSprite(CharacterObject *c,int x,int y) {
    obj=c;
    FreshParts();
    this->x=x;
    this->y=y;
    this->name=c->key;
    addTricker("FreshPart",[this](){
        FreshParts();
        return "";
    });
}

void CharacterSprite::FreshParts()
{
    clearChildren();
    parts.clear();
    for(const auto &equip:obj->equips){
        for(const auto &part:LoadEquip(equip.second).parts){
            AnimationSprite* sprite=new AnimationSprite(name+"_"+equip.first);
            if(equip.first=="eye"){
                sprite->LoadSheet(SHEET->get("eye_front"));
            }else{
                sprite->LoadSheet(SHEET->get("walk_front"));
            }
            auto image=IMG->get(part.image);
            sprite->SetTextures(image);
            sprite->anchor=7;
            sprite->z=part.z;
            sprite->speed=2;
            pushChild(sprite);
            parts.push_back(sprite);
        }
    }
    sortChildrenByZ();
}

void CharacterSprite::playPop()
{
    pop=new AnimationSprite(IMG->get("icon_sys_bubble"),
                              SHEET->getStep(3),
                              this->name+"_pop");
    pushChild(pop);
    pop->loop=1;
    pop->anchor=7;
    pop->y=-48;
}

void CharacterSprite::playEmotion(std::string name)
{
    emotion=new AnimationSprite(IMG->get(name),
                                  SHEET->getStep(3),
                                  this->name+"_"+name);
    emotion->anchor=7;
    emotion->y=-4;
    pop->pushChild(emotion);
}

void CharacterSprite::Selected()
{
    auto pop=new AnimationSprite(IMG->get("icon_sys_selectionsigndown"),
                                   SHEET->getStep(4),
                                   this->name+"_sign");
    pushChild(pop);
    pop->anchor=7;
    pop->y=-48;
}

void CharacterSprite::setOffset(int offset)
{
    for(auto item:parts){
        item->setOffset(offset);
    }
}

