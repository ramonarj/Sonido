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
	result_ = FMOD::System_Create(&system_);
	ERRCHECK(result_);

	result_ = system_->init(128, FMOD_INIT_NORMAL, 0);
	ERRCHECK(result_);
}

System::~System()
{
	result_ = system_->release();
	ERRCHECK(result_);
}

System* System::Instance()
{
	if (!instance_) instance_ = new System();
	return instance_;
}

void System::update()
{
	system_->update();
}
