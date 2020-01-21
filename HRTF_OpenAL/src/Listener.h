#ifndef __LISTENER_H__
#define __LISTENER_H__

class Listener
{
private:
	float* pos;
	float* vel;
	float* ori;
	int id;

	static int count;

public:
	//Constructora por defecto
	Listener();
	//Constructora con parámetros
	Listener(float* pos, float* vel, float* ori);
	//Destructora
	~Listener();

	//SETTERS
	//Sets listener's position 
	void setPosition(float* newPos);
	//Sets listener's velocity 
	void setVelocity(float* newVel);
	//Sets listener's orientation 
	void setOrientation(float* newOri);

	//GETTERS
	//Gets listener's position
	inline float* getPosition() { return pos; }
	//Gets listener's velocity
	inline float* getVelocity() { return vel; }
	//Gets listener's orientation
	inline float* getOrientation() { return ori; }
};

#endif // __LISTENER_H__