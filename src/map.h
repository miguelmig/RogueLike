#pragma once
#include "estado.h"

typedef enum
{
	EMPTY,
	OBSTACLE,
	ENEMY,
	PLAYER_SPAWN_POINT,
	PORTAL
} CellTypes;

typedef enum
{
	LEFT,
	RIGHT,
	UP,
	DOWN
} Orientations;

CellTypes getCellTypeAtPosition(ESTADO* e, int x, int y);
char generateRandomTileOffset();
char generateRandomObstacleOffset();
void draw_tile(ESTADO* e, int x, int y);
void draw_obstacle(ESTADO* e, int x, int y);
void drawArrow(Orientations orientation, int x, int y);

const char* getImagesAssetDirectory();

/*
typedef struct
{
	short map_index;
	char map_name[MAP_NAME_MAX];
	int width;
	int height;
	void* cells;
} TMapData;
*/


//int load_map(const char* file_name, TMapData* target);