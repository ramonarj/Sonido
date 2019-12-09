#ifndef __HRTFDEMO_H__
#define __HRTFDEMO_H__

#include "al.h" //audio library -> tipos y funciones básicas
#include <string>

class Listener;
class Source;

class HRTFDemo
{
public:
	//Constructora por defecto
	HRTFDemo();
	~HRTFDemo();

	bool update();

	bool init(std::string sourceFilename, int sceneWidth, int sceneHeight);

	void free();


private:
	Listener * listener;
	Source* source;
	float incr;
	ALuint sourceBuffer;
	int sceneWidth;
	int sceneHeight;

	void renderScenario(Listener* listener, Source* source);
	bool processInput();
	void loadWAV(std::string filename);

};
#endif // __HRTFDEMO_H__
