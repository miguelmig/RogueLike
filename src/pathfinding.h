/**
  * @file pathfinding.h
  * @brief Definição de estruturas uteis no algoritmo A*
*/

#pragma once
#include "estado.h"

/**
\private
\brief Representa cada telha do tabuleiro com informação relevante ao algoritmo de procura
*/
typedef struct node
{
	/** Node coordinates */
	POSICAO pos;

	/** Parent Node */
	struct node* parent;

	int f; // sum of g and h
	int g; // cost of moving from starting Node to this node   
	int h; // cost of moving from this node to the End Node, heuristic
	int opened;
	int closed;
	int mb_Walkable; // Is an object or an empty space
} Node;

/**
\private
\brief Estrutura que contém uma matriz de dimensão TAM x TAM
*/
typedef struct grid
{
	Node nodes[TAM][TAM]; // list of nodes
} Grid;

typedef struct lligada_path
{
	POSICAO pos;
	struct lligada_path* prox;
} LPos, Path;

/**
\private
\brief Lista ligada de apontadores para Nodes
Lista ligada ordenada por valores 'f' de cada Node.
O node com menor valor 'f' está no fim da lista ligada
*/
typedef struct lligada_nodes_ord
{
	Node* node;
	struct lligada_nodes_ord* prox;
} LNodeOrd;

/**
\brief Obtém um caminho entre 2 pontos no tabuleiro usando o algoritmo A*
@param startX[in] Coordenada X do ponto de origem
@param startY[in] Coordenada Y do ponto de origem
@param endX[in] Coordenada X do ponto de destinação
@param endY[in] Coordenada Y do ponto de destinação
@param walkableGrid[in] Caso especial para geração de mapa

@return Lista ligada de posições que constituem o caminho da origem à destinação, ou caso não exista caminho
devolve NULL

O algoritmo analisa as casas alheias à atual e vai vendo qual é a casa cuja distância à destinação é menor
e vai avançando até encontrar um caminho
Mais detalhes em: https://en.wikipedia.org/wiki/A*_search_algorithm
*/
Path* find_path(long startX, long startY, long endX, long endY, int walkableGrid[TAM][TAM]);

/**
\brief Preenche uma matriz de dimensão TAM x TAM com a capacidade de andar em cada telha
@param e[in] Estado para obter capacidade de andar em cada telha
@param for_enemy[in] Se a matriz for destinada a movimentos para inimigos, é preciso verificar contra poções e outros objetos
@param walkableGrid[out] Matriz resultado, 1 significa que o jogador pode andar na telha, 0 não
*/
void fill_matrix_from_estado(ESTADO* e, int for_enemy, int walkableGrid[TAM][TAM]);


/**
\brief Verifica se existe um caminho entre 2 pontos no tabuleiro
@param startX[in] Coordenada X do ponto de origem
@param startY[in] Coordenada Y do ponto de origem
@param endX[in] Coordenada X do ponto de destinação
@param endY[in] Coordenada Y do ponto de destinação
@param walkableGrid[in] Caso especial para geração de mapa
@return 1 se existir caminho, 0 senão
*/
int exists_path(long startX, long startY, long endX, long endY, int walkableGrid[TAM][TAM]);

/**
\brief Liberta a memória usada por um Path
*/
void freePath(Path* path);