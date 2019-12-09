#ifndef __LISTENER_H__
#define __LISTENER_H__

#include "AL/al.h" //audio library -> tipos y funciones básicas

#include <string>


class Listener
{
public:
	//Constructora por defecto
	Listener();
	//Constructora guay
	Listener(ALfloat* pos, ALfloat* vel, ALfloat* ori);
	~Listener();


	//SETTERS

	//Sets listener's position 
	void setPosition(ALfloat* newPos);
	//Sets listener's velocity 
	void setVelocity(ALfloat* newVel);
	//Sets listener's orientation 
	void setOrientation(ALfloat* newOri);



	//GETTERS
	//Gets listener's position
	inline ALfloat* getPosition() { return pos; }
	//Gets listener's velocity
	inline ALfloat* getVelocity() { return vel; }
	//Gets listener's orientation
	inline ALfloat* getOrientation() { return ori; }


private:
	ALfloat* pos;
	ALfloat* vel;
	ALfloat* ori;
	ALuint id;
};
#endif // __LISTENER_H__
