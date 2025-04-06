#ifndef AUDIO_PLAYER_H
#define AUDIO_PLAYER_H

#include <SDL2/SDL.h>
#include <iostream>
#include <string>

using namespace std;

class AudioPlayer
{
private:
	SDL_AudioSpec wavSpec;
	Uint8* wavBuffer;
	Uint32 wavLength;
	SDL_AudioDeviceID deviceID;

	Uint8* bufferCopy;

public:
	void InitAudioData(string soundPath);
	void LoopSound();
	void PlayAudioData();
	void PauseAudioData();
	void DeleteAudioData();

	void Volume(float vol);
};

#endif // !AUDIO_PLAYER_H

