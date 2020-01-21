#include <iostream>

#include "Source.h"
#include "Utils.h"
#include "AL/al.h"

Source::Source() :
	name("unnamedSrc"),
	id(0),
	pos(nullptr)
{
}

Source::Source(const char* name) :
	name(name),
	pos(nullptr)
{
	alGenSources(1, &id);
	DisplayALError();

	ALfloat defaultPos[] = { 0.0f, 0.0f, 0.0f };
	setPosition(defaultPos);
}

Source::Source(const char* name, unsigned int buffer, float* pos) :
	name(name)
{
	alGenSources(1, &id);
	DisplayALError();

	setBuffer(buffer);
	setPosition(pos);
}


Source::~Source()
{
	alDeleteSources(1, &id);
	DisplayALError();
}

void Source::setBuffer(unsigned int buffer)
{
	alSourcei(id, AL_BUFFER, buffer);
	DisplayALError();
}

void Source::setPosition(float* newPos)
{
	pos = newPos;
	alSourcefv(id, AL_POSITION, pos);
	DisplayALError();
}

void Source::setLooping(bool loop)
{
	if (loop)
	{
		alSourcei(id, AL_LOOPING, AL_TRUE);
		DisplayALError();
	}
	else
	{
		alSourcei(id, AL_LOOPING, AL_FALSE);
		DisplayALError();
	}
}

void Source::setGain(float gain)
{
	alSourcef(id, AL_GAIN, gain);
	DisplayALError();
}

void Source::setPitch(float pitch)
{
	alSourcef(id, AL_PITCH, pitch);
	DisplayALError();
}

void Source::play()
{
	alSourcePlay(id);
	DisplayALError();
}

void Source::pause()
{
	alSourcePause(id);
	DisplayALError();
}

void Source::stop()
{
	alSourceStop(id);
	DisplayALError();
}

bool Source::isPlaying()
{
	ALenum state;
	alGetSourcei(id, AL_SOURCE_STATE, &state);
	DisplayALError();

	return (state == AL_PLAYING);
}
