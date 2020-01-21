#ifndef __HRTFDEMO_H__
#define __HRTFDEMO_H__

class Listener;
class Source;
struct ALCcontext;
struct ALCdevice;

class HRTFDemo
{
private:
	//Objetos de la demo
	Source* source;
	Listener* listener;
	unsigned int sourceBuffer;

	// Parámetros de la demo
	int sceneWidth;
	int sceneHeight;
	const char* hrtfname;

public:
	//Constructora por defecto
	HRTFDemo();
	~HRTFDemo();

	//Inicializa recursos
	bool init(const char* sourceFilename, int sceneWidth, int sceneHeight, const char *hrtfname);

	//Actualiza la lógica
	bool update();

	//Libera recursos
	void free();

private:
	//Métodos auxiliares
	void renderScenario(Listener* listener, Source* source);
	bool processInput();
	void initOpenAl(bool hrtf);
	void loadWAV(const char* filename);
};

#endif // !__HRTFDEMO_H__