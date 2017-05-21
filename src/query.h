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

void create_move_query(int dx, int dy, char* destination);
void create_exit_query(char* destination);
void create_attack_query(int dx, int dy, char* destination);
void create_potion_query(int dx, int dy, char* destination);