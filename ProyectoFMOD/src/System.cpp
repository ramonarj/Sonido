#include "System.h"

FMOD::System* System::system_ = nullptr;

void System::init()
{
	FMOD_RESULT result = FMOD::System_Create(&system_);
	ERRCHECK(result);

	result = system_->init(128, FMOD_INIT_NORMAL, 0);
	ERRCHECK(result);
}

void System::release()
{
	FMOD_RESULT result = system_->release();
	ERRCHECK(result);
}

void System::update()
{
	system_->update();
}
