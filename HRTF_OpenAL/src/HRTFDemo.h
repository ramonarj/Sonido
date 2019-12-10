#ifndef __HRTFDEMO_H__
#define __HRTFDEMO_H__

#include <string>

class Listener;
class Source;
struct ALCcontext;
struct ALCdevice;
typedef unsigned int ALuint;

class HRTFDemo
{
public:
	//Constructora por defecto
	HRTFDemo();
	~HRTFDemo();

	//Inicializa recursos
	bool init(std::string sourceFilename, int sceneWidth, int sceneHeight, const char *hrtfname);

	//Actualiza la lógica
	bool update();

	//Libera recursos
	void free();

private:
	//Objetos de la demo
	Source* source;
	Listener * listener;
	ALuint sourceBuffer;

	float incr;
	int sceneWidth;
	int sceneHeight;
	const char *hrtfname;

	//Métodos auxiliares
	void renderScenario(Listener* listener, Source* source);
	bool processInput();
	void loadWAV(std::string filename);

	void initOpenAl(bool hrtf);
};
#endif 
