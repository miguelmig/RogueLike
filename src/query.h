#pragma once
#include "estado.h"

/**
 \brief Lê os argumentos passados pela QUERY_STRING e interpreta corretamente
 @param query_string string passada pelo url depois do '?' contendo a ação para ser realizada
 @param e Estado que vai ser alterado conforme a ação a ser executada
 @param update_enemies Variável que vai guardar se a ação implica mudança de turno
 @return 1 se o estado foi alterado, 0 se não foi alterado
*/
int parse_query(const char* query_string, ESTADO* e, int* change_turn);


/**
\brief Cria uma hiperligação para uma ação de movimento
@param dx Alteração da posição do jogador na coordenada x
@param dy Alteração da posição do jogador na coordenada y
@param destination Variável que vai guardar a string da hiperligação
*/
void create_move_query(int dx, int dy, char* destination);

/**
\brief Cria uma hiperligação para uma ação de saída de nível
@param destination Variável que vai guardar a string da hiperligação
*/
void create_exit_query(char* destination);

/**
\brief Cria uma hiperligação para uma ação de ataque
@param dx Diferença em x do inimigo que o jogador vai atacar
@param dy Diferença em y do inimigo que o jogador vai atacar
@param destination Variável que vai guardar a string da hiperligação
*/
void create_attack_query(int dx, int dy, char* destination);

/**
\brief Cria uma hiperligação para uma ação de usar uma poção
@param dx Diferença em x da poção que o jogador vai usar
@param dy Diferença em y da poção que o jogador vai usar
@param destination Variável que vai guardar a string da hiperligação
*/
void create_potion_query(int dx, int dy, char* destination);