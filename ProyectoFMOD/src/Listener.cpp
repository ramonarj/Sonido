#include "Listener.h"
#include "System.h"

Listener::Listener(FMOD_VECTOR pos, FMOD_VECTOR vel, FMOD_VECTOR forward, FMOD_VECTOR up) : 
	position_(pos), 
	velocity_(vel),
	forward_(forward),
	up_(up)
{


}

Listener::~Listener()
{

}
