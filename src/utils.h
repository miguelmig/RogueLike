/**
@file utils.h
Funções de uso geral 
*/

#pragma once

void print_error(const char* format, ...);
void print_debug(const char* format, ...);

/**
 \brief Gera um número aleatório no range (min, max)

*/
int random_number(int min, int max);

#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))

/**
\brief Cria um cookie no browser do jogador

*/
void write_to_cookie(char *name,
	char *value,
	char *expires,
	char *path,
	char *domain,
	int secure);

