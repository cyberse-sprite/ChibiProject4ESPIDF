#include "container.h"

Container::Container(std::string n,Container*parent) {
    this->name=n;
    this->z=0;
    this->x=0;
    this->y=0;
    this->rotate=0;
    this->parent=parent;
    visible=true;
    addTricker("hide",[this](){
        Hide();
        return "";
    });
    addTricker("show",[this](){
        Show();
        return "";
    });
}

void Container::paintEvent(PaintEvent *event)
{
    if(!visible)return;
    event->x+=x;
    event->y+=y;
    for(auto i=children.begin();i!=children.end();i++){
        (*i)->paintEvent(event);
    }
    event->x-=x;
    event->y-=y;
}

void Container::Hide()
{
    visible=false;
}

void Container::Show()
{
    visible=true;
}

void Container::pushChild(Container *child,std::string parent)
{
    if(parent==""||parent==name){
        child->parent=this;
        children.push_back(child);
    }else{
        Container* target=getChild(parent);
        if(target==nullptr)return;
        target->pushChild(child,parent);
    }
}

void Container::removeChild(std::string name,bool recursive)
{
    for(auto child:children){
        if(child->name==name){
            // delete child;
            children.remove(child);
            return;
        }
    }
    if(recursive){
        for(auto child:children){
            child->removeChild(name,recursive);
        }
    }
}

void Container::clearChildren()
{
    for(auto item:children){
        // delete item;
    }
    children.clear();
}

Container *Container::getChild(std::string name,bool recursive)
{
    for(auto i=children.begin();i!=children.end();i++){
        if((*i)->name==name){
            return (*i);
        }
    }
    if(recursive){
        for(auto i=children.begin();i!=children.end();i++){
            Container* target=(*i)->getChild(name,recursive);
            if(target!=nullptr)return target;
        }
    }
    return nullptr;
}

bool z_index(Container* t1,Container* t2){
    return t1->z<t2->z;
}

void Container::sortChildrenByZ()
{
    children.sort(z_index);
}
