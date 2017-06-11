#pragma once
#include "estado.h"

/**
\brief Interpreta a string passada e movimenta o jogador de acordo com os parametros presentes na string
@param move_query_string[in] String retirada da QUERY_STRING que vai ser interpretada
@param e[in, out] Estado que vai ser alterado consoante o movimento interpretado
@return 1 se o estado foi alterado, 0 se não foi alterado

A função obtém as direções em x e y que o jogador se pretende movimentar usando sscanf()
e o formato especifico do movimento "x=%d&y=%d" e verifica se os valores passados são válidos
e caso sejam, move o jogador de acordo com esse mesmo x e y
*/
int parse_move_action(const char* move_query_string, ESTADO* e);

/**
\brief Interpreta a string passada e avança o jogo para um novo nível
@param exit_query_string[in] String retirada da QUERY_STRING que vai ser interpretada
@param e[in, out] Estado que vai ser alterado consoante os paramêtros 
@return 1 se o estado foi alterado, 0 se não foi alterado

A função obtém as coordenadas para onde o jogador será teleportado no novo nível usando sscanf()
e o formato "x=%d&y=%" e coloca o jogador nessa posição
O jogador é também recompensado com um bónus de pontos equivalente a #define NEW_LEVEL_SCORE_BONUS
E recupera pontos de vida equivalente a metade de #define PLAYER_MAX_HEALTH
*/
int parse_exit_action(const char* exit_query_string, ESTADO* e);

/**
\brief Interpreta a string passada e ataca um inimigo
@param attack_query_string[in] String retirada da QUERY_STRING que vai ser interpretada
@param e[in, out] Estado que vai ser alterado consoante os paramêtros
@return 1 se o estado foi alterado, 0 se não foi alterado

A função obtém as direções x e y que o jogador pretende atacar usando sscanf()
e o formato "x=%d&y=%" e tenta encontrar se existe um inimigo nessas coordenadas
Caso exista, o inimigo é eliminado e o jogador é também recompensado 
com um bónus de pontos equivalente a #define KILL_SCORE_BONUS
*/
int parse_attack_action(const char* attack_query_string, ESTADO* e);

/**
\brief Interpreta a string passada e ataca um inimigo
@param attack_query_string[in] String retirada da QUERY_STRING que vai ser interpretada
@param e[in, out] Estado que vai ser alterado consoante os paramêtros
@return 1 se o estado foi alterado, 0 se não foi alterado

A função obtém as direções x e y que o jogador pretende atacar usando sscanf()
e o formato "x=%d&y=%" e tenta encontrar se existe um inimigo nessas coordenadas
Caso exista, o inimigo é eliminado e o jogador é também recompensado
com um bónus de pontos equivalente a #define KILL_SCORE_BONUS
*/
int parse_potion_action(const char* potion_query_string, ESTADO* e);

/**
 \brief Lê os argumentos passados pela QUERY_STRING e interpreta corretamente
 @param query_string[in] string passada pelo url depois do '?' contendo a ação para ser realizada
 @param e[in, out] Estado que vai ser alterado conforme a ação a ser executada
 @param change_turn[out] Variável que vai guardar se a ação implica mudança de turno
 @return 1 se o estado foi alterado, 0 se não foi alterado
*/
int parse_query(const char* query_string, ESTADO* e, int* change_turn);

/**
\brief Cria uma hiperligação para uma ação de movimento
@param dx[in] Alteração da posição do jogador na coordenada x
@param dy[in] Alteração da posição do jogador na coordenada y
@param destination[out] Variável que vai guardar a string da hiperligação
*/
void create_move_query(int dx, int dy, char* destination);

/**
\brief Cria uma hiperligação para uma ação de saída de nível
@param destination[out] Variável que vai guardar a string da hiperligação
*/
void create_exit_query(char* destination);

/**
\brief Cria uma hiperligação para uma ação de ataque
@param dx[in] Diferença em x do inimigo que o jogador vai atacar
@param dy[in] Diferença em y do inimigo que o jogador vai atacar
@param destination[out] Variável que vai guardar a string da hiperligação
*/
void create_attack_query(int dx, int dy, char* destination);

/**
\brief Cria uma hiperligação para uma ação de usar uma poção
@param dx[in] Diferença em x da poção que o jogador vai usar
@param dy[in] Diferença em y da poção que o jogador vai usar
@param destination[out] Variável que vai guardar a string da hiperligação
*/
void create_potion_query(int dx, int dy, char* destination);


