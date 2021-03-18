#include "header.h"
#include <iostream>
#include <SDL.h>
#include "AudioManager.h"

AudioManager::~AudioManager() {
    SDL_CloseAudioDevice(deviceId);
    SDL_FreeWAV(wavBuffer);
}

void AudioManager::load(const char* filename) {
    SDL_LoadWAV(filename, &wavSpec, &wavBuffer, &wavLength);
    deviceId = SDL_OpenAudioDevice(NULL, 0, &wavSpec, NULL, 0);
}

void AudioManager::play() {
    SDL_QueueAudio(deviceId, wavBuffer, wavLength);
    SDL_PauseAudioDevice(deviceId, 0);
}