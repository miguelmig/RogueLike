/**
  *	@file estado.h
  * @brief Definição do estado e das funções que convertem estados em strings e vice-versa
*/

#pragma once

#include "constants.h"

/** \brief O nº máximo de inimigos */
#define MAX_INIMIGOS		100

/** \brief O nº máximo de obstáculos */
#define MAX_OBSTACULOS		100

/** \brief O nº máximo de poções */
#define MAX_POCOES 5

/**
\brief Estrutura que armazena uma posição
*/
typedef struct posicao {
	char x;
	char y;
} POSICAO;

/**
\brief Estrutura que armazena informação sobre o jogador
*/
typedef struct jogador
{
	POSICAO pos;
	int current_health;
	int max_health;
} JOGADOR;



/**
\brief Estrutura que armazena informação sobre cada inimigo
*/

typedef struct inimigo
{
	int id;
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
	/** O nº de poções */
	char num_pocoes;
	/** Array com a posição dos inimigos */
	INIMIGO inimigo[MAX_INIMIGOS];
	/** Array com a posição dos obstáculos */
	POSICAO obstaculo[MAX_OBSTACULOS];
	/** Array com a posição das poções */
	POSICAO pocoes[MAX_POCOES];
	/** Seed necessária para a função rand() */
	unsigned int gameSeed;
	/* Estado sobre a textura de cada casa */
	char tile_texture_offset[TAM][TAM];
	/* Estado sobre a textura de cada obstáculo */
	char obstacle_texture_offset[TAM][TAM];
	/* Estado sobre a textura de cada inimigo */
	char enemy_texture_offset[MAX_INIMIGOS];
	/* Nivel de progresso atual do jogo */
	int level;
	/* Pontuação do jogo atual */
	int score;
	/* Número de Inimigos Mortos */
	int inimigos_mortos;
	/* Número de Poções Usadas */
	int pocoes_usadas;
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
@returns 0 se o ficheiro nao existir, ou caso exista, o número de bytes lidos
*/
int read_state_from_file(const char* file_name, ESTADO* destination);

/**
\brief Função que guarda o estado do jogo num ficheiro
@param e Estado a ser guardado
@param file_name Nome do ficheiro aonde o estado vai ser guardado
@returns 0 se tiver ocurrido algum erro, 1 caso tudo tenha corrido bem
*/
int output_state_to_file(const ESTADO* e, const char* file_name);


/**
\brief Função que carrega o estado guardado num cookie
@param request_header_string String contendo o cookie 
@param destination Apontador para o endereço onde vai ser guardado o estado
@returns 0 se o cookie nao existir, 1 caso tudo tenha corrido bem
*/
int read_state_from_request_header(const char* request_header_string, ESTADO* destination);

/**
\brief Função que guarda o estado do jogo num cookie
@param e Estado a ser guardado
@returns 0 se tiver ocurrido algum erro, 1 caso tudo tenha corrido bem
*/
int output_state_to_cookie(const ESTADO* e);
