#include "map.h"
#include "stdio.h" 
#include "utils.h"
#include "cgi.h"
#include <stdlib.h> // rand()
#include <string.h> // strdup
#include "estado.h"


static const char image_directory[] = "/images/";

#ifdef _WIN32
#define strdup _strdup
#endif

/**
 \brief Sub-directory containg any tile assets
*/
static const char tile_sub_directory[] = "tiles/";

/**
\brief Sub-directory containg any obstacle assets
*/
static const char obstacle_sub_directory[] = "obstacles/";

/**
\brief Sub-directory containg any enemy assets
*/
static const char enemy_sub_directory[] = "enemies/";

#define BLACK_TILESET_FLOOR_NUM_ASSETS 4
#define DUNGEON_TILESET_FLOOR_NUM_ASSETS 6
#define BLACK_TILESET_OBSTACLE_NUM_ASSETS 4


static const char* move_file_names[] =
{
	"left_arrow.png",
	"right_arrow.png",
	"up_arrow.png",
	"down_arrow.png",
};

static const char* move_ids[] = 
{
	"arrow-left",
	"arrow-right",
	"arrow-up",
	"arrow-down",
};

static const char* attack_file_names[] =
{
	"attack_sword.png",
	"attack_sword.png",
	"attack_sword.png",
	"attack_sword.png",
};

static const char* attack_ids[] =
{
	"attack-left",
	"attack-right",
	"attack-up",
	"attack-down",
};

#define TILESET_NUM 3
static const TileSetData tileSets[TILESET_NUM] =
{
	{
		"Black Tileset",
		{
			"big_rock_default2.png",
			"lava_pool.png",
			"fall_pit.png",
			"big_rock2.png",
		},
		BLACK_TILESET_OBSTACLE_NUM_ASSETS,
		{
			"black_stone_floor.png",
			"black_stone_floor.png",
			"black_stone_floor2.png",
			"black_stone_floor_broken.png"
		}, 
		BLACK_TILESET_FLOOR_NUM_ASSETS,
		{
			"werecreature_25.png",
			"werecreature_09.png",
			"werecreature_20.png",
		},
		3
	},

	{
		"Dungeon Tileset",
		{
			"big_rock_default2.png",
			"lava_pool.png",
			"fall_pit.png",
			"big_rock2.png",
		}, 
		BLACK_TILESET_OBSTACLE_NUM_ASSETS,
		{
			"dungeon_floor_normal.png",
			"dungeon_floor_normal.png",
			"dungeon_floor_normal.png",
			"dungeon_floor_normal2.png",
			"dungeon_floor_broken.png",
			"dungeon_floor_broken2.png",
		}, 
		DUNGEON_TILESET_FLOOR_NUM_ASSETS,
		{
			"Char_28.png",
			"Char_59.png",
			"character_02.png",
			"characters-34.png"
		},
		4
	},

	{
		"Dirt Tileset",
		{
			"big_rock4.png",
			"pots.png",
			"isaac_pot.png",
			"isaac_shroom.png",
		},
		4,
		{
			"dirt_floor_normal.png",
			"dirt_floor_normal.png",
			"dirt_floor_normal.png",
			"dirt_floor_broken.png",
			"dirt_floor_broken.png",
			"dirt_floor_broken2.png",
		},
		6,
		{
			"Orc_04.png",
			"Orc_03.png",
			"Ogre_11.png",
			"Orc_13.png",
			"Orc_Bloodrager_02_hi.png",
		},
		5
	},

};

const char* get_images_asset_directory()
{
	return image_directory;
}

const char* get_asset_file_name(CellTypes cell, unsigned char tileOffset, TileSetData tileset)
{
	char full_path[256] = { 0 };
	CellTypes cellType = cell;

	switch (cellType)
	{
	case EMPTY:
		sprintf(full_path, "%s%s", tile_sub_directory, tileset.floor_file_names[tileOffset]);
		return strdup(full_path);
	case OBSTACLE:
		sprintf(full_path, "%s%s", obstacle_sub_directory, tileset.obstacles_file_names[tileOffset]);
		return strdup(full_path);
	case ENEMY:
		sprintf(full_path, "%s%s", enemy_sub_directory, tileset.enemy_file_names[tileOffset]);
		return strdup(full_path);
	default:
		return NULL;
	}
}

char generate_random_tile_offset(TileSets tileset)
{
	TileSetData data = tileSets[tileset];

	return random_number(0, data.number_of_floor_tiles - 1);
}

char generate_random_obstacle_offset(TileSets tileset)
{
	TileSetData data = tileSets[tileset];

	return random_number(0, data.number_of_obstacle_tiles - 1);
}

char generate_random_enemy_offset(TileSets tileset)
{
	TileSetData data = tileSets[tileset];

	return random_number(0, data.number_of_enemy_tiles - 1);
}

CellTypes get_cell_type_at_pos(ESTADO* e, int x, int y)
{
	if (e == NULL)
	{
		return -1;
	}

	int i;
	// Check against enemies coords
	for (i = 0; i < e->num_inimigos; ++i)
	{
		if (e->inimigo[i].pos.x == x && e->inimigo[i].pos.y == y)
			return ENEMY;
	}

	// Check against obstacles coords
	for (i = 0; i < e->num_obstaculos; ++i)
	{
		if (e->obstaculo[i].x == x && e->obstaculo[i].y == y)
			return OBSTACLE;
	}

	// Check against potions coords
	for (i = 0; i < e->num_pocoes; ++i)
	{
		if (e->pocoes[i].x == x && e->pocoes[i].y == y)
			return POTION;
	}

	// Check against exit's coords
	if (x == e->exit.x && y == e->exit.y)
		return PORTAL;

	return EMPTY;
}

TileSetData get_tile_set_data(int level)
{
	TileSets tileset = get_tileset_by_level(level);
	return tileSets[tileset];
}

void draw_tile(ESTADO* e, int x, int y)
{
	const char* base_directory = get_images_asset_directory();
	char offset = e->tile_texture_offset[x][y];
	TileSetData data = get_tile_set_data(e->level);
	const char* asset_file_name = get_asset_file_name(EMPTY, offset, data);
	printf("<image x=%d y=%d width=%d height=%d xlink:href=%s%s />\n", \
		ESCALA * x, ESCALA* y, ESCALA, ESCALA, base_directory, asset_file_name);

	free((void*)asset_file_name);
}

void draw_obstacle(ESTADO* e, int x, int y)
{
	const char* base_directory = get_images_asset_directory();
	char offset = e->obstacle_texture_offset[x][y];
	TileSetData data = get_tile_set_data(e->level);
	const char* asset_file_name = get_asset_file_name(OBSTACLE, offset, data);
	printf("<image x=%d y=%d width=%d height=%d xlink:href=%s%s />\n", \
		ESCALA * x, ESCALA* y, ESCALA, ESCALA, base_directory, asset_file_name);

	free((void*)asset_file_name);
}

void draw_enemy(ESTADO* e, int x, int y, int id)
{
	const char* base_directory = get_images_asset_directory();
	char offset = e->enemy_texture_offset[id];
	TileSetData data = get_tile_set_data(e->level);
	const char* asset_file_name = get_asset_file_name(ENEMY, offset, data);
	printf("<image x=%d y=%d width=%d height=%d xlink:href=%s%s />\n", \
		ESCALA * x, ESCALA* y, ESCALA, ESCALA, base_directory, asset_file_name);

	free((void*)asset_file_name);
}

void create_arrow_link(Orientations orientation, int x, int y, const char* link)
{
	const char* orientation_id = move_ids[orientation];
	printf("<a id=%s xlink:href=%s>\n", orientation_id, link);
	draw_arrow_image(orientation, x, y);
	FECHAR_LINK;
}

void draw_arrow_image(Orientations orientation, int x, int y)
{
	const char* base_directory = get_images_asset_directory();
	const char* asset_file_name = move_file_names[orientation];

	printf("<image x=%d y=%d width=%d height=%d xlink:href=%s%s />\n", \
		ESCALA * x, ESCALA* y, ESCALA, ESCALA, base_directory, asset_file_name);
}

void create_attack_link(Orientations orientation, int x, int y, const char* link)
{
	const char* orientation_id = attack_ids[orientation];
	printf("<a id=%s xlink:href=%s>\n", orientation_id, link);
	draw_attack_image(orientation, x, y);
	FECHAR_LINK;
}

void draw_attack_image(Orientations orientation, int x, int y)
{
	const char* base_directory = get_images_asset_directory();
	const char* asset_file_name = attack_file_names[orientation];

	printf("<image x=%d y=%d width=%d height=%d xlink:href=%s%s />\n", \
		ESCALA * x, ESCALA* y, ESCALA, ESCALA, base_directory, asset_file_name);
}

void create_potion_link(int x, int y, const char* link)
{
	printf("<a class=potion xlink:href=%s>\n", link);
	draw_potion_image(x, y);
	FECHAR_LINK;
}

void draw_potion_image(int x, int y)
{
	const char* base_directory = get_images_asset_directory();
	const char* asset_file_name = POTION_IMAGE_FILE_NAME;

	printf("<image x=%d y=%d width=%d height=%d xlink:href=%s%s />\n", \
		ESCALA * x, ESCALA* y, ESCALA, ESCALA, base_directory, asset_file_name);
}

void update_enemy_array(ESTADO* e, int index)
{
	int max = e->num_inimigos;
	int i;
	for (i = index; i <= max - 2; i++)
	{
		e->inimigo[i] = e->inimigo[i + 1];
	}
	e->num_inimigos--;
}

void update_potion_array(ESTADO* e, int index)
{
	int max = e->num_pocoes;
	int i;
	for (i = index; i <= max - 2; i++)
	{
		e->pocoes[i] = e->pocoes[i + 1];
	}
	e->num_pocoes--;
}

TileSets get_tileset_by_level(int level)
{
	return (TileSets)(level % TILESET_NUM);
}

/*
int load_map(const char* file_name, TMapData* target)
{
	if (target == NULL)
	{
		return -1;
	}


	FILE* f;
	f = fopen(file_name, "r");
	if (f == NULL)
	{
		print_error("Error while loading map %s", file_name);
		return -1;
	}

	return 0;
}
*/