#ifndef __SOURCE_H__
#define __SOURCE_H__

#include "alut.h"
#include "al.h"
#include "alc.h"
#include <string>

class Source
{
public:
	Source();
	Source(std::string name);
	~Source();

	//Links source to audio buffer
	void setBuffer(ALuint buffer);

	//Sets position of source
	void setPosition(ALfloat* newPos);

	//Sets position of source
	void setLooping(bool loop);

	//Get name of the source
	inline std::string getName() const { return name; }

	//Plays its sample
	void play();


private:
	
	ALfloat* pos;
	std::string name;
	ALuint id;
};



#endif // __SOURCE_H__
