#pragma once
#include "estado.h"

/**
 \brief L� os argumentos passados pela QUERY_STRING e interpreta corretamente
 @param query_string string passada pelo url depois do '?' contendo a a��o para ser realizada
 @param e Estado que vai ser alterado conforme a a��o a ser executada
 @param update_enemies Vari�vel que vai guardar se a a��o implica mudan�a de turno
 @return 1 se o estado foi alterado, 0 se n�o foi alterado
*/
int parse_query(const char* query_string, ESTADO* e, int* change_turn);


/**
\brief Cria uma hiperliga��o para uma a��o de movimento
@param dx Altera��o da posi��o do jogador na coordenada x
@param dy Altera��o da posi��o do jogador na coordenada y
@param destination Vari�vel que vai guardar a string da hiperliga��o
*/
void create_move_query(int dx, int dy, char* destination);

/**
\brief Cria uma hiperliga��o para uma a��o de sa�da de n�vel
@param destination Vari�vel que vai guardar a string da hiperliga��o
*/
void create_exit_query(char* destination);

/**
\brief Cria uma hiperliga��o para uma a��o de ataque
@param dx Diferen�a em x do inimigo que o jogador vai atacar
@param dy Diferen�a em y do inimigo que o jogador vai atacar
@param destination Vari�vel que vai guardar a string da hiperliga��o
*/
void create_attack_query(int dx, int dy, char* destination);

/**
\brief Cria uma hiperliga��o para uma a��o de usar uma po��o
@param dx Diferen�a em x da po��o que o jogador vai usar
@param dy Diferen�a em y da po��o que o jogador vai usar
@param destination Vari�vel que vai guardar a string da hiperliga��o
*/
void create_potion_query(int dx, int dy, char* destination);