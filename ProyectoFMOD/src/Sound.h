#ifndef __SOUND_H__
#define __SOUND_H__

#include <string>
#include <iostream>

#include "fmod.hpp"
#include "fmod_errors.h"

#define FMOD_SYSTEM System::Instance()->getSystem()

class Sound
{
private:
	FMOD::Channel* channel_;
	FMOD_RESULT result_;

public:
	Sound(std::string filename);
	~Sound();

	void play();
	void pause();
	void stop();

	inline void setVolume(float volume) {  }

};

#endif // !__SOUND_H__