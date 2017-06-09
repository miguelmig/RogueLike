#include <stdio.h>
#include "estado.h"
#include <string.h>
#define MAX_BUFFER		10240

char *estado2str(ESTADO e) {
	static char buffer[MAX_BUFFER];
	unsigned char *p = (unsigned char *)&e;
	unsigned int i,j;

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
	unsigned int i;

	for(i = 0; i < sizeof(ESTADO); i++, argumentos += 2) {
		unsigned int d;
		sscanf(argumentos, "%2x", &d);
		p[i] = (unsigned char)d;
	}
	
	return e;
}

int read_state_from_file(const char* file_name, ESTADO* destination)
{
	if (destination == NULL)
	{
		return 0;
	}

	FILE* f = fopen(file_name, "rb");
	if (f == NULL)
	{
		return 0;
	}

	static char buffer[MAX_BUFFER];
	int num_bytes_read = fread(buffer, sizeof(char), MAX_BUFFER, f);
	fclose(f);
	ESTADO e = str2estado(buffer);
	*destination = e;
	return 1;
}

int output_state_to_file(const ESTADO* e, const char* file_name)
{
	if (e == NULL)
	{
		return 0;
	}

	// Serialize game state to a byte string
	char* serialized_state_data = estado2str(*e);
	size_t size_of_data = strlen(serialized_state_data) + sizeof(char); // 1 extra byte for null terminator

	FILE* f = fopen(file_name, "wb");
	if (f == NULL)
	{
		return 0;
	}

	fwrite((const void*)serialized_state_data, sizeof(char), size_of_data, f);
	fclose(f);
	return 1;
}