#include "HRTFDemo.h"

#include "Listener.h"
#include "Source.h"
#include "Utils.h"

#include <conio.h> //para _getch
#include <iostream>

#include "AL/al.h" // audio library -> tipos y funciones básicas de openAL
#include "AL/alc.h" // audio library context -> para dar el contexto al sonido (con un dispositivo, etc.) Para el HRTF.
#include "AL/alut.h" // audio library utility toolkit -> inicialización más cómoda y más utilidades 
#include "AL/alext.h" // audio library extension -> extensión usada para las 2 funciones estáticas a continuación:

static LPALCGETSTRINGISOFT alcGetStringiSOFT;
static LPALCRESETDEVICESOFT alcResetDeviceSOFT;

//Macros
#define ESC '\033'
#define INCR 1.0f
#define HRTF_ID 0 //ID de la hrtf que usamos (0 = default, 2 = default#2, 4 = Built-in). Todas de 44100Hz

//Atributos del listener y source (son globales porque si no desaparecen al salir de contexto)
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

bool HRTFDemo::init(std::string sourceFilename, int sceneWidth, int sceneHeight, const char* hrtfname)
{
	this->sceneWidth = sceneWidth;
	this->sceneHeight = sceneHeight;
	this->hrtfname = hrtfname;

	// 1. Inicializamos OpenAL
	initOpenAl(true);

	// 2. Cargamos los WAVES
	loadWAV(sourceFilename);

	// 3. Creación del Source con su nombre, buffer y posición
	source = new Source("Footstep", sourceBuffer, sourcePos);
	source->setLooping(true); //Ponemos looping a true
	source->play(); //Reproducimos (en este caso, en bucle)

	//4. Creación del Listener con su posición, velocidad y orientación
	listener = new Listener(lPos, lVel, lOri);
	return true;
}

void HRTFDemo::free()
{
	//Eliminamos buffers y sources
	alDeleteBuffers(1, &sourceBuffer);
	if (source != nullptr)
		delete source;
	if (listener != nullptr)
		delete listener;

	//Get active context
	ALCcontext* Context = alcGetCurrentContext();
	//Get device for active context
	ALCdevice* Device = alcGetContextsDevice(Context);
	//Disable context
	alcMakeContextCurrent(NULL);
	//Release context(s)
	alcDestroyContext(Context);
	//Close device
	alcCloseDevice(Device);
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
			posSteps[0] -= INCR;
			break;
		case 'd':
			posSteps[0] += INCR;
			break;
			//Con la S, W movemos en el eje Z
		case 'w':
			posSteps[2] -= INCR;
			break;
		case 's':
			posSteps[2] += INCR;
			break;
			//Con el 1, 2 movemos en el eje Y
		case '1':
			posSteps[1] -= INCR;
			break;
		case '2':
			posSteps[1] += INCR;
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

bool HRTFDemo::update()
{
	//1. Renderizar el escenario
	renderScenario(listener, source);

	//return true;
	//2. Procesar el input
	return processInput();
}

void HRTFDemo::renderScenario(Listener* listener, Source* source)
{
	system("CLS");

	ALfloat* pos = listener->getPosition();
	ALfloat* sourcePos = source->getPosition();

	//Pintamos
	for (int i = -sceneHeight / 2; i < sceneHeight / 2; i++)
	{
		for (int j = -sceneWidth / 2; j < sceneWidth / 2; j++)
		{
			if (pos[0] == j && pos[2] == i) //Listener
				std::cout << "L ";
			else if (sourcePos[0] == j && sourcePos[2] == i) //Source
				std::cout << "S ";
			else
				std::cout << "- ";
		}
		std::cout << std::endl;
	}
	std::cout << "Altura Listener: " << pos[1] << std::endl;
	std::cout << "Altura Source: " << sourcePos[1] << std::endl;
}



void HRTFDemo::initOpenAl(bool hrtf)
{
	//Inicialización: creamos el contexto en el que vamos a trabajar (que consta de listener y fuentes)
	//y selecciona el dispositivo según considere (la tarjeta de sonido)
	//Solo puede haber un contexto activo en cada momento
	ALCdevice* device;
	ALCcontext* ctx;
	ALCint num_hrtf;
	ALCint hrtf_state;


	//1. Abrimos el dispositivo 
	device = alcOpenDevice(NULL); //(por defecto) ("DirectSound3D")

	//2. Creamos el contexto... (dependiendo de si queremos HRTF o no)
	if (hrtf)
	{
		//Comprobamos que el HRTF es compatible con el dispositivo en el que estamos
		if (!alcIsExtensionPresent(device, "ALC_SOFT_HRTF"))
			fprintf(stderr, "Error: ALC_SOFT_HRTF not supported\n");

		//Creamos el contexto diciendo que queremos HRTF
		ALCint attrs[] = { ALC_HRTF_SOFT, ALC_TRUE,  //Para que se use el HRTF
			ALC_HRTF_ID_SOFT, HRTF_ID, //Índice del HRTF
			0 }; //Fin de la lista
		ctx = alcCreateContext(device, attrs);

		//Vemos qué hrtf hay disponible y lo asignamos
		alcGetIntegerv(device, ALC_NUM_HRTF_SPECIFIERS_SOFT, 1, &num_hrtf);
		if (!num_hrtf)
			printf("No HRTFs found\n");
		
	}
	//No queremos HRTF
	else
		ctx = alcCreateContext(device, NULL);

	//2. ... y lo ponemos el contexto como el activo
	alcMakeContextCurrent(ctx);


	//3. Comprobamos que se ha creado bien todo lo relativo al HRTF
	alcGetIntegerv(device, ALC_HRTF_SOFT, 1, &hrtf_state);
	if (!hrtf_state)
		printf("HRTF not enabled!\n");
	else
	{
		const ALchar* name = alcGetString(device, ALC_HRTF_SPECIFIER_SOFT);
		printf("HRTF enabled, using %s\n", name);
	}
}

void HRTFDemo::loadWAV(std::string filename)
{
	//Genera los buffers necesarios
	alGenBuffers(1, &sourceBuffer);

	int error;
	ALsizei size, freq;
	ALenum	format;
	ALvoid	*data;
	ALboolean loop;

	//Carga los archivos WAVE
	alutLoadWAVFile((ALbyte*)filename.c_str(), &format, &data, &size, &freq, &loop);
	if ((error = alGetError()) != AL_NO_ERROR) //Error al cargar el archivo
	{
		DisplayALError("alutLoadWAVFile : ", error);
		alDeleteBuffers(1, &sourceBuffer);
	}

	//Copia la información de los WAVE al Buffer de datos
	alBufferData(sourceBuffer, format, data, size, freq);

	//Descarga los WAVES
	alutUnloadWAV(format, data, size, freq);
}
