#ifndef LISTSPRITE_H
#define LISTSPRITE_H

#include "container.h"
#include "core/sprite/rectsprite.h"
#include "core/sprite/textsprite.h"
#include <string>

struct ListItemStyle{
    int icon_x=0;
    int icon_y=0;
    int text_x=6;
    int text_y=6;
    bool isIcon=1;
    bool isText=0;
};

class ListItemSprite:public Container{
    ListItemStyle* style;
    Container* icon;
    TextSprite* text;
public:
    std::string tag;
    std::string file;
    ListItemSprite(std::string icon,std::string text,std::string tag,std::string file,ListItemStyle* style);
};

struct ListStyle{
    int x_offset=32;
    int y_offset=0;
    int x_num=4;
    int y_num=1;
    int page_size=x_num*y_num;
};

class ListSprite : public Container
{
public:
    RectSprite rect;
    ListSprite(std::string n="",ListStyle style=ListStyle(),Container* parent=nullptr);
    std::vector<ListItemSprite*> items;
    int current=0;
    ListStyle style;
    ListItemStyle itemStyle;
    void Next();
    void Prev();
    std::string getTag();
    std::string getFile();
    void AppendItem(std::string icon,std::string text,std::string tag,std::string file);
    void countCurrent();
    void setCurrent(std::string tag);
};

#endif // LISTSPRITE_H
