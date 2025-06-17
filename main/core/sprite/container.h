#ifndef ABSTRACTSPRITE_H
#define ABSTRACTSPRITE_H

#include "core/paintevent.h"
#include "core/sprite/trigger.h"
#include <list>
#include <string>
class Container:public Trigger
{
    std::list<Container*> children;
public:
    Container(std::string n="",Container*parent=nullptr);
    std::string name;
    int x;
    int y;
    int z;
    int rotate;
    int anchor=0;
    bool visible;
    Container* parent;
    virtual void paintEvent(PaintEvent *event);
    void Hide();
    void Show();
    void pushChild(Container* child,std::string parent="");
    void removeChild(std::string name,bool recursive=true);
    void clearChildren();
    Container* getChild(std::string name,bool recursive=true);
    void sortChildrenByZ();
};

#endif // ABSTRACTSPRITE_H
