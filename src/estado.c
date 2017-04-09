#include <stdio.h>
#include "estado.h"

#define MAX_BUFFER		10240

char *estado2str(ESTADO e) {
	static char buffer[MAX_BUFFER];
	unsigned char *p = (unsigned char *)&e;
	int i,j;

	for (i = 0, j = 0; i < sizeof(ESTADO); i++, j += 2)
	{
		sprintf((char*)(buffer + j), "%02x", p[i]);
	}

	buffer[j] = 0;

	return buffer;
}

ESTADO str2estado(char *argumentos) {
	ESTADO e;
	unsigned char *p = (unsigned char *) &e;
	int i;

	for(i = 0; i < sizeof(ESTADO); i++, argumentos += 2) {
		unsigned int d;
		sscanf(argumentos, "%2x", &d);
		p[i] = (unsigned char)d;
	}
	
	return e;
}

