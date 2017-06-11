/**
* @file exemplo.h
* @brief Cont�m o corpo principal do jogo e maior parte das funcionalidades
*/
#pragma once
#include "estado.h"

/**
\brief Verifica se uma certa posi��o est� livre
@param x[in] Coordenada X a verificar
@param y[in] Coordenada Y a verificar
@param e[in] Estado do jogo
@return 1 se estiver livre, 0 sen�o
*/
int posicao_livre(int x, int y, ESTADO* e);

/**
\brief Cria um estado inicial baseado no n�vel indicado
@param level N�vel do estado a ser criado
@return Estado gerado pela fun��o

Esta fun��o gera as posi��es dos inimigos, dos obst�culos e das po��es aleatoriamente.
O n�mero de inimigos � randomizado com base nos #define MIN_ENEMIES e #define MAX_ENEMIES
O n�mero de obst�culos � randomizado com base nos #define MIN_OBSTACLES e #define MAX_OBSTACLES
O n�mero de po��es � randomizado com base no #define MIN_POCOES e o n�vel atual + 1

As texturas dos inimigos, obst�culos e telhas s�o tamb�m randomizadas nesta fun��o
com base no TileSet correspondente ao n�vel atual, obtido atrav�s da fun��o get_tileset_by_level()
*/
ESTADO inicializar(int level);

/**
\brief Verifica se o jogo terminou com a �ltima a��o realizada
@param e Estado que vai ser verificado
@return 1 se o jogo tiver terminado, 0 sen�o

Verifica se a condi��o de fim de jogo foi cumprida, ou seja, se a vida do jogador � menor ou igual a 0
*/
int is_game_over(ESTADO* e);

/**
\brief Procedimento realizado no fim do jogo
@param e Estado que vai ser analisado

Atualiza os highscores caso a pontua��o do jogo atual perten�a l� e imprime a janela de 'Game Over' e recome�a o jogo
*/
void on_game_over(ESTADO* e);

/**
\brief Procedimento em que um inimigo ataca um jogador
@param enemy[in] Inimigo que vai atacar o jogador
@param e[in, out] Estado do jogo atual.
@param damage_done[out] Apontador para uma vari�vel que ir� guardar o dano efetuado pelo inimigo

*/
void atacar_jogador(INIMIGO* enemy, ESTADO* e, int* damage_done);

/**
\brief Procedimento para mover todos os inimigos no tabuleiro e atacar o jogador caso seja poss�vel
@param enemy[in] Inimigo que vai atacar o jogador
@param damage_done[out] Apontador para uma vari�vel que ir� guardar o dano efetuado pelos inimigos

Move os inimigos consoante uma fun��o simples de dist�ncia entre a posi��o do jogador e a posi��o do inimigo
A fun��o analisa todas as poss�veis dire��es que o inimigo se pode mover e escolhe a melhor consoante a dist�ncia Euclideana
entre o novo ponto segundo essa dire��o e a posi��o do jogador.

Caso o inimigo j� esteja numa posi��o capaz de atacar o jogador, ou seja, num + em que o jogador � o centro,
a fun��o atacar_jogador() � chamada e o jogador sofre dano
*/
void mover_inimigos(ESTADO* e, int* damage_done);

/**
\brief L� os highscores presentes no ficheiro #define HIGHSCORES_FILE_NAME e coloca-os em \p highscore_array
@param highscore_array[out] Apontador para uma array que ir� guardar #define HIGHSCORE_SAVE_COUNT n�mero de highscores
@return O n�mero de bytes lidos do ficheiro, 0 significa que houve um erro no procedimento
*/
int ler_highscores(int* highscore_array);

/**
\brief Guarda os highscores no ficheiro #define HIGHSCORES_FILE_NAME 
@param highscore_array[in] Apontador para uma array que cont�m #define HIGHSCORE_SAVE_COUNT n�mero de highscores 
para serem guardados 
*/
void guardar_highscores(int* highscore_array);

/**
\brief Fun��o que obt�m o Estado do ficheiro
@return Devolve o estado obtido

Tenta obter o estado que esteja no ficheiro #define STATE_FILE_NAME usando a fun��o read_state_from_file()
Caso n�o seja poss�vel, a fun��o inicializar() � chamada com \p level igual a 1 e � criado um novo estado
e guardado no ficheiro usando a fun��o output_state_to_file()
*/
ESTADO obter_estado();