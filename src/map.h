#pragma once
#include "estado.h"

#define MAX_NAME_LENGTH 32

#define OBSTACLE_TILE_MAX 10
#define FLOOR_TILE_MAX 10
#define FLOOR_TILE_MAX_FILE_NAME_LENGTH 32
#define OBSTACLE_TILE_MAX_FILE_NAME_LENGTH 32
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
	BLACK = 0,
	DUNGEON,
	DIRT
} TileSets;

typedef enum
{
	LEFT,
	RIGHT,
	UP,
	DOWN
} Orientations;

typedef struct
{
	char identifier[MAX_NAME_LENGTH];
	const char obstacles_file_names[OBSTACLE_TILE_MAX][OBSTACLE_TILE_MAX_FILE_NAME_LENGTH];
	int number_of_obstacle_tiles;
	const char floor_file_names[FLOOR_TILE_MAX][FLOOR_TILE_MAX_FILE_NAME_LENGTH];
	int number_of_floor_tiles;
} TileSetData;


CellTypes getCellTypeAtPosition(ESTADO* e, int x, int y);
char generateRandomTileOffset(TileSets tileset);
char generateRandomObstacleOffset(TileSets tileset);
void draw_tile(ESTADO* e, int x, int y);
void draw_obstacle(ESTADO* e, int x, int y);
void createArrowLink(Orientations orientation, int x, int y, const char* link);
void drawArrow(Orientations orientation, int x, int y);
void create_attack_link(Orientations orientation, int x, int y, const char* link);
void draw_attack_image(Orientations orientation, int x, int y);
void onKillEnemy(ESTADO* e, int index);

const char* getImagesAssetDirectory();

TileSets get_tileset_by_level(int level);

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