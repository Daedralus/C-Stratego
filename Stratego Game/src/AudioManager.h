#pragma once
#include "header.h"
#include <iostream>
#include <SDL.h>

#ifndef AUDIO_H
#define AUDIO_H


class AudioManager {
public:
    ~AudioManager();
    void load(const char* filename);
    void play();
private:
    SDL_AudioSpec wavSpec;
    Uint32 wavLength;
    Uint8* wavBuffer;
    SDL_AudioDeviceID deviceId;
};

#endif //AUDIO_H 

