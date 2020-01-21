#include <iostream>

#include "AL/al.h"
#include "Utils.h"

void DisplayALError()
{
	ALenum error = alGetError();
	if (error != AL_NO_ERROR)
	{
		printf("AL Error: %s", alGetString(error));
		exit(-1);
	}
}