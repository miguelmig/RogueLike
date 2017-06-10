#include <stdio.h>
#include "estado.h"
#include <string.h>
#include "utils.h" // write_to_cookie
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
	return num_bytes_read;
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

int read_state_from_request_header(const char* request_header_string, ESTADO* destination)
{
	if (destination == NULL)
	{
		return 0;
	}

	static char gamestate1[MAX_BUFFER];
	static char gamestate2[MAX_BUFFER];

	static char final_state_str[MAX_BUFFER];

	sscanf(request_header_string, "gamestate1=%s; gamestate2=%s", gamestate1, gamestate2);
	int gamestate1_len = strlen(gamestate1);
	int gamestate2_len = strlen(gamestate2);
	strncpy(final_state_str, gamestate1, gamestate1_len);
	strncpy(final_state_str + gamestate1_len, gamestate2, gamestate2_len);

	ESTADO e = str2estado(final_state_str);
	*destination = e;
	return 1;

}

int output_state_to_cookie(const ESTADO* e)
{
	if (e == NULL)
	{
		return 0;
	}

	// Serialize game state to a byte string
	char* serialized_state_data = estado2str(*e);
	size_t size_of_data = strlen(serialized_state_data) + sizeof(char); // 1 extra byte for null terminator

	static char first_buffer[MAX_BUFFER];

	strncpy(first_buffer, serialized_state_data, 2000);
	//first_buffer[2000] = '\0';
	char* new_start = serialized_state_data + 2000;

	static char second_buffer[MAX_BUFFER];
	strncpy(second_buffer, new_start, 2200);


	write_to_cookie(COOKIE_NAME "1", first_buffer, "Sun, 15 Jul 2018 00:00:01 GMT", NULL, NULL, 0);

	write_to_cookie(COOKIE_NAME "2", second_buffer, "Sun, 15 Jul 2018 00:00:01 GMT", NULL, NULL, 0);

	return 1;
}