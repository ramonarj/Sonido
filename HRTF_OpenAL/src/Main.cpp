#include "HRTFDemo.h"

//LOS WAV TIENEN QUE ESTAR EN FORMATO MONO!!
int main(int argc, char* argv[]) 
{
	//Creamos la demo y la inicializamos
	HRTFDemo hrtfDemo = HRTFDemo();
	if (!hrtfDemo.init("res/audio/footstepLoop.wav", 20, 20, "res/hrtf/IRC_1005.def"))
		return -1;

	//Actualizamos
	while (hrtfDemo.update());

	//Liberamos y nos vamos
	hrtfDemo.free();

	return 0;
}