#include "animationsprite.h"
#include "listsprite.h"
#include "core/assets/imageassets.h"
#include "core/assets/sheetassets.h"


ListSprite::ListSprite(std::string n, ListStyle s, Container * parent):Container(n,parent)
{
    current=0;
    style=s;
    addTricker("next",[this](){
        Next();
        return "";
    });
    addTricker("prev",[this](){
        Prev();
        return "";
    });
    addTricker("getTag",[this](){
        return getTag();
    });
    addTricker("getFile",[this](){
        return getFile();
    });
    rect.name=name+"_listrect";
    pushChild(&rect);
}

void ListSprite::Next()
{
    current+=1;
    if(current>=items.size()){
        current=0;
    }
    countCurrent();
}

void ListSprite::Prev()
{
    current-=1;
    if(current<0){
        current=items.size()-1;
    }
    countCurrent();
}

std::string ListSprite::getTag()
{
    return items[current]->tag;
}

std::string ListSprite::getFile()
{
    return items[current]->file;
}

void ListSprite::AppendItem(std::string icon, std::string text,std::string tag,std::string file)
{
    auto item=new ListItemSprite(icon,text,tag,file,&itemStyle);
    items.push_back(item);
    pushChild(item);
    countCurrent();
}

void ListSprite::countCurrent()
{
    int start=current-(current%style.page_size);
    int end=start+style.page_size;
    for(auto item:items){
        item->Hide();
    }
    for(int j=0;j<style.y_num;j++){
        for(int i=0;i<style.x_num;i++){
            if(start>=items.size()||start>=end){
                break;
            }
            int ix=style.x_offset*i;
            int iy=style.y_offset*j;
            items[start]->Show();
            items[start]->x=ix;
            items[start]->y=iy;
            if(start==current){
                rect.setRect(ix,iy,style.x_offset,style.y_offset);
            }
            start+=1;
        }
    }
}

void ListSprite::setCurrent(std::string tag)
{
    for(int i=0;i<items.size();i++){
        if(items.at(i)->tag==tag)
            current=i;
    }
    countCurrent();
}

ListItemSprite::ListItemSprite(std::string icon, std::string text, std::string tag,std::string file,ListItemStyle* style)
{
    this->name=tag+"_listitem";
    this->style=style;
    this->icon=new AnimationSprite(IMG->get(icon),SHEET->get(""),name+"_"+icon);
    this->icon->x=style->icon_x;
    this->icon->y=style->icon_y;
    this->icon->visible=style->isIcon;
    this->text=new TextSprite(text);
    this->text->x=style->text_x;
    this->text->y=style->text_y;
    this->text->visible=style->isText;
    this->tag=tag;
    this->file=file;
    pushChild(this->icon);
    pushChild(this->text);
}
