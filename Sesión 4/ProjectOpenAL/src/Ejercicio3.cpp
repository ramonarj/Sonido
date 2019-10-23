#include <stdlib.h> // para el exit
#include <stdio.h>
#include <iostream> // para min y max
#include <algorithm>
#include <conio.h>
#include <time.h>
#include "Source.h"


int main(int argc, char* argv[]) 
{

	srand(static_cast<unsigned int>(time(NULL)));

	// INICIALIZACIÓN DE AUDIO
	alutInit(NULL, 0);
	alutGetError();

	// 1. CARGA DE BUFFER
	ALuint footsBuffer = alutCreateBufferFromFile("res/audio/footstepLoop.wav");
	if (alGetError() != AL_NO_ERROR) exit(-1);

	// 2. Creación del source con su nombre, buffer y posición
	ALfloat posSteps[] = { 0.0, 0.0, -2.0 };
	Source* footStepSrc = new Source("Footstep", footsBuffer, posSteps);
	footStepSrc->setLooping(true); //Ponemos looping a true
	footStepSrc->play(); //Reproducimos (en este caso, en bucle)


	float incr = 1.0f;


	// Loop
	while (true)
	{
		char ch = _getch();
		if (ch != '\0')
		{
			switch (ch)
			{
			case 'a':
				posSteps[0] -= incr;
				break;
			case 'd':
				posSteps[0] += incr;
				break;
			case 'w':
				posSteps[2] -= incr;
				break;
			case 's':
				posSteps[2] += incr;
				break;
			case '1':
				posSteps[1] -= incr;
				break;
			case '2':
				posSteps[1] += incr;
				break;
			default:
				break;
			}
			footStepSrc->setPosition(posSteps);
			system("cls");
		}
	}

	// eliminamos buffers y sources
	alutExit();
}


