#include <stdlib.h> // para el exit
#include <iostream> // para min y max
#include <algorithm>
#include <conio.h> //para _getch

#include "alc.h" // audio library context -> no la usamos de momento
#include "alut.h" //audio library utility toolkit -> inicialización y cosas más tochas

#include "Source.h"
#include "Listener.h"

//LOS WAV TIENEN QUE ESTAR EN FORMATO MONO!!
int main(int argc, char* argv[]) 
{
	//Inicialización: esta función crea el contexto en el que vamos a trabajar (que consta de listener y fuentes)
	//y selecciona el dispositivo según considere (la tarjeta de sonido)
	//Solo puede haber un contexto activo en cada momento
	alutInit(NULL, 0); 
	alutGetError();

	//Es lo mismo que hacer:
	//ALCdevice *Device = alcOpenDevice((ALubyte*) "DirectSound3D");
	//ALCcontext *Context = alcCreateContext(Device, NULL);
	//alcMakeContextCurrent(Context);

	// 1. Carga de buffers (con alut es solo una línea)
	ALuint footsBuffer = alutCreateBufferFromFile("res/footstepLoop.wav");
	if (alGetError() != AL_NO_ERROR) exit(-1);

	// 2. Creación del source con su nombre, buffer y posición
	ALfloat posSteps[] = { 0.0, 0.0, -2.0 };
	Source* footStepSrc = new Source("Footstep", footsBuffer, posSteps);
	footStepSrc->setLooping(true); //Ponemos looping a true
	footStepSrc->play(); //Reproducimos (en este caso, en bucle)

	//3. Creación del listener con su posición, velocidad y orientación
	ALfloat lPos[] = { 0,0,0 }; 
	ALfloat lVel[] = { 0,0,0 };
	ALfloat lOri[] = { 0.0, 0.0, -1.0,  0.0, 1.0, 0.0 }; //vectores "At" y "Up" (mira hacia el eje Z negativo)
	Listener* listener = new Listener(lPos, lVel, lOri);

	float incr = 1.0f;

	//Bucle de renderizado de audio
	while (true)
	{
		char ch = _getch();
		//Procesamos el input
		if (ch != '\0')
		{
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
				if(footStepSrc->isPlaying())
					footStepSrc->pause();
				else
					footStepSrc->play();
				break;
				//Con la Q se para del todo la reproducción (se reinicia con la P)
			case 'q':
				footStepSrc->stop();
				break;
			default:
				break;
			}
			//Actualizamos la posición del Source
			footStepSrc->setPosition(posSteps);
		}
	}

	//Eliminamos buffers y sources
	alDeleteBuffers(1, &footsBuffer);
	if(footStepSrc != nullptr)
		delete footStepSrc;
	if (listener != nullptr)
		delete listener;

	//alutExit
	alutExit();
}


