#include "Source.h"
#include <iostream>

Source::Source() : name("unnamedSrc")
{

}

Source::Source(std::string name): pos(pos), name(name)
{
	alGenSources(1, &id);
	if (alGetError() != AL_NO_ERROR)
		exit(-1);

	//Default position for the source
	ALfloat defaultPos []= { 0.0,0.0,0.0 };
	setPosition(defaultPos);
}


Source::~Source()
{
}

void Source::setBuffer(ALuint buffer)
{
	alSourcei(id, AL_BUFFER, buffer);
}

void Source::setPosition(ALfloat* newPos)
{
	alSourcefv(id, AL_POSITION, newPos);
}

void Source::setLooping(bool loop)
{
	if(loop)
		alSourcei(id, AL_LOOPING, AL_TRUE);
	else
		alSourcei(id, AL_LOOPING, AL_FALSE);

}

void Source::play()
{
	alSourcePlay(id);
}
