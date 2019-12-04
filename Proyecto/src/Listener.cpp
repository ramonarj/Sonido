#include "Listener.h"

#include <iostream>

Listener::Listener() :  pos(nullptr), vel(nullptr), ori(nullptr)
{

}

Listener::Listener(ALfloat* pos, ALfloat* vel, ALfloat* ori): pos(pos), vel(vel), ori(ori)
{
	alListenerfv(AL_POSITION, pos);
	alListenerfv(AL_VELOCITY, vel);
	alListenerfv(AL_ORIENTATION, ori);
}



Listener::~Listener()
{
}

void Listener::setPosition(ALfloat* newPos)
{
	pos = newPos;
	alListenerfv(AL_POSITION, pos);
}

void Listener::setVelocity(ALfloat* newVel)
{
	vel = newVel;
	alListenerfv(AL_VELOCITY, pos);
}
void Listener::setOrientation(ALfloat* newOri)
{
	ori = newOri;
	alListenerfv(AL_ORIENTATION, ori);
}
