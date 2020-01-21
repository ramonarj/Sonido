#ifndef __SOURCE_H__
#define __SOURCE_H__

class Source
{
private:
	const char* name;
	unsigned int id;
	float* pos;

public:
	//Constructora por defecto
	Source();
	//Constructora solo con el nombre
	Source(const char* name);
	//Constructora con parámetros
	Source(const char* name, unsigned int buffer, float* pos);
	// Destructora
	~Source();

	//SETTERS
	//Links source to audio buffer
	void setBuffer(unsigned int buffer);
	//Sets position of source
	void setPosition(float* newPos);
	//Sets position of source
	void setLooping(bool loop);
	//Sets source gain (0 <= gain <= 1)
	void setGain(float buffer);
	//Sets source pitch (0.5 <= pitch <= 2)
	void setPitch(float pitch);

	//GETTERS
	//Get name of the source
	inline const char* getName() const { return name; }
	//Gets source position
	inline float* getPosition() { return pos; }

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
};

#endif // __SOURCE_H__