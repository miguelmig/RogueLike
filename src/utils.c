#include "utils.h"
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h> // rand()

#define BUFFER_MAX_LEN 128

void print_error(const char* format, ...)
{
	va_list args;
	va_start(args, format);

	char buffer[BUFFER_MAX_LEN + 1];
	vsnprintf(buffer, sizeof(buffer), format, args);

	va_end(args);
	fputs(buffer, stderr);
}


void print_debug(const char* format, ...)
{
	va_list args;
	va_start(args, format);

	char buffer[BUFFER_MAX_LEN + 1];
	vsnprintf(buffer, sizeof(buffer), format, args);

	va_end(args);
	fputs(buffer, stdout);
}

int random_number(int min, int max)
{
	if ((max - min + 1) != 0)
	{
		return (rand() % (max - min + 1)) + min;
	}
	else
	{
		return -1;
	}
}