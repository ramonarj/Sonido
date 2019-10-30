#ifndef __SOURCE_H__
#define __SOURCE_H__

#include "al.h" //audio library -> tipos y funciones básicas

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
	//Sets source gain (0 <= gain <= 1)
	void setGain(ALfloat buffer);
	//Sets source pitch (0.5 <= pitch <= 2)
	void setPitch(ALfloat pitch);


	//GETTERS
	//Get name of the source
	inline std::string getName() const { return name; }
	//Gets source position
	inline ALfloat* getPosition() { return pos; }


	//BÁSICOS
	//Plays its sample
	void play();
	//Pauses the sample
	void pause();
	//Stops the sample
	void stop();


	//BOOLEANOS
	//Indica si está sonando
	bool isPlaying();


private:
	ALfloat* pos;
	std::string name;
	ALuint id;
};
#endif // __SOURCE_H__
