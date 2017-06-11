#pragma once
#include "estado.h"

/**
\brief Interpreta a string passada e movimenta o jogador de acordo com os parametros presentes na string
@param move_query_string[in] String retirada da QUERY_STRING que vai ser interpretada
@param e[in, out] Estado que vai ser alterado consoante o movimento interpretado
@return 1 se o estado foi alterado, 0 se n�o foi alterado

A fun��o obt�m as dire��es em x e y que o jogador se pretende movimentar usando sscanf()
e o formato especifico do movimento "x=%d&y=%d" e verifica se os valores passados s�o v�lidos
e caso sejam, move o jogador de acordo com esse mesmo x e y
*/
int parse_move_action(const char* move_query_string, ESTADO* e);

/**
\brief Interpreta a string passada e avan�a o jogo para um novo n�vel
@param exit_query_string[in] String retirada da QUERY_STRING que vai ser interpretada
@param e[in, out] Estado que vai ser alterado consoante os param�tros 
@return 1 se o estado foi alterado, 0 se n�o foi alterado

A fun��o obt�m as coordenadas para onde o jogador ser� teleportado no novo n�vel usando sscanf()
e o formato "x=%d&y=%" e coloca o jogador nessa posi��o
O jogador � tamb�m recompensado com um b�nus de pontos equivalente a #define NEW_LEVEL_SCORE_BONUS
E recupera pontos de vida equivalente a metade de #define PLAYER_MAX_HEALTH
*/
int parse_exit_action(const char* exit_query_string, ESTADO* e);

/**
\brief Interpreta a string passada e ataca um inimigo
@param attack_query_string[in] String retirada da QUERY_STRING que vai ser interpretada
@param e[in, out] Estado que vai ser alterado consoante os param�tros
@return 1 se o estado foi alterado, 0 se n�o foi alterado

A fun��o obt�m as dire��es x e y que o jogador pretende atacar usando sscanf()
e o formato "x=%d&y=%" e tenta encontrar se existe um inimigo nessas coordenadas
Caso exista, o inimigo � eliminado e o jogador � tamb�m recompensado 
com um b�nus de pontos equivalente a #define KILL_SCORE_BONUS
*/
int parse_attack_action(const char* attack_query_string, ESTADO* e);

/**
\brief Interpreta a string passada e ataca um inimigo
@param attack_query_string[in] String retirada da QUERY_STRING que vai ser interpretada
@param e[in, out] Estado que vai ser alterado consoante os param�tros
@return 1 se o estado foi alterado, 0 se n�o foi alterado

A fun��o obt�m as dire��es x e y que o jogador pretende atacar usando sscanf()
e o formato "x=%d&y=%" e tenta encontrar se existe um inimigo nessas coordenadas
Caso exista, o inimigo � eliminado e o jogador � tamb�m recompensado
com um b�nus de pontos equivalente a #define KILL_SCORE_BONUS
*/
int parse_potion_action(const char* potion_query_string, ESTADO* e);

/**
 \brief L� os argumentos passados pela QUERY_STRING e interpreta corretamente
 @param query_string[in] string passada pelo url depois do '?' contendo a a��o para ser realizada
 @param e[in, out] Estado que vai ser alterado conforme a a��o a ser executada
 @param change_turn[out] Vari�vel que vai guardar se a a��o implica mudan�a de turno
 @return 1 se o estado foi alterado, 0 se n�o foi alterado
*/
int parse_query(const char* query_string, ESTADO* e, int* change_turn);

/**
\brief Cria uma hiperliga��o para uma a��o de movimento
@param dx[in] Altera��o da posi��o do jogador na coordenada x
@param dy[in] Altera��o da posi��o do jogador na coordenada y
@param destination[out] Vari�vel que vai guardar a string da hiperliga��o
*/
void create_move_query(int dx, int dy, char* destination);

/**
\brief Cria uma hiperliga��o para uma a��o de sa�da de n�vel
@param destination[out] Vari�vel que vai guardar a string da hiperliga��o
*/
void create_exit_query(char* destination);

/**
\brief Cria uma hiperliga��o para uma a��o de ataque
@param dx[in] Diferen�a em x do inimigo que o jogador vai atacar
@param dy[in] Diferen�a em y do inimigo que o jogador vai atacar
@param destination[out] Vari�vel que vai guardar a string da hiperliga��o
*/
void create_attack_query(int dx, int dy, char* destination);

/**
\brief Cria uma hiperliga��o para uma a��o de usar uma po��o
@param dx[in] Diferen�a em x da po��o que o jogador vai usar
@param dy[in] Diferen�a em y da po��o que o jogador vai usar
@param destination[out] Vari�vel que vai guardar a string da hiperliga��o
*/
void create_potion_query(int dx, int dy, char* destination);


