
#ifndef BASIC_AUDIO_H
#define BASIC_AUDIO_H
#include <stdio.h>
#include <stdint.h>

struct WavFile
{
    uint16_t numChannels;
    uint32_t sampleRate;
    uint16_t bitsPerSanple;
    FILE *fp;
} typedef WavFile;

#ifdef __cplusplus
extern "C"
{
#endif
void test();
#ifdef __cplusplus
}
#endif

#endif