/**
* @file exemplo.h
* @brief Contém o corpo principal do jogo e maior parte das funcionalidades
*/
#pragma once
#include "estado.h"

/**
\brief Verifica se uma certa posição está livre
@param x[in] Coordenada X a verificar
@param y[in] Coordenada Y a verificar
@param e[in] Estado do jogo
@return 1 se estiver livre, 0 senão
*/
int posicao_livre(int x, int y, ESTADO* e);

/**
\brief Cria um estado inicial baseado no nível indicado
@param level Nível do estado a ser criado
@return Estado gerado pela função

Esta função gera as posições dos inimigos, dos obstáculos e das poções aleatoriamente.
O número de inimigos é randomizado com base nos #define MIN_ENEMIES e #define MAX_ENEMIES
O número de obstáculos é randomizado com base nos #define MIN_OBSTACLES e #define MAX_OBSTACLES
O número de poções é randomizado com base no #define MIN_POCOES e o nível atual + 1

As texturas dos inimigos, obstáculos e telhas são também randomizadas nesta função
com base no TileSet correspondente ao nível atual, obtido através da função get_tileset_by_level()
*/
ESTADO inicializar(int level);

/**
\brief Verifica se o jogo terminou com a última ação realizada
@param e Estado que vai ser verificado
@return 1 se o jogo tiver terminado, 0 senão

Verifica se a condição de fim de jogo foi cumprida, ou seja, se a vida do jogador é menor ou igual a 0
*/
int is_game_over(ESTADO* e);

/**
\brief Procedimento realizado no fim do jogo
@param e Estado que vai ser analisado

Atualiza os highscores caso a pontuação do jogo atual pertença lá e imprime a janela de 'Game Over' e recomeça o jogo
*/
void on_game_over(ESTADO* e);

/**
\brief Procedimento em que um inimigo ataca um jogador
@param enemy[in] Inimigo que vai atacar o jogador
@param e[in, out] Estado do jogo atual.
@param damage_done[out] Apontador para uma variável que irá guardar o dano efetuado pelo inimigo

*/
void atacar_jogador(INIMIGO* enemy, ESTADO* e, int* damage_done);

/**
\brief Procedimento para mover todos os inimigos no tabuleiro e atacar o jogador caso seja possível
@param enemy[in] Inimigo que vai atacar o jogador
@param damage_done[out] Apontador para uma variável que irá guardar o dano efetuado pelos inimigos

Move os inimigos consoante uma função simples de distância entre a posição do jogador e a posição do inimigo
A função analisa todas as possíveis direções que o inimigo se pode mover e escolhe a melhor consoante a distância Euclideana
entre o novo ponto segundo essa direção e a posição do jogador.

Caso o inimigo já esteja numa posição capaz de atacar o jogador, ou seja, num + em que o jogador é o centro,
a função atacar_jogador() é chamada e o jogador sofre dano
*/
void mover_inimigos(ESTADO* e, int* damage_done);

/**
\brief Lê os highscores presentes no ficheiro #define HIGHSCORES_FILE_NAME e coloca-os em \p highscore_array
@param highscore_array[out] Apontador para uma array que irá guardar #define HIGHSCORE_SAVE_COUNT número de highscores
@return O número de bytes lidos do ficheiro, 0 significa que houve um erro no procedimento
*/
int ler_highscores(int* highscore_array);

/**
\brief Guarda os highscores no ficheiro #define HIGHSCORES_FILE_NAME 
@param highscore_array[in] Apontador para uma array que contém #define HIGHSCORE_SAVE_COUNT número de highscores 
para serem guardados 
*/
void guardar_highscores(int* highscore_array);

/**
\brief Função que obtém o Estado do ficheiro
@return Devolve o estado obtido

Tenta obter o estado que esteja no ficheiro #define STATE_FILE_NAME usando a função read_state_from_file()
Caso não seja possível, a função inicializar() é chamada com \p level igual a 1 e é criado um novo estado
e guardado no ficheiro usando a função output_state_to_file()
*/
ESTADO obter_estado();