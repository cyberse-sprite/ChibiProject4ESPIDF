#ifndef AUDIO_H
#define AUDIO_H

#include <string>
class Audio
{
public:
    Audio();
    void playBGM(std::string name);
    void playSE(std::string name);
};

extern Audio* AUD;

#endif // AUDIO_H
