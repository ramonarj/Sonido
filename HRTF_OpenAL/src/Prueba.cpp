#include "HRTFDemo.h"


//LOS WAV TIENEN QUE ESTAR EN FORMATO MONO!!
int main(int argc, char* argv[]) 
{
	//Creamos la demo y la inicializamos
	HRTFDemo hrtfDemo = HRTFDemo();
	if(!hrtfDemo.init("res/footstepLoop.wav", 20, 20))
		exit(-1);

	//Actualizamos
	while (hrtfDemo.update());

	//Liberamos y nos vamos
	hrtfDemo.free();
}