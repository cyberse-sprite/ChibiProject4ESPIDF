#include "font.h"
#include <algorithm>
#include "inf/file.h"

Font::Font() {
    loadFont("fonts/allgb");
    loadFontAsc("fonts/asc");
}

PixChar Font::getPixChar(unsigned char c)
{
    return asc.at(c);
}

PixChar Font::getPixChar(std::string unicode)
{
    auto it=std::find(chars.begin(),chars.end(),unicode);
    if(it!=chars.end()){
        int dis=it-chars.begin();
        if(dis<pixs.size())
        return pixs.at(dis);
    }
    auto pix=PixChar();
    pix.content[0]=1;
    return pix;
}

void Font::loadFont(std::string path)
{
    File file;
    std::string txt=path+".txt";
    file.open(txt,"r");
    while(!file.end()){
        auto c=file.read(3);
        chars.push_back(c);
    }
    file.close();
    std::string data=path;
    file.open(data,"r");
    while(!file.end()){
        auto patten=file.read(18);
        PixChar pix;
        pix.loadString(patten);
        pixs.push_back(pix);
    }
    file.close();
}

void Font::loadFontAsc(std::string path)
{
    File file;
    file.open(path,"r");
    while(!file.end()){
        auto patten=file.read(18);
        PixChar pix;
        pix.loadString(patten);
        pix.width=(unsigned char)file.read(1)[0];
        asc.push_back(pix);
    }
    file.close();
}

std::string PixChar::getString()
{
    std::string res="";
    for(int i=0;i<18;i++){
        std::bitset<8> c;
        for(int j=0;j<8;j++){
            c[j]=content[i*8+j];
        }
        res.push_back(c.to_ulong());
    }
    std::string s=content.to_string();
    return res;
}

void PixChar::loadString(std::string str)
{
    for(int i=0;i<18;i++){
        std::bitset<8> c(str[i]);
        for(int j=0;j<8;j++){
            content[i*8+j]=c[j];
        }
    }
    std::string s=content.to_string();
}

