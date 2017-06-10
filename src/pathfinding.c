#include "pathfinding.h"
#include <stdlib.h>

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
		Path* next = path = path->prox;
		free(path);
		path = next;
	}
}

Path* backtrace(Node* node)
{
	Path* path = create_new_path(node->pos.x, node->pos.y, NULL);
	Path* start = path;
	// std::vector < std::pair<long, long>> path = { { node->m_lX, node->m_lY } };

	while (node->parent) 
	{
		path->prox = create_new_path(node->parent->pos.x, node->parent->pos.y, NULL);
		node = node->parent;
		path = path->prox;
		//path.push_back({ node->m_lX, node->m_lY });
	}

	return start;
}

int grid_is_inside(Grid* grid, int x, int y)
{
	return (x >= 0 && x < 10) && (y >= 0 && y < 10);
}

int grid_is_walkable(Grid* grid, int x, int y)
{
	return grid_is_inside(grid, x, y) && grid->nodes[y][x].mb_Walkable;
}

int get_neighbors(Grid* grid, Node current, Node** output)
{
	long x = current.pos.x, y = current.pos.y;
	int count = 0;

	// ?
	if (grid_is_walkable(grid, x, y - 1)) {
		output[count++] = &grid->nodes[x][y - 1];
	}

	// ?
	if (grid_is_walkable(grid, x + 1, y)) {
		output[count++] = &grid->nodes[x +1][y];
	}

	// ?
	if (grid_is_walkable(grid, x, y + 1)) {
		output[count++] = &grid->nodes[x][y + 1];
	}

	// ?
	if (grid_is_walkable(grid, x - 1, y)) {
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
	for (; *l != NULL && (*l)->node->f < new_node->f; l = &((*l)->prox));
	*l = new_lnode_ord(new_node, *l);
}

Node* get_top(LNodeOrd** l)
{
	for (; *l != NULL && (*l)->prox != NULL; l = &((*l)->prox));

	return (*l)->node;
}

void pop(LNodeOrd** l)
{
	for (; *l != NULL && (*l)->prox != NULL; l = &((*l)->prox));
	*l = NULL;
}
/*
Path* findPath(long startX, long startY, long endX, long endY, Grid* grid)
{
	LNodeOrd* openList = (LNodeOrd*)malloc(sizeof(struct lligada_nodes_ord));

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
		Node* node = openList.top();
		openList.pop();
		node->closed = 1;

		// if reached the end position, construct the path and return it
		if (node == endNode) {
			return backtrace(&endNode);
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
			long ng = node->g + ((x - node->pos.x == 0 || y - node->pos.y == 0) ? 1 : sqrt(2));

			// check if the neighbor has not been inspected yet, or
			// can be reached with smaller cost from the current node
			if (!neighbor->opened || ng < neighbor->g) {
				if (neighbor->opened)
					openList.erase(&neighbor); // Always erase the value from the set before modyfing it
				neighbor->g = ng;
				int manhattanDistance = manhattan(abs(x - endX), abs(y - endY));
				neighbor->h = manhattanDistance != 0 ? manhattanDistance : 0;
				neighbor->f = neighbor->g + neighbor->h;
				neighbor->parent = node;

				if (!neighbor->opened) 
				{
					openList.push(&neighbor);
					neighbor->opened = 1;
				}
				else 
				{
					// the neighbor can be reached with smaller cost.
					// Since its f value has been updated, we have to
					// update its position in the open list
					openList.push(&neighbor);
				}
			}
		} // end for each neighbor
	} // end while not open list empty

	  // fail to find the path
	return{};
}
*/

