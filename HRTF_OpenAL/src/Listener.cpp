#include <iostream>

#include "Listener.h"
#include "Utils.h"
#include "AL/al.h"

int Listener::count = 0;

Listener::Listener() :
	pos(nullptr),
	vel(nullptr),
	ori(nullptr),
	id(count)
{
	count++;
}

Listener::Listener(float* pos, float* vel, float* ori) :
	id(count)
{
	setPosition(pos);
	setVelocity(vel);
	setOrientation(ori);
	count++;
}

Listener::~Listener()
{
	count--;
}

void Listener::setPosition(float* newPos)
{
	pos = newPos;
	alListenerfv(AL_POSITION, pos);
	DisplayALError();
}

void Listener::setVelocity(float* newVel)
{
	vel = newVel;
	alListenerfv(AL_VELOCITY, pos);
	DisplayALError();
}
void Listener::setOrientation(float* newOri)
{
	ori = newOri;
	alListenerfv(AL_ORIENTATION, ori);
	DisplayALError();
}