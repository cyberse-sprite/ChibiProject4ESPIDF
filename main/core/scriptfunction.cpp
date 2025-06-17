#include "scriptfunction.h"
#include "actuator.h"
#include "core/assets/imageassets.h"
#include "core/action/floataction.h"
#include "core/action/moveaction.h"
#include "core/action/popaction.h"
#include "core/action/sheetaction.h"
#include "core/action/walkaction.h"
#include "core/archive.h"
#include "core/assets/sheetassets.h"
#include "inf/audio.h"
#include "core/sprite/animationsprite.h"
#include "core/sprite/charactersprite.h"
#include "inf/log.h"
#include "sprite/imagesprite.h"
#include "sprite/listsprite.h"
#include "stage.h"

ScriptFunctionRes ScriptFunction::call(Actuator *act, Line line)
{
    std::string name = line.GetName();
    ScriptFunctionRes res{true, true};
    LOG->info(name);
    if (name == "addImageSprite")
    {
        ImageSprite *sprite = new ImageSprite(IMG->get(line.GetStr("image")),
                                              line.GetStr("name"));
        sprite->x = line.GetInt("x");
        sprite->y = line.GetInt("y");
        sprite->anchor = line.GetInt("anchor");
        STAGE->pushChild(sprite, line.GetStr("target"));
    }
    else if (name == "addAnimationSprite")
    {
        Image *image = IMG->get(line.GetStr("image"));
        Sheet *sheet=SHEET->get(line.GetStr("sheet"),line.GetInt("num"));
        AnimationSprite *sprite = new AnimationSprite(image,sheet, line.GetStr("name"));
        int speed = line.GetInt("speed");
        if (speed == 0)
            speed = 2;
        sprite->speed = speed;
        STAGE->pushChild(sprite, line.GetStr("target"));
        STAGE->addAction(new SheetAction(sprite));
    }
    else if (name == "addListSprite")
    {
        ListStyle style{line.GetInt("x_offset"), line.GetInt("y_offset"), line.GetInt("x_num"), line.GetInt("y_num")};
        ListItemStyle itemStyle;
        itemStyle.isIcon = line.GetInt("icon");
        itemStyle.isText = line.GetInt("text");
        itemStyle.text_x = line.GetInt("text_x");
        itemStyle.text_y = line.GetInt("text_y");
        ListSprite *sprite = new ListSprite(line.GetStr("name"),
                                            style);
        sprite->x = line.GetInt("x");
        sprite->y = line.GetInt("y");
        sprite->itemStyle = itemStyle;
        STAGE->pushChild(sprite, line.GetStr("target"));
    }
    else if (name == "addListItem")
    {
        Container *sprite = STAGE->getChild(line.GetStr("target"));
        if (sprite == nullptr)
            return res;
        ListSprite *list = dynamic_cast<ListSprite *>(sprite);
        std::string file = line.GetStr("file");
        if (file == "")
            file = act->scripts.top()->name;
        list->AppendItem(line.GetStr("icon"),
                         line.GetStr("text"),
                         line.GetStr("tag"),
                         file);
    }
    else if (name == "addCharacterSprite")
    {
        CharacterSprite *sprite = new CharacterSprite(&(ARC->characters.at(line.GetStr("character"))));
        sprite->x = line.GetInt("x");
        sprite->y = line.GetInt("y");
        sprite->name = line.GetStr("name");
        STAGE->pushChild(sprite, line.GetStr("target"));
    }
    else if (name == "event")
    {
        act->events[line.GetStr("name")] = Target{line.GetStr("label"), line.GetStr("file")};
    }
    else if (name == "r")
    {
        std::string label = line.GetStr("label");
        act->callReturn(line.GetInt("depth"));
        if (label != "")
        {
            act->jumpScript(label);
        }
        res.next = false;
    }
    else if (name == "w")
    {
        res.next = false;
        res.res = false;
    }
    else if (name == "print")
    {
        LOG->info(line.GetStr("text"));
    }
    else if (name == "action")
    {
        Container *target = STAGE->getChild(line.GetStr("target"));
        if (target == nullptr)
        {
            return res;
        };
        std::string res = target->triggered(line.GetStr("func"));
        if (res != "")
        {
            ARC->varis[line.GetStr("result")] = res;
        }
    }
    else if (name == "jump")
    {
        if (act->scripts.size() > 0)
            act->scripts.top()->next();
        act->jumpScript(line.GetStr("label"), line.GetStr("file"), line.GetInt("depth"));
        res.next = false;
    }
    else if (name == "call")
    {
        if (act->scripts.size() > 0)
            act->scripts.top()->next();
        // LOG->info(line.GetStr("file"));
        act->callScript(line.GetStr("label"), line.GetStr("file"));
        res.next = false;
    }
    else if (name == "clearStage")
    {
        STAGE->clearChildren();
        IMG->clear();
    }
    else if (name == "checkCharacter")
    {
        for (auto c : ARC->characters)
        {
            for (const auto &scope : c.second.scopes)
            {
                if (scope == act->scripts.top()->name)
                {
                    CharacterSprite *s = new CharacterSprite(&ARC->characters.at(c.first));
                    auto target = new CharacterShadowSprite(s);
                    target->name = s->name;
                    if (act->scripts.top()->name == "scene/river")
                    {
                        target->y = 88;
                    }
                    STAGE->addAction(new WalkAction(target));
                    target->shadow->playing = false;
                    if (c.second.GetInt("float"))
                    {
                        target->sprite->y -= 5;
                        STAGE->addAction(new FloatAction(target));
                    }
                    STAGE->pushChild(target, line.GetStr("target"));
                    ARC->varis["character"] = Variable(s->name);
                    return res;
                }
            }
        }
        ARC->varis["character"] = Variable("");
    }
    else if (name == "addCharacter")
    {
        std::string key = line.GetStr("key");
        CharacterObject obj(key);
        for (const auto &item : line.varis)
        {
            obj.varis[item.first] = item.second;
        }
        ARC->characters.insert(std::make_pair(key, obj));
    }
    else if (name == "addScope")
    {
        auto c = &ARC->characters.at(line.GetStr("target"));
        c->addScope(line.GetStr("scope"));
    }
    else if (name == "addEquip")
    {
        ARC->characters.at(line.GetStr("target")).addEquip(line.GetStr("equip"), line.GetStr("key"));
    }
    else if (name == "getEquip")
    {
        std::string res = ARC->characters.at(line.GetStr("target")).getEquip(line.GetStr("key"));
        ARC->varis[line.GetStr("res")] = Variable("\"" + res + "\"");
    }
    else if (name == "setVari")
    {
        auto v = Variable(line.GetRaw("value"));
        std::string prefix = line.GetStr("prefix");
        if (v.isType(VariableType::TAG))
        {
            if (prefix != "")
            {
                ARC->varis[line.GetStr("key")] = Variable("\"" + prefix + v.ToStr() + "\"");
            }
            else
            {
                ARC->varis[line.GetStr("key")] = v;
            }
        }
        else
        {
            v.content = prefix + v.content;
            ARC->varis[line.GetStr("key")] = v;
        }
    }
    else if (name == "characterEmotion")
    {
        auto sprite = STAGE->getChild(line.GetStr("target"));
        if (sprite != nullptr)
        {
            CharacterShadowSprite *character = dynamic_cast<CharacterShadowSprite *>(sprite);
            STAGE->addAction(new PopAction(character->sprite, line.GetStr("emotion")));
        }
    }
    else if (name == "characterSelected")
    {
        auto sprite = STAGE->getChild(line.GetStr("target"));
        if (sprite != nullptr)
        {
            CharacterSprite *character = dynamic_cast<CharacterSprite *>(sprite);
            character->Selected();
        }
    }
    else if (name == "wait")
    {
        // TODO 第一次执行wait可能会吞指令
        act->cd += line.GetInt("time");
    }
    else if (name == "spriteAction")
    {
        auto sprite = STAGE->getChild(line.GetStr("target"));
        if (sprite != nullptr)
        {
            if (line.GetStr("action") == "moveto")
            {
                MoveAction *action = new MoveAction(sprite, line.GetInt("x"), line.GetInt("y"), line.GetInt("time"));
                STAGE->addAction(action);
                act->cd += line.GetInt("time");
            }
        }
    }
    else if (name == "removeSprite")
    {
        STAGE->removeChild(line.GetStr("target"));
    }
    else if (name == "getCharacterVari")
    {
        auto character = ARC->characters.at(line.GetStr("target"));
        auto vari = character.varis[line.GetStr("key")];
        ARC->varis[line.GetStr("res")] = vari;
    }
    else if (name == "setCharacterVari")
    {
        auto character = &(ARC->characters.at(line.GetStr("target")));
        character->varis[line.GetStr("key")] = Variable(line.GetRaw("value"));
    }
    else if (name == "setListCurrent")
    {
        Container *sprite = STAGE->getChild(line.GetStr("target"));
        ListSprite *list = dynamic_cast<ListSprite *>(sprite);
        list->setCurrent(line.GetStr("tag"));
    }
    else if (name == "canTrigger")
    {
        act->canTrigger = true;
    }
    else if (name == "banTrigger")
    {
        act->canTrigger = false;
    }
    else if (name == "playBGM")
    {
        AUD->playBGM(line.GetStr("bgm"));
    }
    else if (name == "playSE")
    {
        AUD->playSE(line.GetStr("se"));
    }
    return res;
}
