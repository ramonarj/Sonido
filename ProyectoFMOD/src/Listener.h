#ifndef __LISTENER_H__
#define __LISTENER_H__

#include <string>

#include "System.h"

#define FMOD_SYSTEM System::getFmodSystem()

class Listener
{
private:
	FMOD_VECTOR position_;
	FMOD_VECTOR velocity_;
	FMOD_VECTOR forward_;
	FMOD_VECTOR up_;

public:
	Listener(FMOD_VECTOR pos, FMOD_VECTOR vel, FMOD_VECTOR forward, FMOD_VECTOR up);
	~Listener();

private:

};

#endif // !__LISTENER_H__