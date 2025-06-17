#include "core/assets/imageassets.h"
#include "inf/file.h"
#include <core/utils/textutils.h>

Image *ImageAssets::get(std::string name){
    typename std::map<std::string,Image*>::iterator i=items.find(name);
    if(i!=items.end()){
        return i->second;
    }
    return load(name);
}

void ImageAssets::add(std::string name, Image *image)
{
    items.insert(std::make_pair(name,image));
}

Image* ImageAssets::load(std::string name)
{
    std::string target="image/"+name;
    File file;
    if(!file.open(target,"r"))return nullptr;
    Image* image=new Image;
    Image* cursor=image;
    add(name,cursor);
    while(!file.end()){
        cursor->x=file.readuint16_t();
        cursor->y=file.readuint16_t();
        cursor->w=file.readuint16_t();
        cursor->h=file.readuint16_t();
        cursor->dw=file.readuint16_t();
        cursor->dh=file.readuint16_t();
        cursor->type=file.readuint16_t();
        int size=cursor->dw*cursor->dh;
        cursor->data=new uint16_t[size];
        for(int i=0;i<size;i++){
            cursor->data[i]=file.readuint16_t_swap();
        }
        cursor->alpha=new uint8_t[size];
        for(int i=0;i<size;i++){
            cursor->alpha[i]=file.readuint8_t();
        }
        if(!file.end()){
            cursor->next=new Image;
            cursor->next->prev=cursor;
            cursor=cursor->next;
        }
    }
    cursor->next=nullptr;
    file.close();
    return image;
}

void ImageAssets::clear()
{
    for(auto item:items){
        releaseImage(item.second);
    }
    items.clear();
}

void ImageAssets::releaseImage(Image *image)
{
    while(image->next!=nullptr){
        image=image->next;
    }
    while(image->prev!=nullptr){
        delete image->data;
        delete image->alpha;
        image=image->prev;
        delete image->next;
    }
    delete image->data;
    delete image->alpha;
    delete image;
}
