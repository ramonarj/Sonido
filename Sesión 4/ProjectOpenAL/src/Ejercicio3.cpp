#include <stdlib.h> // para el exit
#include <stdio.h>
#include <iostream> // para min y max
#include <algorithm>
#include <conio.h>
#include <time.h>
#include "Source.h"


//class RenderBoard
//{
//public:
//	RenderBoard() : sizeX(0), sizeY(0), numSources(0), sources(nullptr)
//	{
//	}
//	RenderBoard(int sizeX, int sizeY) : sizeX(sizeX), sizeY(sizeY), numSources(0), sources(nullptr) {}
//
//	//Tamaño del tablero
//	int getSize(int i) { if (i == 0) return sizeX; return sizeY; }
//
//	//Añade un source a la escena
//	void addSource(ALfloat* source) { sources[numSources] = source; }
//
//	int sourceNo() { return numSources; }
//
//private:
//	int sizeX;
//	int sizeY;
//	ALfloat **sources;
//	int numSources;
//};
//
//void render(RenderBoard* board, ALfloat* listener, ALfloat* source)
//{
//	for (int i = 0; i < board->getSize(0); i++)
//	{
//		for (int j = 0; j < board->getSize(1); j++)
//		{
//
//			if (i == source[2] + board->getSize(0) / 2 && j == source[0] + board->getSize(1) /2)
//				std::cout << source[1] << " ";
//			else if (i == listener[2] + board->getSize(0) /2 && j == listener[0] + board->getSize(1) /2)
//				std::cout << "L ";
//			else
//				std::cout << "- ";
//		}
//		std::cout << "\n";
//	}
//}

int main(int argc, char* argv[]) 
{

	srand(static_cast<unsigned int>(time(NULL)));

	// INICIALIZACIÓN DE AUDIO
	alutInit(NULL, 0);
	alutGetError();

	// 1. CARGA DE BUFFER
	ALuint footsBuffer = alutCreateBufferFromFile("res/audio/footstepLoop.wav");
	if (alGetError() != AL_NO_ERROR) exit(-1);

	// 2. SOURCES (UNA POR CADA FUENTE)
	Source* footStepSrc = new Source("Footstep");

	//Posición
	ALfloat posSteps[] = { 0.0, 0.0, -2.0 };
	footStepSrc->setPosition(posSteps);
	

	// 3. LINKAR BUFFER CON SOURCE
	footStepSrc->setBuffer(footsBuffer);


	// 4. POSICION DEL LISTENER
	ALfloat posListener[] = { 0.0, 0.0, 0.0 };

	// REPRODUCCIÓN EN LOOP
	footStepSrc->setLooping(true);

	// LE DAMO AL PLEI
	footStepSrc->play();


	float incr = 1.0f;

	//RenderBoard* board = nullptr; // new RenderBoard(30, 30, sources);

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
			//render(board, posListener, posSteps);
		}
	}

	// eliminamos buffers y sources
	alutExit();
}


