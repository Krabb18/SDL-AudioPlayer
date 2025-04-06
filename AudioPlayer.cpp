#include "AudioPlayer.h"

void AudioPlayer::InitAudioData(string soundPath)
{
    if (SDL_LoadWAV(soundPath.c_str(), &wavSpec, &wavBuffer, &wavLength) == nullptr) {
        std::cerr << "Something went wrong: " << SDL_GetError() << std::endl;
    }

    wavSpec.callback = nullptr;
    deviceID = SDL_OpenAudioDevice(nullptr, 0, &wavSpec, nullptr, 0);
    if(deviceID == 0)
    {
        std::cerr << "Something went wrong: " << SDL_GetError() << std::endl;
        SDL_FreeWAV(wavBuffer);
    }

    bufferCopy = (Uint8*)SDL_malloc(wavLength);
}

void AudioPlayer::LoopSound()
{
if (SDL_GetQueuedAudioSize(deviceID) == 0) {
        SDL_QueueAudio(deviceID, bufferCopy, wavLength);
    }
}

void AudioPlayer::PlayAudioData()
{
    SDL_QueueAudio(deviceID, bufferCopy, wavLength);
    SDL_PauseAudioDevice(deviceID, 0); // 0 = abspielen
}

void AudioPlayer::PauseAudioData()
{
    SDL_QueueAudio(deviceID, bufferCopy, wavLength);
    SDL_PauseAudioDevice(deviceID, 1); // 1 = pause
}

void AudioPlayer::Volume(float vol)
{
    SDL_MixAudioFormat(bufferCopy, wavBuffer, wavSpec.format, wavLength, vol * 128);
}

void AudioPlayer::DeleteAudioData()
{
    SDL_free(bufferCopy);
    SDL_CloseAudioDevice(deviceID);
    SDL_FreeWAV(wavBuffer);
    SDL_Quit();
}