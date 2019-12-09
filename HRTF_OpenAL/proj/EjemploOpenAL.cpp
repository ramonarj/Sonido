//// sample code for 10/7/04 lecture, simplified version of the demo from OpenAL distribution 
//
//// OpenALDemo.cpp : Defines the entry point for the console application.
////
//
//#include <stdio.h>
//#include <conio.h>
//#include <stdlib.h>
//#include "al.h"
//#include "alc.h"
//#include "alut.h"
//#include <memory.h>
//#include <windows.h>
//#include <math.h>
//
//#define PI 3.141592654
//
//#define NUM_BUFFERS 7	// Number of buffers to be Generated
//
//// Global variables
//ALuint	g_Buffers[NUM_BUFFERS];		// Array of Buffer IDs
//
//									// Function prototypes
//ALvoid DisplayALError(ALubyte *szText, ALint errorCode);
//
//// Test Function prototypes
//ALvoid PositionTest(ALvoid);
//ALvoid LoopingTest(ALvoid);
//ALvoid FreqTest(ALvoid);
//ALvoid StereoTest(ALvoid);
//ALvoid GainTest(ALvoid);
//ALvoid RelativeTest(ALvoid);
//ALvoid MultipleSourcesTest(ALvoid);
//ALvoid SourceRollOffTest(ALvoid);
//
///*
//Display AL Error message
//*/
///* In this sample code most error checking from the original openal demo was removed to make it
//easier to read; however in real code it is best to insert error-checking code for debugging; see example below
//for loading files
//*/
//
//ALvoid DisplayALError(ALbyte *szText, ALint errorcode)
//{
//	printf("%s%s", szText, alGetString(errorcode));
//}
//
///*
//Main application - Initializes Open AL, Sets up Listener, Generates Buffers, and loads in audio data.
//Displays Test Menu and calls appropriate Test functions.  On exit, buffers are destroyed and Open AL
//is shutdown.
//
//Each Test function is responsible for creating and destroying whatever Sources they require. All test
//applications use the same set of Buffers (created in this function).
//*/
//int main(int argc, char* argv[])
//{
//	ALint	error;
//
//	ALCcontext *Context;
//	ALCdevice *Device;
//
//	ALfloat listenerPos[] = { 0.0,0.0,0.0 };
//	ALfloat listenerVel[] = { 0.0,0.0,0.0 };
//	ALfloat	listenerOri[] = { 0.0,0.0,-1.0, 0.0,1.0,0.0 };	// Listener facing into the screen
//
//
//	printf("OpenAL Test application\n\n");
//
//	// Initialize Open AL manually
//
//	//Open device
//	Device = alcOpenDevice(NULL); // this is supposed to select the "preferred device"	
//								  //Create context(s)
//	Context = alcCreateContext(Device, NULL);
//	//Set active context
//	alcMakeContextCurrent(Context);
//
//
//	// Set Listener attributes
//	alListenerfv(AL_POSITION, listenerPos); 	// Position ...
//	alListenerfv(AL_VELOCITY, listenerVel); 	// Velocity ...
//	alListenerfv(AL_ORIENTATION, listenerOri); 	// Orientation ...
//	alGenBuffers(NUM_BUFFERS, g_Buffers);  // Generate Buffers
//
//										   // Load in samples to be used by Test functions
//	const char* WaveNames[] = {
//		"res/footstepLoop.wav",
//		"res/Gun1.wav",
//		"res/Gun2.wav",
//	};
//	for (int which_wave = 0; which_wave < sizeof(WaveNames) / sizeof(ALbyte*); ++which_wave)
//	{
//		ALsizei size, freq;
//		ALenum	format;
//		ALvoid	*data;
//		ALboolean loop;
//
//		// Load WaveNames[which_wave]
//		alutLoadWAVFile((ALbyte*)WaveNames[which_wave], &format, &data, &size, &freq, &loop);
//
//		// Copy WaveNames[which_wave] data into AL Buffer which_wave
//		alBufferData(g_Buffers[which_wave], format, data, size, freq);
//
//		// Unload WaveNames[which_wave]
//		alutUnloadWAV(format, data, size, freq);
//	}
//
//	ALbyte ch;
//	do
//	{
//		printf("\nSelect a test from the following options\n\n");
//		printf("1 Position Test\n");
//		printf("2 Looping Test\n");
//		printf("3 Frequency Test\n");
//		printf("4 Stereo Test\n");
//		printf("5 Gain Test\n");
//		printf("6 Source Relative Test\n");
//		printf("7 Multiple Sources Test\n");
//		printf("8 Source Roll-off Test\n");
//		printf("Q to quit\n\n\n");
//
//		ch = _getch();
//		ch = toupper(ch);
//
//		switch (ch)
//		{
//		case '1':
//			PositionTest();
//			break;
//		case '2':
//			LoopingTest();
//			break;
//		case '3':
//			FreqTest();
//			break;
//		case '4':
//			StereoTest();
//			break;
//		case '5':
//			GainTest();
//			break;
//		case '6':
//			RelativeTest();
//			break;
//		case '7':
//			MultipleSourcesTest();
//			break;
//		case '8':
//			SourceRollOffTest();
//			break;
//		default:
//			break;
//		}
//	} while (ch != 'Q');
//
//
//	// Quitting, let's cleanup
//
//	alDeleteBuffers(NUM_BUFFERS, g_Buffers);
//	//Get active context
//	Context = alcGetCurrentContext();
//	//Get device for active context
//	Device = alcGetContextsDevice(Context);
//	//Disable context
//	alcMakeContextCurrent(NULL);
//	//Release context(s)
//	alcDestroyContext(Context);
//	//Close device
//	alcCloseDevice(Device);
//
//	return 0;
//}
//
///*
//Position Test
//Creates 2 Sources - one to the front right of the listener, and one to the rear left of the listener
//*/
//ALvoid PositionTest(ALvoid)
//{
//	ALint	error;
//
//	ALuint	source[2];
//	ALbyte	ch;
//
//	ALfloat source0Pos[] = { -2.0, 0.0, 2.0 };	// Behind and to the left of the listener
//	ALfloat source0Vel[] = { 0.0, 0.0, 0.0 };
//
//	ALfloat source1Pos[] = { 2.0, 0.0, -2.0 };	// Front and to the right of the listener
//	ALfloat source1Vel[] = { 0.0, 0.0, 0.0 };
//
//	alGenSources(2, source);
//
//	alSourcef(source[0], AL_PITCH, 1.0f);
//	alSourcef(source[0], AL_GAIN, 1.0f);
//	alSourcefv(source[0], AL_POSITION, source0Pos);
//	alSourcefv(source[0], AL_VELOCITY, source0Vel);
//	alSourcei(source[0], AL_BUFFER, g_Buffers[1]);
//	alSourcei(source[0], AL_LOOPING, AL_TRUE);
//
//	alSourcef(source[1], AL_PITCH, 1.0f);
//	alSourcef(source[1], AL_GAIN, 1.0f);
//	alSourcefv(source[1], AL_POSITION, source1Pos);
//	alSourcefv(source[1], AL_VELOCITY, source1Vel);
//	alSourcei(source[1], AL_BUFFER, g_Buffers[1]);
//	alSourcei(source[1], AL_LOOPING, AL_FALSE);
//
//	printf("Position Test\n");
//	printf("Press '1' to play source 0 rear left of listener\n");
//	printf("Press '2' to play source 1 once (single shot) front right of listener\n");
//	printf("Press '3' to stop source 0\n");
//	printf("Press '4' to stop source 1\n");
//	printf("Press '5' to set Source 0 Reference Distance to 2\n");
//	printf("Press '6' to set Source 0 Reference Distance to 1\n");
//	printf("Press 'q' to quit\n");
//
//	do
//	{
//		ch = _getch();
//		ch = toupper(ch);
//		switch (ch)
//		{
//		case '1':
//			alSourcePlay(source[0]);
//			break;
//		case '2':
//			alSourcePlay(source[1]);
//			break;
//		case '3':
//			alSourceStop(source[0]);
//			break;
//		case '4':
//			alSourceStop(source[1]);
//			break;
//		case '5':
//			alSourcef(source[0], AL_REFERENCE_DISTANCE, 2.0f);
//			break;
//		case '6':
//			alSourcef(source[0], AL_REFERENCE_DISTANCE, 1.0f);
//			break;
//
//		}
//	} while (ch != 'Q');
//
//	// Release resources
//	alSourceStopv(2, source);
//	alDeleteSources(2, source);
//
//	return;
//}
//
//
///*
//Looping Test
//Tests the ability to switch Looping ON and OFF for a particular source, either before or during
//Playback.  (If looping is switched off during playback, the buffer should finish playing until
//the end of the sample.)
//*/
//ALvoid LoopingTest(ALvoid)
//{
//	ALint	error;
//	ALuint	source[2];
//	ALbyte	ch;
//	ALboolean bLooping0 = AL_FALSE;
//	ALboolean bLooping1 = AL_FALSE;
//
//	ALfloat source0Pos[] = { 2.0, 0.0, 2.0 };	// Front left of the listener
//	ALfloat source0Vel[] = { 0.0, 0.0, 0.0 };
//
//	ALfloat source1Pos[] = { 2.0, 0,0, -2.0 };		// Front right of the listener
//	ALfloat source1Vel[] = { 0.0, 0.0, 0,0 };
//
//
//	alGenSources(2, source);
//
//	alSourcef(source[0], AL_PITCH, 1.0f);
//	alSourcef(source[0], AL_GAIN, 1.0f);
//	alSourcefv(source[0], AL_POSITION, source0Pos);
//	alSourcefv(source[0], AL_VELOCITY, source0Vel);
//	alSourcei(source[0], AL_BUFFER, g_Buffers[0]);
//	alSourcei(source[0], AL_LOOPING, AL_FALSE);
//
//	alSourcef(source[1], AL_PITCH, 1.0f);
//	alSourcef(source[1], AL_GAIN, 1.0f);
//	alSourcefv(source[1], AL_POSITION, source1Pos);
//	alSourcefv(source[1], AL_VELOCITY, source1Vel);
//	alSourcei(source[1], AL_BUFFER, g_Buffers[1]);
//	alSourcei(source[1], AL_LOOPING, AL_FALSE);
//
//	printf("Looping Test\n");
//	printf("Press '1' to play source 0 once (single shot)\n");
//	printf("Press '2' to toggle looping on source 0\n");
//	printf("Press '3' to play source 1 once (single shot)\n");
//	printf("Press '4' to toggle looping on source 1\n");
//	printf("Press 'q' to quit\n");
//	printf("\nSource 0 : Not looping Source 1 : Not looping\r");
//	do
//	{
//		ch = _getch();
//		ch = toupper(ch);
//		switch (ch)
//		{
//		case '1':
//			alSourcePlay(source[0]);
//			break;
//		case '2':
//			if (bLooping0 == AL_FALSE)
//			{
//				bLooping0 = AL_TRUE;
//				if (bLooping1)
//					printf("Source 0 : Looping     Source 1 : Looping    \r");
//				else
//					printf("Source 0 : Looping     Source 1 : Not looping\r");
//			}
//			else
//			{
//				bLooping0 = AL_FALSE;
//				if (bLooping1)
//					printf("Source 0 : Not looping Source 1 : Looping    \r");
//				else
//					printf("Source 0 : Not looping Source 1 : Not looping\r");
//			}
//			alSourcei(source[0], AL_LOOPING, bLooping0);
//			break;
//		case '3':
//			alSourcePlay(source[1]);
//			break;
//		case '4':
//			if (bLooping1 == AL_FALSE)
//			{
//				bLooping1 = AL_TRUE;
//				if (bLooping0)
//					printf("Source 0 : Looping     Source 1 : Looping    \r");
//				else
//					printf("Source 0 : Not looping Source 1 : Looping    \r");
//			}
//			else
//			{
//				bLooping1 = AL_FALSE;
//				if (bLooping0)
//					printf("Source 0 : Looping     Source 1 : Not looping\r");
//				else
//					printf("Source 0 : Not looping Source 1 : Not looping\r");
//			}
//			alSourcei(source[1], AL_LOOPING, bLooping1);
//			break;
//		}
//	} while (ch != 'Q');
//
//	printf("\n");
//
//	// Release resources
//	alSourceStop(source[0]);
//	alDeleteSources(2, source);
//
//	return;
//}
//
///*
//FreqTest
//Test AL_PITCH functionality
//*/
//ALvoid FreqTest(ALvoid)
//{
//	ALint	error;
//	ALuint	source[1];
//	ALbyte	ch;
//	ALfloat source0Pos[] = { 2.0, 0.0,-2.0 };	// Front and right of the listener
//	ALfloat source0Vel[] = { 0.0, 0.0, 0.0 };
//
//
//	alGenSources(1, source);
//
//	alSourcef(source[0], AL_PITCH, 1.0f);
//	alSourcef(source[0], AL_GAIN, 1.0f);
//	alSourcefv(source[0], AL_POSITION, source0Pos);
//	alSourcefv(source[0], AL_VELOCITY, source0Vel);
//	alSourcei(source[0], AL_BUFFER, g_Buffers[1]);
//	alSourcei(source[0], AL_LOOPING, AL_TRUE);
//
//	printf("Frequency Test\n");
//	printf("Press '1' to play source 0 (looping)\n");
//	printf("Press '2' to Double Frequency\n");
//	printf("Press '3' to Halve Frequency\n");
//	printf("Press 'q' to quit\n");
//
//	do
//	{
//		ch = _getch();
//		ch = toupper(ch);
//		switch (ch)
//		{
//		case '1':
//			alSourcePlay(source[0]);
//			break;
//		case '2':
//			alSourcef(source[0], AL_PITCH, 2.0f);
//			break;
//		case '3':
//			alSourcef(source[0], AL_PITCH, 0.5f);
//			break;
//		}
//	} while (ch != 'Q');
//
//	// Release resources
//	alSourceStopv(1, source);
//	alDeleteSources(1, source);
//	return;
//}
//
///*
//Stereo Test
//Plays a stereo buffer
//*/
//ALvoid StereoTest(ALvoid)
//{
//	ALint	error;
//	ALuint	source[1];
//	ALuint  buffers[2];
//	ALuint	Buffer;
//	ALint	BuffersInQueue, BuffersProcessed;
//	ALbyte	ch;
//	ALboolean bLoop = true;
//	ALfloat source0Pos[] = { 2.0, 0.0,-2.0 };	// Front and right of the listener
//	ALfloat source0Vel[] = { 0.0, 0.0, 0.0 };
//
//	alGenSources(1, source);
//
//	buffers[0] = g_Buffers[6];
//	buffers[1] = g_Buffers[6];
//
//	printf("Stereo Test\n");
//	printf("Press '1' to play a stereo buffer on source 0 (looping)\n");
//	printf("Press '2' to play a mono buffer on source 0 (looping)\n");
//	printf("Press '3' to stop source 0\n");
//	printf("Press '4' to queue 2 stereo buffers on source 0 and start playing\n");
//	printf("Press '5' to unqueue the 2 stereo buffers on source 0\n");
//	printf("Press '6' to toggle looping on / off\n");
//	printf("Press '0' to display stats\n");
//	printf("Press 'q' to quit\n");
//	printf("Looping is on\r");
//
//	do
//	{
//		ch = _getch();
//		ch = toupper(ch);
//		switch (ch)
//		{
//		case '1':
//			// Stop source
//			alSourceStop(source[0]);
//			// Attach new buffer
//			alSourcei(source[0], AL_BUFFER, g_Buffers[6]);
//			// Set volume
//			alSourcef(source[0], AL_GAIN, 0.5f);
//			// Set looping
//			alSourcei(source[0], AL_LOOPING, bLoop);
//			// Play source
//			alSourcePlay(source[0]);
//
//			break;
//		case '2':
//			// Stop source
//			alSourceStop(source[0]);
//			// Attach new buffer
//			alSourcei(source[0], AL_BUFFER, g_Buffers[0]);
//			// Set 3D position
//			alSourcefv(source[0], AL_POSITION, source0Pos);
//			// Set 3D velocity
//			alSourcefv(source[0], AL_VELOCITY, source0Vel);
//			// Set volume to full
//			alSourcef(source[0], AL_GAIN, 1.0f);
//			// Set Looping
//			alSourcei(source[0], AL_LOOPING, bLoop);
//			// Play source
//			alSourcePlay(source[0]);
//			break;
//		case '3':
//			// Stop source
//			alSourceStop(source[0]);
//			break;
//		case '4':
//			// Stop source
//			alSourceStop(source[0]);
//			// Attach NULL buffer to source to clear everything
//			alSourcei(source[0], AL_BUFFER, 0);
//			// Queue two buffers
//			alSourceQueueBuffers(source[0], 2, buffers);
//			// Set Looping
//			alSourcei(source[0], AL_LOOPING, bLoop);
//			// Play source
//			alSourcePlay(source[0]);
//			break;
//		case '5':
//			alSourceUnqueueBuffers(source[0], 2, buffers);
//			break;
//		case '6':
//			if (bLoop)
//			{
//				printf("Looping is off\r");
//				bLoop = AL_FALSE;
//			}
//			else
//			{
//				printf("Looping is on  \r");
//				bLoop = AL_TRUE;
//			}
//			alSourcei(source[0], AL_LOOPING, bLoop);
//			break;
//		case '0':
//			// Retrieve number of buffers in queue
//			alGetSourcei(source[0], AL_BUFFERS_QUEUED, &BuffersInQueue);
//			// Retrieve number of processed buffers
//			alGetSourcei(source[0], AL_BUFFERS_PROCESSED, &BuffersProcessed);
//			// Retrieve current buffer
//			alGetSourcei(source[0], AL_BUFFER, (ALint*)&Buffer);
//			if (Buffer == buffers[0])
//				Buffer = 6;
//			else if (Buffer == buffers[1])
//				Buffer = 6;
//			else
//				Buffer = 0;
//
//			printf("Current Buffer is %d, %d Buffers in queue, %d Processed\r", Buffer, BuffersInQueue, BuffersProcessed);
//
//			break;
//		}
//	} while (ch != 'Q');
//
//	// Release resources
//	alSourceStop(source[0]);
//	alDeleteSources(1, source);
//	return;
//}
//
///*
//GainTest
//Play 2 Sources - control gain of each, and control Listener Gain
//*/
//ALvoid GainTest(ALvoid)
//{
//	ALint	error;
//	ALuint	source[2];
//	ALbyte	ch;
//
//	ALfloat source0Pos[] = { 2.0, 0.0,-2.0 };	// Front and right of the listener
//	ALfloat source0Vel[] = { 0.0, 0.0, 0.0 };
//
//	ALfloat source1Pos[] = { -2.0, 0.0,-2.0 };
//	ALfloat source1Vel[] = { 0.0, 0.0, 0.0 };
//
//	alGenSources(2, source);
//
//	alSourcef(source[0], AL_PITCH, 1.0f);
//	alSourcef(source[0], AL_GAIN, 1.0f);
//	alSourcefv(source[0], AL_POSITION, source0Pos);
//	alSourcefv(source[0], AL_VELOCITY, source0Vel);
//	alSourcei(source[0], AL_BUFFER, g_Buffers[0]);
//	alSourcei(source[0], AL_LOOPING, AL_TRUE);
//
//	alSourcef(source[1], AL_PITCH, 1.0f);
//	alSourcef(source[1], AL_GAIN, 1.0f);
//	alSourcefv(source[1], AL_POSITION, source1Pos);
//	alSourcefv(source[1], AL_VELOCITY, source1Vel);
//	alSourcei(source[1], AL_BUFFER, g_Buffers[1]);
//	alSourcei(source[1], AL_LOOPING, AL_TRUE);
//
//	printf("Gain Test\n");
//	printf("Press '1' to play source 0 (looping)\n");
//	printf("Press '2' to play source 1 (looping)\n");
//	printf("Press '3' to stop source 0\n");
//	printf("Press '4' to stop source 1\n");
//	printf("Press '5' to set source 0 gain to 1.0\n");
//	printf("Press '6' to set source 0 gain to 0.5\n");
//	printf("Press '7' to set source 0 gain to 0.25\n");
//	printf("Press '8' to set source 0 gain to 0\n");
//	printf("Press 'a' to set Listener Gain to 1.0\n");
//	printf("Press 'b' to set Listener Gain to 0.5\n");
//	printf("Press 'c' to set Listener Gain to 0.25\n");
//	printf("Press 'd' to set Listener Gain to 0.0\n");
//	printf("Press 'q' to quit\n");
//
//	do
//	{
//		ch = _getch();
//		ch = toupper(ch);
//		switch (ch)
//		{
//		case '1':
//			alSourcePlay(source[0]);
//			break;
//		case '2':
//			alSourcePlay(source[1]);
//			break;
//		case '3':
//			alSourceStop(source[0]);
//			break;
//		case '4':
//			alSourceStop(source[1]);
//			break;
//		case '5':
//			alSourcef(source[0], AL_GAIN, 1.0f);
//			break;
//		case '6':
//			alSourcef(source[0], AL_GAIN, 0.5f);
//			break;
//		case '7':
//			alSourcef(source[0], AL_GAIN, 0.25f);
//			break;
//		case '8':
//			alSourcef(source[0], AL_GAIN, 0.0f);
//			break;
//		case 'A':
//			alListenerf(AL_GAIN, 1.0f);
//			break;
//		case 'B':
//			alListenerf(AL_GAIN, 0.5f);
//			break;
//		case 'C':
//			alListenerf(AL_GAIN, 0.25f);
//			break;
//		case 'D':
//			alListenerf(AL_GAIN, 0.0f);
//			break;
//		}
//	} while (ch != 'Q');
//
//	// Release resources
//	alSourceStopv(2, source);
//
//	alDeleteSources(2, source);
//
//	return;
//}
//
//
//ALvoid RelativeTest(ALvoid)
//{
//	ALint	error;
//
//	ALuint	source[1];
//	ALbyte	ch;
//	ALboolean bRelative = AL_FALSE;
//
//	ALfloat Pos[3];
//	ALfloat LPos[3];
//	ALfloat Vel[] = { 0.0, 0.0, 0.0 };
//
//	alGenSources(1, source);
//
//
//	alSourcef(source[0], AL_PITCH, 1.0f);
//	alSourcef(source[0], AL_GAIN, 1.0f);
//	alSourcefv(source[0], AL_VELOCITY, Vel);
//	alSourcei(source[0], AL_BUFFER, g_Buffers[1]);
//	alSourcei(source[0], AL_LOOPING, AL_TRUE);
//	alSourcei(source[0], AL_SOURCE_RELATIVE, AL_FALSE);
//
//	printf("Source Relative Test\n");
//	printf("Press '1' to play source 0 at 1, 0, 0\n");
//	printf("Press '2' to move listener  to 2, 0, 0\n");
//	printf("Press '3' to toggle SOURCE RELATIVE Mode\n");
//	printf("Press 'q' to quit\n");
//
//	do
//	{
//		ch = _getch();
//		ch = toupper(ch);
//		switch (ch)
//		{
//		case '1':
//			Pos[0] = 1.f;
//			Pos[1] = 0.f;
//			Pos[2] = 0.f;
//			alSourcefv(source[0], AL_POSITION, Pos);
//
//			alSourcePlay(source[0]);
//			break;
//		case '2':
//			LPos[0] = 2.f;
//			LPos[1] = 0.0f;
//			LPos[2] = 0.0f;
//			alListenerfv(AL_POSITION, LPos);
//			break;
//		case '3':
//			if (bRelative)
//			{
//				printf("Source Relative == FALSE\r");
//				alSourcei(source[0], AL_SOURCE_RELATIVE, AL_FALSE);
//				bRelative = AL_FALSE;
//			}
//			else
//			{
//				alSourcei(source[0], AL_SOURCE_RELATIVE, AL_TRUE);
//				printf("Source Relative == TRUE \r");
//				bRelative = AL_TRUE;
//			}
//		}
//	} while (ch != 'Q');
//
//	// Release resources
//	alSourceStopv(1, source);
//	alDeleteSources(1, source);
//
//	return;
//}
//
//ALvoid MultipleSourcesTest()
//{
//	ALuint	numSources = 0;
//	ALuint	Sources[64] = { 0 };
//	ALuint	SourceStopped[64] = { 0 };
//	ALint	error;
//	ALuint	i;
//	char	ch;
//	ALfloat radius;
//	double anglestep;
//	ALfloat pos[3];
//
//	// Generate as many sources as possible (up to 64)
//	for (i = 0; i < 64; i++)
//	{
//		alGenSources(1, &Sources[i]);
//		if ((error = alGetError()) != AL_NO_ERROR)
//			break;
//		else
//			numSources++;
//	}
//
//	printf("Multiple Sources Test\n\n");
//	printf("Generated %d Sources\n", numSources);
//
//	// Set sources to located in a circle around the listener
//
//	anglestep = (2 * PI) / (ALfloat)numSources;
//	radius = 2.0f;
//
//	for (i = 0; i < numSources; i++)
//	{
//		// Attach buffer
//		alSourcei(Sources[i], AL_BUFFER, g_Buffers[0]);
//
//		// Set position
//		pos[0] = (float)(cos(anglestep*i) * radius);
//		pos[1] = 0.0f;
//		pos[2] = (float)(sin(anglestep*i) * radius);
//		alSourcefv(Sources[i], AL_POSITION, pos);
//
//		// Enable looping
//		alSourcei(Sources[i], AL_LOOPING, AL_TRUE);
//	}
//
//
//	printf("Press '1' to start playing Sources seperately\n");
//	printf("Press '2' to stop playing Sources seperately\n");
//	printf("Press 'q' to quit\n");
//
//	do
//	{
//		ch = _getch();
//		ch = toupper(ch);
//		switch (ch)
//		{
//		case '1':
//			for (i = 0; i < numSources; i++)
//			{
//				alSourcePlay(Sources[i]);
//
//				// Delay a little
//				Sleep(100);
//			}
//			break;
//		case '2':
//			alSourceStopv(numSources, Sources);
//			break;
//		}
//	} while (ch != 'Q');
//
//	// Delete the Sources
//	alDeleteSources(numSources, Sources);
//}
//
//ALvoid SourceRollOffTest()
//{
//	ALint	error;
//
//	ALuint	source[2];
//	ALbyte	ch;
//
//	ALfloat source0Pos[] = { -10.0, 0.0, 10.0 };	// Behind and to the left of the listener
//	ALfloat source1Pos[] = { 10.0, 0.0, -10.0 };	// Front and to the right of the listener
//
//	alGenSources(2, source);
//
//	alSourcefv(source[0], AL_POSITION, source0Pos);
//	alSourcei(source[0], AL_BUFFER, g_Buffers[1]);
//	alSourcei(source[0], AL_LOOPING, AL_TRUE);
//
//	alSourcefv(source[1], AL_POSITION, source1Pos);
//	alSourcei(source[1], AL_BUFFER, g_Buffers[1]);
//	alSourcei(source[1], AL_LOOPING, AL_TRUE);
//
//	printf("Source Roll-off Test\n");
//	printf("Press '1' to play source 0 rear left of listener\n");
//	printf("Press '2' to stop source 0\n");
//	printf("Press '3' to play source 1 front right of listener\n");
//	printf("Press '4' to stop source 1\n");
//	printf("Press '5' to set Source 0 Roff-off Factor to 0.5\n");
//	printf("Press '6' to set Source 0 Roll-off Factor to 1.0\n");
//	printf("Press '7' to set Source 0 Roll-off Factor to 2.0\n");
//	printf("Press '8' to set Source 1 Roff-off Factor to 0.5\n");
//	printf("Press '9' to set Source 1 Roll-off Factor to 1.0\n");
//	printf("Press 'A' to set Source 1 Roll-off Factor to 2.0\n");
//
//	printf("Press 'q' to quit\n");
//
//	do
//	{
//		ch = _getch();
//		ch = toupper(ch);
//		switch (ch)
//		{
//		case '1':
//			alSourcePlay(source[0]);
//			break;
//		case '2':
//			alSourceStop(source[0]);
//			break;
//		case '3':
//			alSourcePlay(source[1]);
//			break;
//		case '4':
//			alSourceStop(source[1]);
//			break;
//		case '5':
//			alSourcef(source[0], AL_ROLLOFF_FACTOR, 0.5f);
//			break;
//		case '6':
//			alSourcef(source[0], AL_ROLLOFF_FACTOR, 1.0f);
//			break;
//		case '7':
//			alSourcef(source[0], AL_ROLLOFF_FACTOR, 2.0f);
//			break;
//		case '8':
//			alSourcef(source[1], AL_ROLLOFF_FACTOR, 0.5f);
//			break;
//		case '9':
//			alSourcef(source[1], AL_ROLLOFF_FACTOR, 1.0f);
//			break;
//		case 'A':
//			alSourcef(source[1], AL_ROLLOFF_FACTOR, 2.0f);
//			break;
//		}
//	} while (ch != 'Q');
//
//	// Release resources
//	alSourceStopv(2, source);
//	alDeleteSources(2, source);
//
//	return;
//}