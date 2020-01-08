#include <iostream>
#include <conio.h>

#include <fmod.hpp>
#include <fmod_errors.h>

// Función para comprobar errores de FMOD
// Si se produce un error se termina la ejecución
void ERRCHECK(FMOD_RESULT result)
{
	if (result != FMOD_OK)
	{
		std::cout << FMOD_ErrorString(result) << std::endl;
		exit(-1);
	}
}

FMOD_RESULT result = FMOD_RESULT::FMOD_OK;

int main()
{
	//---------- Inicialización de System ----------//
	// Creamos System
	FMOD::System* FMODSystem;
	result = FMOD::System_Create(&FMODSystem);
	ERRCHECK(result);
	// Inicializamos System
	result = FMODSystem->init(128, FMOD_INIT_NORMAL, nullptr);
	ERRCHECK(result);
	// Inicializamos el motor de audio 3D
	result = FMODSystem->set3DSettings(1.0f, 1.0f, 1.0f);
	ERRCHECK(result);

	//------------------ Listener ------------------//
	// Creamos un Listener
	FMOD_VECTOR listenerPos = { 0, 0, -1 };
	FMOD_VECTOR listenerVel = { 0, 0, 0 };
	FMOD_VECTOR forward = { 1, 0, 0 };
	FMOD_VECTOR up = { 0, 1, 0 };
	result = FMODSystem->set3DListenerAttributes(0, &listenerPos, &listenerVel, &forward, &up);
	ERRCHECK(result);

	//------------------- Source -------------------//
	// Cargamos el archivo y creamos un sonido 3D en loop
	FMOD::Sound* sound;
	result = FMODSystem->createSound("res/footstep.wav", FMOD_3D | FMOD_LOOP_NORMAL, 0, &sound);
	ERRCHECK(result);
	// Asignamos un canal al sonido
	FMOD::Channel* channel;
	float pitch = 1.0f;
	result = FMODSystem->playSound(sound, 0, true, &channel);
	ERRCHECK(result);
	// Asignamos posición y velocidad a la Source
	FMOD_VECTOR sourcePos = { 0, 0, 4 };
	FMOD_VECTOR sourceVel = { 0, 0, 0 };
	result = channel->set3DAttributes(&sourcePos, &sourceVel);
	ERRCHECK(result);

	//------------------- Reverb -------------------//
	// Creamos una Reverb
	FMOD::Reverb3D* reverb;
	result = FMODSystem->createReverb3D(&reverb);
	ERRCHECK(result);
	// Asignamos las propiedades del recinto
	FMOD_REVERB_PROPERTIES properties = FMOD_PRESET_CONCERTHALL;
	result = reverb->setProperties(&properties);
	ERRCHECK(result);
	// Asignamos los atributos de la Reverb
	float minDistance = 1.0f;
	float maxDistance = 10.0f;
	FMOD_VECTOR reverbPos = { 2, 0, 6 };
	result = reverb->set3DAttributes(&reverbPos, minDistance, maxDistance);
	ERRCHECK(result);

	//------------------ Geometry ------------------//
	// Creamos una Geometry
	FMOD::Geometry* geometry;
	FMOD_VECTOR geometryPos = { 0, 0, 0 };
	int polygonIndex;
	const int numVertices = 4;
	float directOcclusion = 1.0f;
	float reverbOcclusion = 1.0f;
	// El polígono está en el plano x-y
	FMOD_VECTOR vertices[numVertices] = {
		{ 2,  2, 0},
		{-2,  2, 0},
		{-2, -2, 0},
		{ 2, -2, 0}
	};
	result = FMODSystem->createGeometry(1, 4, &geometry);
	ERRCHECK(result);
	// Colocamos la Geomtry
	result = geometry->setPosition(&geometryPos);
	ERRCHECK(result);
	result = geometry->setRotation(&forward, &up);
	ERRCHECK(result);
	// Añadimos un polígono a la Geometry
	geometry->addPolygon(directOcclusion, reverbOcclusion, true, numVertices, vertices, &polygonIndex);
	ERRCHECK(result);


	//------------------ MainLoop ------------------//
	// Comienza a reproducirse el sonido de Source
	channel->setPaused(false);

	while (true)
	{
		if (_kbhit())
		{
			// Si se produce una pulsación de tecla,
			// se registra y se procesa el caracter
			char key = _getch();
			if (key == 'W' || key == 'w')
			{
				listenerPos.x += 0.1f;
				result = FMODSystem->set3DListenerAttributes(0, &listenerPos, &listenerVel, &forward, &up);
				ERRCHECK(result);
			}
			else if (key == 'A' || key == 'a')
			{
				listenerPos.z += 0.1f;
				result = FMODSystem->set3DListenerAttributes(0, &listenerPos, &listenerVel, &forward, &up);
				ERRCHECK(result);
			}
			else if (key == 'S' || key == 's')
			{
				listenerPos.x -= 0.1f;
				result = FMODSystem->set3DListenerAttributes(0, &listenerPos, &listenerVel, &forward, &up);
				ERRCHECK(result);
			}
			else if (key == 'D' || key == 'd')
			{
				listenerPos.z -= 0.1f;
				result = FMODSystem->set3DListenerAttributes(0, &listenerPos, &listenerVel, &forward, &up);
				ERRCHECK(result);
			}
			else if (key == 'P')
			{
				pitch += 0.01f;
				result = channel->setPitch(pitch);
				ERRCHECK(result);
			}
			else if(key == 'p')
			{
				pitch -= 0.01f;
				result = channel->setPitch(pitch);
				ERRCHECK(result);
			}
			else if (key == 'R')
			{
				result = reverb->setActive(true);
				ERRCHECK(result);
			}
			else if (key == 'r')
			{
				result = reverb->setActive(false);
				ERRCHECK(result);
			}
			else if (key == 'O')
			{
				result = geometry->setActive(true);
				ERRCHECK(result);
			}
			else if (key == 'o')
			{
				result = geometry->setActive(false);
				ERRCHECK(result);
			}
			else if (key == 'Q' || key == 'q')
			{
				break;
			}

			// Si se produce algún cambió, se actualiza 
			// la información que se muestra en pantalla
			system("CLS");
			bool active;
			std::cout << "Listener Pos - x:" << listenerPos.x << " y: " << listenerPos.y << " z: " << listenerPos.z << std::endl;
			std::cout << "Pitch - " << pitch << std::endl;
			result = reverb->getActive(&active);
			ERRCHECK(result);
			std::cout << "Reverb - " << (active ? "ACTIVE" : "NOT ACTIVE") << std::endl;
			result = geometry->getActive(&active);
			ERRCHECK(result);
			std::cout << "Geometry - " << (active ? "ACTIVE" : "NOT ACTIVE") << std::endl;
		}

		// Se actualiza System
		FMODSystem->update();
	}

	//------------------- Cierre -------------------//
	result = geometry->release();
	ERRCHECK(result);
	result = reverb->release();
	ERRCHECK(result);
	result = channel->stop();
	ERRCHECK(result);
	result = sound->release();
	ERRCHECK(result);
	result = FMODSystem->release();
	ERRCHECK(result);

	return 0;
}