#ifndef IMAGE_H
#define IMAGE_H

#include <cstdint>

uint8_t newAlpha(uint8_t a1, uint8_t a2);

uint16_t newColor(uint8_t c1, uint8_t a1, uint8_t c2, uint8_t a2);

class RGBA
{
    uint16_t color=0;
    uint8_t alpha=255;
public:
    RGBA(uint16_t pix, uint8_t = 255);
    RGBA(uint8_t r = 0, uint8_t g = 0, uint8_t b = 0, uint8_t a = 255);
    RGBA operator+(const RGBA &pix);
    const uint8_t getR() const;
    const uint8_t getG() const;
    const uint8_t getB() const;
    const uint8_t getA() const;
    const uint16_t getColor() const;
};

struct Image
{
    uint16_t x=0;
    uint16_t y=0;
    uint16_t w=0;
    uint16_t h=0;
    uint16_t dw=0;
    uint16_t dh=0;
    uint16_t type=0;
    uint16_t *data=nullptr;
    uint8_t *alpha=nullptr;
    Image* next=nullptr;
    Image* prev=nullptr;
};

#endif // IMAGE_H
