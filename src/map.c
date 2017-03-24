#include "map.h"
#include "stdio.h" 
#include "utils.h"
#include "cgi.h"
#include <stdlib.h> // rand()
#include <string.h> // strdup

#define ESCALA 40

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
	"dungeon_floor_normal.png",
	"dungeon_floor_broken.png",
	"dungeon_floor_broken2.png",
};

#define OBSTACLE_NUM_ASSETS 2
static const char* obstacleFileNames[OBSTACLE_NUM_ASSETS] =
{
	"trashcan.png",
	"pots.png",
};


static const char* orientationFileNames[] =
{
	"left_arrow.png",
	"right_arrow.png",
	"up_arrow.png",
	"down_arrow.png",
};

const char* getImagesAssetDirectory()
{
	return imageDirectory;
}

const char* getAssetFileName(CellTypes cellType)
{
	char full_path[256] = { 0 };

	switch (cellType)
	{
	case EMPTY:
		sprintf(full_path, "%s%s", tileSubDirectory, tileFileNames[rand() % TILE_NUM_ASSETS]);
		return _strdup(full_path);
	case OBSTACLE:
		sprintf(full_path, "%s%s", obstacleSubDirectory, obstacleFileNames[rand() % OBSTACLE_NUM_ASSETS]);
		return _strdup(full_path);
	default:
		return _strdup(assetFileNames[cellType]);
	}
}


void drawCell(CellTypes cell_type, int x, int y)
{
	const char* base_directory = getImagesAssetDirectory();
	const char* asset_file_name = getAssetFileName(cell_type);
	printf("<image x=%d y=%d width=%d height=%d xlink:href=%s%s />\n", \
		ESCALA * x, ESCALA* y, ESCALA, ESCALA, base_directory, asset_file_name);

	free(asset_file_name);
}

void drawArrow(Orientations orientation, int x, int y)
{
	const char* base_directory = getImagesAssetDirectory();
	const char* asset_file_name = orientationFileNames[orientation];

	printf("<image x=%d y=%d width=%d height=%d xlink:href=%s%s />\n", \
		ESCALA * x, ESCALA* y, ESCALA, ESCALA, base_directory, asset_file_name);
}

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