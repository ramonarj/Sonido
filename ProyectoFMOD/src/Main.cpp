#include <cmath>
#include <conio.h>
#include <algorithm>
#include <unordered_map>

#include "AudioSource.h"

static int octave = 0;
static std::unordered_map<char, float> keys;
const static std::string RESOURCES_PATH = "..\\res\\";

static float calculateKeyPitch(char c) { return powf(2, (keys[c] + (12 * octave)) / 12); }

int main()
{
	keys['z'] = 0;	// DO
	keys['s'] = 1;	// DO#
	keys['x'] = 2;	// RE
	keys['d'] = 3;	// MIb
	keys['c'] = 4;	// MI
	keys['v'] = 5;	// FA
	keys['g'] = 6;	// FA#
	keys['b'] = 7;	// SOL
	keys['h'] = 8;	// LAb
	keys['n'] = 9;	// LA
	keys['j'] = 10;	// SIb
	keys['m'] = 11;	// SI
	keys[','] = 12;	// DO

	System::init();
	AudioSource sound(RESOURCES_PATH + "piano.ogg");

	char c = ' ';
	while (c != '\x1b')
	{
		c = _getch();
		if (c == '+')
		{
			octave = std::min(octave + 1, 3);
			std::cout << "Octave: " << octave << std::endl;
		}
		else if (c == '-') 
		{
			octave = std::max(octave - 1, -3);
			std::cout << "Octave: " << octave << std::endl;
		}
		else 
		{
			float pitch = calculateKeyPitch(c);
			sound.setPitch(pitch);
			sound.play();
		}

		System::update();
	}

	System::release();
	return 0;
}