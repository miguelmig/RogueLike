#include "pathfinding.h"
#include "map.h"
#include <stdlib.h>
#include <math.h>
#include <stdio.h>

Path* create_new_path(int x, int y, LPos* prox)
{
	LPos* n = (LPos*)malloc(sizeof(struct lligada_path));
	n->pos.x = x;
	n->pos.y = y;
	n->prox = prox;
	return n;
}

void freePath(Path* path)
{
	while(path != NULL)
	{
		Path* next = path->prox;
		free(path);
		path = next;
	}
}

Path* backtrace(Node* node)
{
	Path* path = create_new_path(node->pos.x, node->pos.y, NULL);
	Path* start = path;

	while (node->parent) 
	{
		path->prox = create_new_path(node->parent->pos.x, node->parent->pos.y, NULL);
		node = node->parent;
		path = path->prox;
	}

	Path* next;
	Path* current = start;
	Path* prev = NULL;
	while(current != NULL)
	{
		next = current->prox;
		current->prox = prev;
		prev = current;
		current = next;
	}

	return prev;
}

int grid_is_inside(int x, int y)
{
	return (x >= 0 && x < TAM) && (y >= 0 && y < TAM);
}

int grid_is_walkable(Grid* grid, int x, int y)
{
	return grid_is_inside(x, y) && grid->nodes[x][y].mb_Walkable;
}

int get_neighbors(Grid* grid, Node current, Node** output)
{
	long x = current.pos.x, y = current.pos.y;
	int count = 0;

	if (grid_is_walkable(grid, x, y - 1)) 
	{
		output[count++] = &grid->nodes[x][y - 1];
	}

	if (grid_is_walkable(grid, x + 1, y)) 
	{
		output[count++] = &grid->nodes[x +1][y];
	}

	if (grid_is_walkable(grid, x, y + 1)) 
	{
		output[count++] = &grid->nodes[x][y + 1];
	}

	if (grid_is_walkable(grid, x - 1, y)) 
	{
		output[count++] = &grid->nodes[x - 1][y];
	}

	return count;
}

LNodeOrd* new_lnode_ord(Node* value, LNodeOrd* next)
{
	LNodeOrd* new = (LNodeOrd*)malloc(sizeof(struct lligada_nodes_ord));

	if (new != NULL) 
	{
		new->node = value;
		new->prox = next;
	}

	return new;
}

void insert_ord(LNodeOrd** l, Node* new_node)
{
	for (; *l != NULL && (*l)->node->f > new_node->f; l = &((*l)->prox));
	*l = new_lnode_ord(new_node, *l);
}

Node* get_top(LNodeOrd* l)
{
	for (; l != NULL && l->prox != NULL; l = l->prox);

	return l->node;
}

void pop(LNodeOrd** l)
{
	for (; *l != NULL && (*l)->prox != NULL; l = &((*l)->prox));
	*l = NULL;
}

void erase(LNodeOrd** l, Node* val)
{
	for (; *l != NULL && (*l)->node != val; l = &((*l)->prox));
	LNodeOrd* next = (*l)->prox;
	free(*l);
	*l = next;
}

void update_walkable_grid(Grid* grid, int** walkable)
{
	int i, j;

	for (i = 0; i < TAM; i++)
	{
		for (j = 0; j < TAM; j++)
		{
			grid->nodes[i][j].mb_Walkable = walkable[i][j];
		}
	}
}

long manhattan(long dx, long dy)
{
	return dx + dy;
}

void freeLNodeOrd(LNodeOrd* openList)
{
	while (openList != NULL)
	{
		LNodeOrd* next = openList->prox;
		free(openList);
		openList = next;
	}
}

void print_path(Path* path)
{
	for (; path != NULL; path = path->prox)
	{
		printf("(%d,%d)\n", path->pos.x, path->pos.y);
	}
}

Path* findPath(long startX, long startY, long endX, long endY, Grid* grid)
{
	LNodeOrd* openList = (LNodeOrd*)malloc(sizeof(LNodeOrd));
	Node* startNode = &grid->nodes[startX][startY];
	Node* endNode = &grid->nodes[endX][endY];
	Node* neighbors[4];

	// set the `g` and `f` value of the start node to be 0
	startNode->g = 0;
	startNode->f = 0;

	// set the open list first element as the start
	openList->node = startNode;
	openList->prox = NULL;
	startNode->opened = 1;

	// while the open list is not empty
	while (openList != NULL) {
		// pop the position of node which has the minimum `f` value.
		Node* node = get_top(openList);
		pop(&openList);
		node->closed = 1;

		// if reached the end position, construct the path and return it
		if (node == endNode) 
		{
			Path* path = backtrace(endNode);
			freeLNodeOrd(openList);
			return path;
		}

		// get neigbours of the current node
		int count = get_neighbors(grid, (*node), neighbors);
		for (int i = 0; i < count; ++i) {
			Node* neighbor = neighbors[i];

			if (neighbor->closed) {
				continue;
			}

			long x = neighbor->pos.x, y = neighbor->pos.y;

			// get the distance between current node and the neighbor
			// and calculate the next g score
			long ng = node->g + 1;

			// check if the neighbor has not been inspected yet, or
			// can be reached with smaller cost from the current node
			if (!neighbor->opened || ng < neighbor->g) {
				if (neighbor->opened)
					erase(&openList, neighbor); // Always erase the value from the set before modyfing it
				neighbor->g = ng;
				int manhattanDistance = manhattan(abs(x - endX), abs(y - endY));
				neighbor->h = manhattanDistance != 0 ? manhattanDistance : 0;
				neighbor->f = neighbor->g + neighbor->h;
				neighbor->parent = node;

				if (!neighbor->opened) 
				{
					insert_ord(&openList, neighbor);
					neighbor->opened = 1;
				}
				else 
				{
					// the neighbor can be reached with smaller cost.
					// Since its f value has been updated, we have to
					// update its position in the open list
					insert_ord(&openList, neighbor);
				}
			}
		}
	}

	// failed to find the path
	return NULL;
}


void fill_matrix_from_estado(ESTADO* e, int for_enemy, int walkableGrid[TAM][TAM])
{
	int i, j;
	for (i = 0; i < TAM; i++)
	{
		for (j = 0; j < TAM; j++)
		{
			if(for_enemy)
				walkableGrid[i][j] = (get_cell_type_at_pos(e, i, j) == EMPTY);
			else
				walkableGrid[i][j] = (get_cell_type_at_pos(e, i, j) != OBSTACLE);
		}
	}
}

Path* find_path(long startX, long startY, long endX, long endY, int walkableGrid[TAM][TAM])
{
	Grid grid;
	int i, j;
	for (i = 0; i < TAM; i++)
	{
		for (j = 0; j < TAM; j++)
		{
			grid.nodes[i][j].pos.x = i;
			grid.nodes[i][j].pos.y = j;
			grid.nodes[i][j].mb_Walkable = walkableGrid[i][j];
			grid.nodes[i][j].parent = NULL;
			grid.nodes[i][j].f = 0;
			grid.nodes[i][j].g = 0;
			grid.nodes[i][j].h = 0;
			grid.nodes[i][j].closed = 0;
			grid.nodes[i][j].opened = 0;
		}
	}

	Path* path = findPath(startX, startY, endX, endY, &grid);
	//print_path(path);
	return path;
}

int exists_path(long startX, long startY, long endX, long endY, int walkableGrid[TAM][TAM])
{
	Path* path = find_path(startX, startY, endX, endY, walkableGrid);
	if (path == NULL)
	{
		return 0;
	}

	free(path);
	return 1;
}