#include "HRTFDemo.h"

#include <iostream>
#include "Listener.h"
#include "Source.h"
#include <conio.h> //para _getch

#include "AL/alc.h" // audio library context -> no la usamos de momento
#include "AL/alut.h" //audio library utility toolkit -> inicialización y cosas más tochas
#include "AL/alext.h" //Extensión

#include "Utils.h"

#define ESC '\033'

ALfloat lPos[] = { 0,0,0 };
ALfloat lVel[] = { 0,0,0 };
ALfloat lOri[] = { 0.0, 0.0, -1.0,  0.0, 1.0, 0.0 }; //vectores "At" y "Up" (mira hacia el eje Z negativo

ALfloat sourcePos[] = { 0.0, 0.0, -2.0 };

static LPALCGETSTRINGISOFT alcGetStringiSOFT;
static LPALCRESETDEVICESOFT alcResetDeviceSOFT;

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

	// 2. Comprobamos que el HRTF se ha inicializado bien


	// 3. Cargamos los WAVES
	loadWAV(sourceFilename);

	// 4. Creación del Source con su nombre, buffer y posición
	source = new Source("Footstep", sourceBuffer, sourcePos);
	source->setLooping(true); //Ponemos looping a true
	source->play(); //Reproducimos (en este caso, en bucle)

	//5. Creación del Listener con su posición, velocidad y orientación
	listener = new Listener(lPos, lVel, lOri);

	incr = 1.0f;

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

bool HRTFDemo::update()
{
	//1. Renderizar el escenario
	//renderScenario(listener, source);

	//return true;
	//2. Procesar el input
	return processInput();
}

void HRTFDemo::renderScenario(Listener* listener, Source* source)
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



void HRTFDemo::initOpenAl(bool hrtf)
{
	ALCdevice* device;
	ALCcontext* ctx;
	ALboolean has_angle_ext;
	ALCint num_hrtf;
	ALCint hrtf_state;

	//Inicialización: esta función crea el contexto en el que vamos a trabajar (que consta de listener y fuentes)
	//y selecciona el dispositivo según considere (la tarjeta de sonido)
	//Solo puede haber un contexto activo en cada momento
	//Abrimos el dispositivo (por defecto)
	//Device = alcOpenDevice("DirectSound3D");
	device = alcOpenDevice(NULL); //Dispositivo
	//Creamos el contexto (dependiendo de si queremos HRTF o no)
	if (hrtf)
	{
		//Comprobamos que el HRTF es compatible con el dispositivo en el que estamos
		if (!alcIsExtensionPresent(device, "ALC_SOFT_HRTF"))
			fprintf(stderr, "Error: ALC_SOFT_HRTF not supported\n");
		//Creamos el contexto diciendo que queremos HRTF
		ALCint attrs[] = { ALC_HRTF_SOFT, ALC_TRUE,  //Para que se use el HRTF
			ALC_HRTF_ID_SOFT, 0, //Índice del HRTF que queremos usar
			0 }; //Fin de la lista
		ctx = alcCreateContext(device, attrs);
		alcGetIntegerv(device, ALC_NUM_HRTF_SPECIFIERS_SOFT, 1, &num_hrtf);
		if (!num_hrtf)
			printf("No HRTFs found\n");
		else
		{
			ALCint attr[5];
			ALCint index = -1;
			ALCint i;
			printf("Available HRTFs:\n");
			for (i = 0; i < num_hrtf; i++)
			{
				const ALCchar *name = alcGetStringiSOFT(device, ALC_HRTF_SPECIFIER_SOFT, i);
				printf("    %d: %s\n", i, name);
				/* Check if this is the HRTF the user requested. */
				if (hrtfname && (strcmp(name, hrtfname) == 0))
					index = i;
			}
			i = 0;
			attr[i++] = ALC_HRTF_SOFT;
			attr[i++] = ALC_TRUE;
			if (index == -1)
			{
				if (hrtfname)
					printf("HRTF \"%s\" not found\n", hrtfname);
				printf("Using default HRTF...\n");
			}
			else
			{
				printf("Selecting HRTF %d...\n", index);
				attr[i++] = ALC_HRTF_ID_SOFT;
				attr[i++] = index;
			}
			attr[i] = 0;
			if (!alcResetDeviceSOFT(device, attr))
				printf("Failed to reset device: %s\n", alcGetString(device, alcGetError(device)));
		}
	}
	//No queremos HRTF
	else
		ctx = alcCreateContext(device, NULL);
	//Ponemos el contexto como el activo
	alcMakeContextCurrent(ctx);

	alcGetIntegerv(device, ALC_HRTF_SOFT, 1, &hrtf_state);

	if (!hrtf_state)
		printf("HRTF not enabled!\n");
	else
	{
		const ALchar* name = alcGetString(device, ALC_HRTF_SPECIFIER_SOFT);
		printf("HRTF enabled, using %s\n", name);
	}
}

void HRTFDemo::checkHRTFstate()
{

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
		exit(-1);
	}

	//Copia la información de los WAVE al Buffer de datos
	alBufferData(sourceBuffer, format, data, size, freq);

	//Descarga los WAVES
	alutUnloadWAV(format, data, size, freq);
}
