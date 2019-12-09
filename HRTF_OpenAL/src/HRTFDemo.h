#ifndef __HRTFDEMO_H__
#define __HRTFDEMO_H__

#include "al.h" //audio library -> tipos y funciones básicas
#include <string>

class Listener;
class Source;
struct ALCcontext;
struct ALCdevice;

class HRTFDemo
{
public:
	//Constructora por defecto
	HRTFDemo();
	~HRTFDemo();

	//Inicializa recursos
	bool init(std::string sourceFilename, int sceneWidth, int sceneHeight);

	//Actualiza la lógica
	bool update();

	//Libera recursos
	void free();

private:
	//Inicialización de OpenAL
	ALCcontext * Context;
	ALCdevice *Device;

	//Objetos de la demo
	ALuint sourceBuffer;
	Source* source;
	Listener * listener;

	float incr;
	int sceneWidth;
	int sceneHeight;

	//Métodos auxiliares
	void renderScenario(Listener* listener, Source* source);
	bool processInput();
	void loadWAV(std::string filename);
};
#endif 
