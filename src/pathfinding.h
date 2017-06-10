/**
  * @file pathfinding.h
  * @brief Definição de estruturas uteis no algoritmo A*
*/

#pragma once
#include "estado.h"

typedef struct node
{
	POSICAO pos;
	//Parents and Stuff
	struct node* parent;

	int f; // sum of g and h
	int g; // cost of moving from starting Node to this node   
	int h; // cost of moving from this node to the End Node, heuristic
	int opened;
	int closed;
	int mb_Walkable; // Is an object or an empty space
} Node;

typedef struct grid
{
	Node nodes[TAM][TAM]; // list of nodes
} Grid;

typedef struct lligada_path
{
	POSICAO pos;
	struct lligada_path* prox;
} LPos, Path;

typedef struct lligada_nodes
{
	Node* node;
	struct lligada_nodes* prox;
} LNode;

typedef struct lligada_nodes_ord
{
	Node* node;
	struct lligada_nodes_ord* prox;
} LNodeOrd;

