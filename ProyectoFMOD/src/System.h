#ifndef __SYSTEM_H__
#define __SYSTEM_H__

#include <iostream>

#include "fmod.hpp"
#include "fmod_errors.h"

class System
{
private:
	static FMOD::System* system_;

public:
	static void init();
	static void update();
	static void release();

	static FMOD::System* getFmodSystem() { return system_; }
};

static void ERRCHECK(FMOD_RESULT result)
{
	if (result != FMOD_OK)
	{
		std::cout << FMOD_ErrorString(result) << std::endl;
		exit(-1);
	}
}

#endif // !__SYSTEM_H__