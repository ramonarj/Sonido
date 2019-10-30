#ifndef __SYSTEM_H__
#define __SYSTEM_H__

#include <string>
#include <iostream>

#include "fmod.hpp"
#include "fmod_errors.h"

static void ERRCHECK(FMOD_RESULT result);

class System
{
private:
	FMOD::System* system_;
	FMOD_RESULT result_;

public:
	static System* Instance();

	void update();

private:
	System();
	~System();

	static System* instance_;
};

#endif // !__SYSTEM_H__



