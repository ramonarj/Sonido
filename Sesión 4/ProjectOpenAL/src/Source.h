#ifndef __SOURCE_H__
#define __SOURCE_H__

#include "alut.h"
#include "al.h"
#include "alc.h"
#include <string>

class Source
{
public:
	//Constructora por defecto
	Source();
	//Constructora solo con el nombre
	Source(std::string name);
	//Constructora guay
	Source(std::string name, ALuint buffer, ALfloat* pos);
	~Source();


	//SETTERS
	//Links source to audio buffer
	void setBuffer(ALuint buffer);

	//Sets position of source
	void setPosition(ALfloat* newPos);

	//Sets position of source
	void setLooping(bool loop);


	//GETTERS
	//Get name of the source
	inline std::string getName() const { return name; }

	//Gets source position
	inline ALfloat* getPosition() { return pos; }

	//Plays its sample
	void play();


private:
	ALfloat* pos;
	std::string name;
	ALuint id;
};
#endif // __SOURCE_H__
