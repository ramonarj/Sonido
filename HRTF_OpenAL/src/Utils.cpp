#include "Utils.h"

#include "AL/al.h" 
#include <stdio.h>

void DisplayALError(const char * szText, int errorcode)
{
	printf("%s%s", szText, alGetString(errorcode));
}
