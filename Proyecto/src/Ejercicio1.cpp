//#include <stdlib.h> // para el exit
//#include <stdio.h>
//#include <iostream> // para min y max
//#include <algorithm>
//#include <conio.h>
//#include <time.h>
//#include "Source.h"


//int main(int argc, char* argv[]) {
//
//	// INICIALIZACIÓN DE AUDIO
//	alutInit(NULL, 0);
//	alutGetError();
//
//	// CARGA DE BUFFER
//	ALuint buffer = alutCreateBufferFromFile("../res/audio/1.wav");
//	if (alGetError() != AL_NO_ERROR) exit(-1);
//
//	// Generamos 2 sources (mono) para control independiente
//	ALuint source;
//	alGenSources(1, &source);
//	if (alGetError() != AL_NO_ERROR) exit(-1);
//
//	// ASOCIAMOS EL MISMO BUFFER A AMBOS SOURCES
//	alSourcei(source, AL_BUFFER, buffer);
//
//	// UN SOURCE A LA IZDA Y OTRO A LA DERECHA
//	ALfloat pos[] = { 0.0, 0.0, 0.0 };
//	alSourcefv(source, AL_POSITION, pos);
//
//	// INICIALIZACIÓN DE GANANCIAS DE CADA SOURCE
//	ALfloat gain = 0.5f;
//	ALfloat pitch = 1.0f;
//	alSourcef(source, AL_GAIN, gain);
//	if (alGetError() != AL_NO_ERROR) exit(-1);
//
//	// REPRODUCCIÓN EN LOOP DE AMBOS SOURCES
//	alSourcei(source, AL_LOOPING, 1);
//
//	// ARRANCAMOS AMBOS SOURCES
//	alSourcePlay(source);
//
//	// Loop para JUGAR CON LA GANANCIA DE SOURCES
//	while (true) 
//	{
//		char ch = _getch();
//		if (ch == 'd') pitch = std::min(pitch + 0.1, 2.0);
//		else if(ch == 'a') pitch = std::max(pitch - 0.1, 0.5);
//		alSourcef(source, AL_PITCH, pitch);
//	}
//
//	// eliminamos buffers y sources
//	alutExit();
//}