#include "map.h"
#include "stdio.h" 
#include "utils.h"
#include "cgi.h"
#include <stdlib.h> // rand()
#include <string.h> // strdup
#include "estado.h"

static const char imageDirectory[] = "http://localhost/images/";

/**
 \brief Sub-directory containg any tile assets
*/
static const char tileSubDirectory[] = "tiles/";

/**
\brief Sub-directory containg any tile assets
*/
static const char obstacleSubDirectory[] = "obstacles/";

static const char* assetFileNames[] =
{
	// Empty,
	"floor3.png",
	// Obstacle
	"wall1.png",

};

#define TILE_NUM_ASSETS 3
static const char* tileFileNames[TILE_NUM_ASSETS] =
{
	/*
	"dungeon_floor_normal.png",
	"dungeon_floor_normal2.png",
	"dungeon_floor_broken.png",
	"dungeon_floor_broken2.png",

	*/
	
	
	"black_stone_floor.png",
	"black_stone_floor2.png",
	"black_stone_floor_broken.png"
	
};

#define OBSTACLE_NUM_ASSETS 4
static const char* obstacleFileNames[OBSTACLE_NUM_ASSETS] =
{
	"big_rock_default2.png",
	"lava_pool.png",
	"fall_pit.png",
	"big_rock2.png",
};


static const char* orientationFileNames[] =
{
	"left_arrow.png",
	"right_arrow.png",
	"up_arrow.png",
	"down_arrow.png",
};

static const char* orientationIds[] = 
{
	"arrow-left",
	"arrow-right",
	"arrow-up",
	"arrow-down",
};

const char* getImagesAssetDirectory()
{
	return imageDirectory;
}

const char* getAssetFileName(CellTypes cell, unsigned char tileOffset)
{
	char full_path[256] = { 0 };
	CellTypes cellType = cell;

	switch (cellType)
	{
	case EMPTY:
		sprintf(full_path, "%s%s", tileSubDirectory, tileFileNames[tileOffset]);
		return strdup(full_path);
	case OBSTACLE:
		sprintf(full_path, "%s%s", obstacleSubDirectory, obstacleFileNames[tileOffset]);
		return strdup(full_path);
	default:
		return strdup(assetFileNames[cellType]);
	}
}

char generateRandomTileOffset()
{
	return random_number(0, TILE_NUM_ASSETS - 1);
}

char generateRandomObstacleOffset()
{
	return random_number(0, OBSTACLE_NUM_ASSETS - 1);
}

CellTypes getCellTypeAtPosition(ESTADO* e, int x, int y)
{
	if (e == NULL)
	{
		return -1;
	}

	int i;
	// Check against enemies coords
	for (i = 0; i < e->num_inimigos; ++i)
	{
		if (e->inimigo[i].x == x && e->inimigo[i].y == y)
			return ENEMY;
	}

	// Check against obstacles coords
	for (i = 0; i < e->num_obstaculos; ++i)
	{
		if (e->obstaculo[i].x == x && e->obstaculo[i].y == y)
			return OBSTACLE;
	}

	// Check against exit's coords
	if (x == e->exit.x && y == e->exit.y)
		return PORTAL;

	return EMPTY;
}

void draw_tile(ESTADO* e, int x, int y)
{
	const char* base_directory = getImagesAssetDirectory();
	char offset = e->tileTextureOffset[x][y];
	const char* asset_file_name = getAssetFileName(EMPTY, offset);
	printf("<image x=%d y=%d width=%d height=%d xlink:href=%s%s />\n", \
		ESCALA * x, ESCALA* y, ESCALA, ESCALA, base_directory, asset_file_name);

	free((void*)asset_file_name);
}

void draw_obstacle(ESTADO* e, int x, int y)
{
	const char* base_directory = getImagesAssetDirectory();
	char offset = e->obstacleTextureOffset[x][y];
	const char* asset_file_name = getAssetFileName(OBSTACLE, offset);
	printf("<image x=%d y=%d width=%d height=%d xlink:href=%s%s />\n", \
		ESCALA * x, ESCALA* y, ESCALA, ESCALA, base_directory, asset_file_name);

	free((void*)asset_file_name);
}


void createArrowLink(Orientations orientation, int x, int y, const char* link)
{
	const char* orientation_id = orientationIds[orientation];
	printf("<a id=%s xlink:href=%s>\n", orientation_id, link);
	drawArrow(orientation, x, y);
	printf("</a>\n");
}

void drawArrow(Orientations orientation, int x, int y)
{
	const char* base_directory = getImagesAssetDirectory();
	const char* asset_file_name = orientationFileNames[orientation];

	printf("<image x=%d y=%d width=%d height=%d xlink:href=%s%s />\n", \
		ESCALA * x, ESCALA* y, ESCALA, ESCALA, base_directory, asset_file_name);
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