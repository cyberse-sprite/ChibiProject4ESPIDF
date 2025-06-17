#include "image.h"
uint8_t newAlpha(uint8_t a1, uint8_t a2)
{
    return a1 + a2 - a1 * a2 / 255;
}

uint16_t newColor(uint8_t c1, uint8_t a1, uint8_t c2, uint8_t a2)
{
    uint8_t a = newAlpha(a1, a2);
    if (a == 0)
        return 0;
    int value = (c1 * a1 * (255 - a2) / 255 + c2 * a2) / a;
    return value;
}

RGBA::RGBA(uint16_t pix, uint8_t a)
{
    this->color = pix;
    this->alpha = a;
}

RGBA::RGBA(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
    this->color = (r << 11) + (g << 5) + b;
    this->alpha = a;
}

RGBA RGBA::operator+(const RGBA &pix)
{
    uint16_t r = newColor(getR(), getA(), pix.getR(), pix.getA());
    uint16_t g = newColor(getG(), getA(), pix.getG(), pix.getA());
    uint16_t b = newColor(getB(), getA(), pix.getB(), pix.getA());
    uint16_t a = newAlpha(getA(), pix.getA());
    return RGBA(r, g, b, a);
}

const uint8_t RGBA::getR() const
{
    uint8_t r = 0;
    r = (this->color & 0xF800) >> 11;
    return r;
}

const uint8_t RGBA::getG() const
{
    uint8_t g = 0;
    g = (this->color & 0x07e0) >> 5;
    return g;
}

const uint8_t RGBA::getB() const
{
    uint8_t b = 0;
    b = (this->color & 0x1F);
    return b;
}

const uint8_t RGBA::getA() const
{
    return this->alpha;
}

const uint16_t RGBA::getColor() const
{
    return this->color;
}
