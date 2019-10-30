#ifndef __SOUND_H__
#define __SOUND_H__

#include <string>

#include "System.h"

#define FMOD_SYSTEM System::getFmodSystem()

class Sound
{
private:
	FMOD::Channel* channel_;
	FMOD::Sound* sound_;
	FMOD_RESULT result_;

	float volume_;
	float pitch_;
	float pan_;

public:
	Sound(std::string filename);
	~Sound();

	void play();
	void pause();
	void stop();

	void setVolume(float volume);
	void setPitch(float pitch);
	void setPan(float pan);

private:
	void reset();

};

#endif // !__SOUND_H__