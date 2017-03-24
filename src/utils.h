#pragma once

void print_error(const char* format, ...);
void print_debug(const char* format, ...);

/**
 \brief Returns a random number in range (min, max)

*/
int random_number(int min, int max);