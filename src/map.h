/**
  * @file map.h
  * @brief Ficheiro usado para gerar/desenhar/imprimir todo o tipo de acções e imagens relacionadas com a grelha
*/

#pragma once
#include "estado.h"

#define MAX_NAME_LENGTH 32

#define OBSTACLE_TILE_MAX 10
#define FLOOR_TILE_MAX 10
#define ENEMY_TILE_MAX 10
#define FLOOR_TILE_MAX_FILE_NAME_LENGTH 32
#define OBSTACLE_TILE_MAX_FILE_NAME_LENGTH 32
#define ENEMY_TILE_MAX_FILE_NAME_LENGTH 32

/**
  \enum CellTypes
  \brief Enum contendo todos os possíveis objetos/entidades de uma telha
*/
typedef enum
{
	EMPTY,
	OBSTACLE,
	ENEMY,
	PORTAL,
	POTION,
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

/**
  * \struct TileSetData
  * \brief Contém toda a informação necessária sobre um TileSet
*/
typedef struct
{
	/** \brief Nome do TileSet */
	char identifier[MAX_NAME_LENGTH];

	/** \brief Nomes dos ficheiros de todos os obstáculos que podem ser gerados */
	const char obstacles_file_names[OBSTACLE_TILE_MAX][OBSTACLE_TILE_MAX_FILE_NAME_LENGTH]; 
	int number_of_obstacle_tiles;

	/** \brief Nomes dos ficheiros de todas as telhas que podem ser geradas */
	const char floor_file_names[FLOOR_TILE_MAX][FLOOR_TILE_MAX_FILE_NAME_LENGTH];
	int number_of_floor_tiles;

	/** \brief Nomes dos ficheiros de todos os inimigos que podem ser geradas */
	const char enemy_file_names[ENEMY_TILE_MAX][ENEMY_TILE_MAX_FILE_NAME_LENGTH];
	int number_of_enemy_tiles;

} TileSetData;

/**
\brief Função usada para obter o conteúdo de uma telha
@param e Apontador para o estado
@param x Coordenada x para procurar
@param y Coordenada y para procurar
@returns O tipo de objecto/entidade presente nessa telha.
*/
CellTypes get_cell_type_at_pos(ESTADO* e, int x, int y);


char generate_random_tile_offset(TileSets tileset);
char generate_random_obstacle_offset(TileSets tileset);
char generate_random_enemy_offset(TileSets tileset);
void draw_tile(ESTADO* e, int x, int y);
void draw_obstacle(ESTADO* e, int x, int y);
void draw_enemy(ESTADO* e, int x, int y, int id);

void create_arrow_link(Orientations orientation, int x, int y, const char* link);
void draw_arrow_image(Orientations orientation, int x, int y);
void create_attack_link(Orientations orientation, int x, int y, const char* link);
void draw_attack_image(Orientations orientation, int x, int y);

void create_potion_link(int x, int y, const char* link);
void draw_potion_image(int x, int y);
void update_enemy_array(ESTADO* e, int index);
void update_potion_array(ESTADO* e, int index);

const char* get_images_asset_directory();

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