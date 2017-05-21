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

void create_move_query(int dx, int dy, char* destination);
void create_exit_query(char* destination);
void create_attack_query(int dx, int dy, char* destination);
void create_potion_query(int dx, int dy, char* destination);