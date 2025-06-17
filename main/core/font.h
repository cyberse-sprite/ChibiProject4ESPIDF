#ifndef FONT_H
#define FONT_H

#include "core/data/image.h"
#include <bitset>
#include <vector>

struct PixChar{
    std::bitset<144> content;
    unsigned char width=12;
    std::string getString();
    void loadString(std::string);
};

class Font
{
    std::vector<PixChar> asc;
    std::vector<std::string> chars;
    std::vector<PixChar> pixs;
public:
    RGBA defaultColor;
    Font();
    PixChar getPixChar(unsigned char c);
    PixChar getPixChar(std::string unicode);
    void loadFont(std::string path);
    void loadFontAsc(std::string path);
};

#endif // FONT_H
