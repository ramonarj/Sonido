#include "System.h"

static void ERRCHECK(FMOD_RESULT result)
{
	if (result != FMOD_OK)
	{
		std::cout << FMOD_ErrorString(result) << std::endl;
		exit(-1);
	}
}

System::System()
{
	FMOD::System* system = nullptr;
	FMOD_RESULT result;
	result = FMOD::System_Create(&system);
	ERRCHECK(result);

	result = system->init(128, FMOD_INIT_NORMAL, 0);
	ERRCHECK(result);
}

System::~System()
{
	result_ = system->release();
	ERRCHECK(result);
}

System* System::Instance()
{
	if (!instance_) instance_ = new System();
	return instance_;
}

void System::update()
{
}
