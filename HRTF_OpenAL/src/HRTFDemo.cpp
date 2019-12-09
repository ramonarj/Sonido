#include "HRTFDemo.h"

#include <iostream>
#include "Listener.h"
#include "Source.h"
#include <conio.h> //para _getch

#include "alc.h" // audio library context -> no la usamos de momento
#include "alut.h" //audio library utility toolkit -> inicialización y cosas más tochas

#define ESC '\033'

ALfloat lPos[] = { 0,0,0 };
ALfloat lVel[] = { 0,0,0 };
ALfloat lOri[] = { 0.0, 0.0, -1.0,  0.0, 1.0, 0.0 }; //vectores "At" y "Up" (mira hacia el eje Z negativo)

ALfloat sourcePos[] = { 0.0, 0.0, -2.0 };

HRTFDemo::HRTFDemo() :  listener(nullptr), source(nullptr), incr(0), sceneWidth(0), sceneHeight(0)
{

}

HRTFDemo::~HRTFDemo()
{
}

bool HRTFDemo::update()
{
	//1. Renderizar el escenario
	renderScenario(listener, source);

	//return true;
	//2. Procesar el input
	return processInput();
}

bool HRTFDemo::init(std::string sourceFilename, int sceneWidth, int sceneHeight)
{
	this->sceneWidth = sceneWidth;
	this->sceneHeight = sceneHeight;

	//Inicialización: esta función crea el contexto en el que vamos a trabajar (que consta de listener y fuentes)
	//y selecciona el dispositivo según considere (la tarjeta de sonido)
	//Solo puede haber un contexto activo en cada momento


	//Es lo mismo que hacer:
	//ALCdevice *Device = alcOpenDevice((ALubyte*) "DirectSound3D");
	//ALCcontext *Context = alcCreateContext(Device, NULL);
	//alcMakeContextCurrent(Context);

	//Inicializar OpenAL
	alutInit(NULL, 0);
	alutGetError();


	// 1. Carga de buffers (con alut es solo una línea)
	sourceBuffer = alutCreateBufferFromFile(sourceFilename.c_str());
	if (alGetError() != AL_NO_ERROR)
		return false;

	// 2. Creación del source con su nombre, buffer y posición
	source = new Source("Footstep", sourceBuffer, sourcePos);
	source->setLooping(true); //Ponemos looping a true
	source->play(); //Reproducimos (en este caso, en bucle)

	//3. Creación del listener con su posición, velocidad y orientación
	listener = new Listener(lPos, lVel, lOri);

	incr = 1.0f;
}

void HRTFDemo::free()
{
	//Eliminamos buffers y sources
	alDeleteBuffers(1, &sourceBuffer);
	if (source != nullptr)
		delete source;
	if (listener != nullptr)
		delete listener;

	//alutExit
	alutExit();
}

void HRTFDemo::renderScenario(Listener * listener, Source * source)
{
	ALfloat* pos = listener->getPosition();
	ALfloat* sourcePos = source->getPosition();
	system("CLS");
	for (int i = -sceneHeight / 2; i < sceneHeight / 2; i++)
	{
		for (int j = -sceneWidth / 2; j < sceneWidth / 2; j++)
		{
			if (pos[0] == j && pos[2] == i)
				std::cout << "L ";
			else if (sourcePos[0] == j && sourcePos[2] == i)
				std::cout << "S ";
			else
				std::cout << "- ";
		}
		std::cout << std::endl;
	}
	std::cout << "Altura Listener: " << pos[1] << std::endl;
	std::cout << "Altura Source: " << sourcePos[1] << std::endl;
}

bool HRTFDemo::processInput()
{
	//1. Procesar el input
	char ch = _getch();
	if (ch != '\0')
	{
		ALfloat* posSteps = source->getPosition();
		switch (ch)
		{
			//Con la A, D movemos en el eje X
		case 'a':
			posSteps[0] -= incr;
			break;
		case 'd':
			posSteps[0] += incr;
			break;
			//Con la S, W movemos en el eje Z
		case 'w':
			posSteps[2] -= incr;
			break;
		case 's':
			posSteps[2] += incr;
			break;
			//Con el 1, 2 movemos en el eje Y
		case '1':
			posSteps[1] -= incr;
			break;
		case '2':
			posSteps[1] += incr;
			break;
			//Con la P pausamos/reanudamos la reproducción del source
		case 'p':
			if (source->isPlaying())
				source->pause();
			else
				source->play();
			break;
			//Con la Q se para del todo la reproducción (se reinicia con la P)
		case 'q':
			source->stop();
			break;
		case ESC:
			return false;
			break;
		default:
			break;
		}
		//Actualizamos la posición del Source
		source->setPosition(posSteps);
	}
	return true;
}
