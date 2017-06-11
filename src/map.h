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
  * \brief Contém toda a informação necessária sobre um TileSet

  * Esta estrutura é usada para gerar aleatoriamente todo o tipo de texturas
  * desde telhas, obstáculos e inimigos
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

/**
\brief Função usada para gerar um indice aleatório para a textura das telhas
@param tileset O TileSet que contém a informação necessária para saber até que indice se pode gerar
@returns O indice da textura da telha que vai ser usada

Esta função gera um número aleatório entre 0 e o número de texturas de telhas do \p tileset
*/
char generate_random_tile_offset(TileSets tileset);

/**
\brief Função usada para gerar um indice aleatório para a textura das telhas
@param tileset O TileSet que contém a informação necessária para saber até que indice se pode gerar
@returns O indice da textura do obstáculo que vai ser usada

Esta função gera um número aleatório entre 0 e o número de texturas de obstáculos do \p tileset
*/
char generate_random_obstacle_offset(TileSets tileset);

/**
\brief Função usada para gerar um indice aleatório para a textura dos inimigos
@param tileset O TileSet que contém a informação necessária para saber até que indice se pode gerar
@returns O indice da textura de inimigo que vai ser usada

Esta função gera um número aleatório entre 0 e o número de texturas de inimigos do \p tileset
*/
char generate_random_enemy_offset(TileSets tileset);


/**
\brief Desenha uma telha, parte gráfica unicamente
@param e O Estado do jogo 
@param x Coordenada X da telha que vai ser desenhada
@param y Coordenada Y da telha que vai ser desenhada

Desenha uma telha, usando o ESTADO#level na função get_tile_set_data() 
para obter o #TileSet onde se pode utilizar o ESTADO#tile_texture_offset para obter a textura correta
*/
void draw_tile(ESTADO* e, int x, int y);

/**
\brief Desenha um obstáculo, parte gráfica unicamente
@param e O Estado do jogo
@param x Coordenada X do obstáculo que vai ser desenhado
@param y Coordenada Y do obstáculo que vai ser desenhado

Desenha um obstáculo, usando o ESTADO#level na função get_tile_set_data()
para obter o #TileSet onde se pode utilizar o ESTADO#obstacle_texture_offset para obter a textura correta
*/
void draw_obstacle(ESTADO* e, int x, int y);

/**
\brief Desenha um inimigo, parte gráfica unicamente
@param e O Estado do jogo
@param x Coordenada X do obstáculo que vai ser desenhado
@param y Coordenada Y do obstáculo que vai ser desenhado
@param id Identificador do inimigo que vai ser desenhada. Isto é necessário para identificar o inimigo no array

Desenha um inimigo, usando o ESTADO#level na função get_tile_set_data()
para obter o #TileSet onde se pode utilizar o ESTADO#enemy_texture_offset passando o \p id para obter a textura correta
*/
void draw_enemy(ESTADO* e, int x, int y, int id);

/**
\brief Cria a hiperligação para o jogador se movimentar, desenhando também a componente gráfica
@param orientation Orientação do movimento
@param x Coordenada X onde vai ser desenhada a textura da seta
@param y Coordenada Y onde vai ser desenhada a textura da seta
@param link Link da ação a ser executada quando o jogador clicar na textura da seta

Cria a hiperligação de movimento através da tag \i <a> e desenha a parte gráfica da seta na função draw_arrow_image()
*/
void create_arrow_link(Orientations orientation, int x, int y, const char* link);

/**
\brief Desenha a textura da seta de movimento
@param orientation Orientação do movimento
@param x Coordenada X onde vai ser desenhada a textura da seta
@param y Coordenada Y onde vai ser desenhada a textura da seta

Desenha a seta no ecrã tendo em conta a \p orientation que vai ser usada como indice na array #move_file_names
*/
void draw_arrow_image(Orientations orientation, int x, int y);

/**
\brief Cria a hiperligação para o jogador atacar um inimigo, desenhando também a componente gráfica
@param orientation Orientação do ataque
@param x Coordenada X onde vai ser desenhada a textura de ataque
@param y Coordenada Y onde vai ser desenhada a textura de ataque
@param link Link da ação a ser executada quando o jogador clicar na textura de ataque

Cria a hiperligação de ataque através da tag \i <a> e desenha a parte gráfica de ataque na função draw_attack_image()
*/
void create_attack_link(Orientations orientation, int x, int y, const char* link);

/**
\brief Desenha a textura do ataque
@param orientation Orientação do movimento
@param x Coordenada X onde vai ser desenhada a textura de ataque
@param y Coordenada Y onde vai ser desenhada a textura de ataque

Desenha o ataque no ecrã tendo em conta a \p orientation que vai ser usada como indice na array #attack_file_names
*/
void draw_attack_image(Orientations orientation, int x, int y);

/**
\brief Cria a hiperligação para o jogador usar uma poção, desenhando também a componente gráfica
@param x Coordenada X onde vai ser desenhada a textura da poção
@param y Coordenada Y onde vai ser desenhada a textura da poção
@param link Link da ação a ser executada quando o jogador clicar na textura da poção

Cria a hiperligação do uso da poção através da tag \i <a> e desenha a parte gráfica da poção na função draw_potion_image()
*/
void create_potion_link(int x, int y, const char* link);

/**
\brief Desenha a textura da poção
@param x Coordenada X onde vai ser desenhada a textura da poção
@param y Coordenada Y onde vai ser desenhada a textura da poção

Desenha a poção com o nome de ficheiro do #define POTION_IMAGE_FILE_NAME
*/
void draw_potion_image(int x, int y);

/**
\brief Remove um inimigo do array ESTADO#inimigo no indice \p index
@param e Estado do jogo que vai ser alterado
@param index Indice do inimigo a ser eliminado
*/
void update_enemy_array(ESTADO* e, int index);

/**
\brief Remove uma poção do array ESTADO#pocoes no indice \p index
@param e Estado do jogo que vai ser alterado
@param index Indice da poção a ser retirada
*/
void update_potion_array(ESTADO* e, int index);


const char* get_images_asset_directory();

/**
\brief Devolve o TileSet consoante o nível de jogo atual
@param level nível a ser usado para obter o TileSets
@returns O TileSet correspondente ao \p level
*/
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