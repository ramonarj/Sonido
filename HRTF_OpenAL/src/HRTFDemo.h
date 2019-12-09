#ifndef __HRTFDEMO_H__
#define __HRTFDEMO_H__

#include "al.h" //audio library -> tipos y funciones b�sicas
#include "alc.h"
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
	bool init(std::string sourceFilename, int sceneWidth, int sceneHeight, const char *hrtfname);

	//Actualiza la l�gica
	bool update();

	//Libera recursos
	void free();

private:
	//Inicializaci�n de OpenAL
	ALCcontext * Context;
	ALCdevice *Device;

	//Objetos de la demo
	ALuint sourceBuffer;
	Source* source;
	Listener * listener;

	float incr;
	int sceneWidth;
	int sceneHeight;
	const char *hrtfname;
	ALCint num_hrtf;

	//M�todos auxiliares
	void renderScenario(Listener* listener, Source* source);
	bool processInput();
	void loadWAV(std::string filename);

	void initOpenAl(bool hrtf);
	void checkHRTFstate();
};
#endif 
