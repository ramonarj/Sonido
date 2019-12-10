#include "Source.h"

#include <iostream>

#include "Utils.h"

#include "AL/al.h" //audio library -> tipos y funciones básicas

Source::Source() : name("unnamedSrc"), pos(nullptr)
{

}

Source::Source(std::string name): name(name), pos(nullptr)
{
	int error;
	alGenSources(1, &id);
	if ((error = alGetError()) != AL_NO_ERROR)
		DisplayALError("genSources 1 : ", error);
		

	//Default position for the source
	ALfloat defaultPos []= { 0.0,0.0,0.0 };
	setPosition(defaultPos);
}

Source::Source(std::string name, ALuint buffer, ALfloat* pos) : name(name)
{
	alGenSources(1, &id);
	if (alGetError() != AL_NO_ERROR)
		exit(-1);

	setBuffer(buffer);
	setPosition(pos);
}


Source::~Source()
{
	alDeleteSources(1, &id);
}

void Source::setBuffer(ALuint buffer)
{
	alSourcei(id, AL_BUFFER, buffer);
}

void Source::setPosition(ALfloat* newPos)
{
	pos = newPos;
	alSourcefv(id, AL_POSITION, pos);
}

void Source::setLooping(bool loop)
{
	if(loop)
		alSourcei(id, AL_LOOPING, AL_TRUE);
	else
		alSourcei(id, AL_LOOPING, AL_FALSE);

}

void Source::setGain(ALfloat gain)
{
	alSourcef(id, AL_GAIN, gain);
}

void Source::setPitch(ALfloat pitch)
{
	alSourcef(id, AL_PITCH, pitch);
}

void Source::play()
{
	alSourcePlay(id);
}

void Source::pause()
{
	alSourcePause(id);
}

void Source::stop()
{
	alSourceStop(id);
}

bool Source::isPlaying()
{
	ALenum state;
	alGetSourcei(id, AL_SOURCE_STATE, &state);

	return (state == AL_PLAYING);
}
