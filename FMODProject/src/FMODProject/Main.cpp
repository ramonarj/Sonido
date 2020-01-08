#include <iostream>

#include <fmod.hpp>
#include <fmod_errors.h>

void ERRCHECK(FMOD_RESULT result)
{
	if (result != FMOD_OK) printf(FMOD_ErrorString(result));
}

int main()
{
	FMOD::System* system = nullptr;
	FMOD_RESULT result = FMOD_RESULT::FMOD_OK;

	result = FMOD::System_Create(&system);
	ERRCHECK(result);

	result = system->init(128, FMOD_INIT_NORMAL, nullptr);
	ERRCHECK(result);

	result = system->release();
	ERRCHECK(result);

	return 0;
}