/**
@file estado.h
Definição do estado e das funções que convertem estados em strings e vice-versa
*/

#pragma once

#include "constants.h"

/** \brief O nº máximo de inimigos */
#define MAX_INIMIGOS		100

/** \brief O nº máximo de obstáculos */
#define MAX_OBSTACULOS		100

/**
\brief Estrutura que armazena uma posição
*/
typedef struct posicao {
	char x;
	char y;
} POSICAO;

typedef struct jogador
{
	POSICAO pos;
	int current_health;
	int max_health;
} JOGADOR;

typedef struct inimigo
{
	POSICAO pos;
	int current_health;
	int max_health;
} INIMIGO;

/**
\brief Estrutura que armazena o estado do jogo
*/

typedef struct estado {
	/** A posição do jogador */
	JOGADOR jog;
	/** A posição da saida */
	POSICAO exit;
	/** O nº de inimigos */
	char num_inimigos;
	/** O nº de obstáculos */
	char num_obstaculos;
	/** Array com a posição dos inimigos */
	INIMIGO inimigo[MAX_INIMIGOS];
	/** Array com a posição dos obstáculos */
	POSICAO obstaculo[MAX_OBSTACULOS];
	/** Seed necessária para a função rand() */
	unsigned int gameSeed;
	/* Estado sobre a textura de cada casa */
	char tile_texture_offset[TAM][TAM];
	/* Estado sobre a textura de cada obstáculo */
	char obstacle_texture_offset[TAM][TAM];
	/* Nivel de progresso atual do jogo */
	int level;
	/* Pontuação do jogo atual*/
	int score;
} ESTADO;


/**
\brief Função que converte um estado numa string
@param e O estado
@returns A string correspondente ao estado e
*/
char *estado2str(ESTADO e);

/**
\brief Função que converte uma string num estado 
@param argumentos Uma string contendo os argumentos passados à CGI
@returns O estado correspondente à string dos argumentos
*/
ESTADO str2estado(char *argumentos);

/**
\brief Função que carrega o estado guardado num ficheiro
@param file_name Nome do ficheiro aonde o estado está guardado
@param destination Apontador para o endereço onde vai ser guardado o estado
@returns 0 se o ficheiro nao existir, 1 caso tudo tenha corrido bem
*/
int read_state_from_file(const char* file_name, ESTADO* destination);

/**
\brief Função que guarda o estado do jogo num ficheiro
@param e Estado a ser guardado
@param file_name Nome do ficheiro aonde o estado vai ser guardado
@returns 0 se tiver ocurrido algum erro, 1 caso tudo tenha corrido bem
*/
int output_state_to_file(const ESTADO* e, const char* file_name);
