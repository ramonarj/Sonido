#include "Sound.h"
#include "System.h"

Sound::Sound(std::string filename)
{
	FMOD::Sound* sound;
	result_ = FMOD_SYSTEM->createSound(filename.c_str(), FMOD_DEFAULT, 0, &sound);
	ERRCHECK(result_);

	result_ = FMOD_SYSTEM->playSound(sound, 0, true, &channel_);
	ERRCHECK(result_);
}

Sound::~Sound()
{
}

void Sound::play()
{
}

void Sound::pause()
{
}

void Sound::stop()
{
}
