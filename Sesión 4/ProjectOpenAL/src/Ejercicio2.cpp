//#include <stdlib.h> // para el exit
//#include <stdio.h>
//#include <iostream> // para min y max
//#include <algorithm>
//#include <conio.h>
//#include <time.h>
//#include "Source.h"

//const int MAX_TIME = 5;
//const int MIN_TIME = 2;
//const int MAX_DIST = 20;
//const int MIN_DIST = -20;

//int main(int argc, char* argv[]) {
//
//	srand(static_cast<unsigned int>(time(NULL)));
//
//	// INICIALIZACIÓN DE AUDIO
//	alutInit(NULL, 0);
//	alutGetError();
//
//	// 1. CARGA DE BUFFER
//	ALuint battleBuffer = alutCreateBufferFromFile("../res/audio/Battle.wav");
//	ALuint gun1Buffer = alutCreateBufferFromFile("../res/audio/Gun1.wav");
//	ALuint gun2Buffer = alutCreateBufferFromFile("../res/audio/Gun2.wav");
//	if (alGetError() != AL_NO_ERROR) exit(-1);
//
//	// 2. SOURCES (UNA POR CADA FUENTE)
//	ALuint battleSource, gun1Source, gun2Source;
//	alGenSources(1, &battleSource);
//	alGenSources(1, &gun1Source);
//	alGenSources(1, &gun2Source);
//	if (alGetError() != AL_NO_ERROR) exit(-1);
//
//	// 3. LINKAR BUFFER CON SOURCE
//	alSourcei(battleSource, AL_BUFFER, battleBuffer);
//	alSourcei(gun1Source, AL_BUFFER, gun1Buffer);
//	alSourcei(gun2Source, AL_BUFFER, gun2Buffer);
//
//	// 4. POSICIONES DE LOS SOURCES
//	ALfloat posBattle[] = { 0.0, 0.0, -1.0 },   
//		posGun1[] = { -2.0, 0.0, 0.0 },  
//		posGun2[] = { 2.0, 4.0, 0.0 };  
//	alSourcefv(battleSource, AL_POSITION, posBattle);
//	alSourcefv(gun1Source, AL_POSITION, posGun1);
//	alSourcefv(gun2Source, AL_POSITION, posGun2);
//
//	// INICIALIZACIÓN DE GANANCIAS DE CADA SOURCE
//	//ALfloat gainL = 0.5f, gainR = 0.5f;
//	//alSourcef(battleSource, AL_GAIN, gainL);
//	//alSourcef(gun1Source, AL_GAIN, gainR);
//	//if (alGetError() != AL_NO_ERROR) exit(-1);
//
//	// REPRODUCCIÓN EN LOOP
//	alSourcei(battleSource, AL_LOOPING, 1);
//
//	// LE DAMO AL PLEI
//	alSourcePlay(battleSource);
//
//	
//	int t = MIN_TIME + rand() % (MAX_TIME - MIN_TIME);
//
//	// Loop
//	while (true) 
//	{
//		posGun1[0] = MIN_DIST + rand() % (MAX_DIST - MIN_DIST);
//		posGun1[1] = MIN_DIST + rand() % (MAX_DIST - MIN_DIST);
//		posGun1[2] = MIN_DIST + rand() % (MAX_DIST - MIN_DIST);
//
//		posGun2[0] = MIN_DIST + rand() % (MAX_DIST - MIN_DIST);
//		posGun2[1] = MIN_DIST + rand() % (MAX_DIST - MIN_DIST);
//		posGun2[2] = MIN_DIST + rand() % (MAX_DIST - MIN_DIST);
//
//
//	}
//
//	// eliminamos buffers y sources
//	alutExit();
//}