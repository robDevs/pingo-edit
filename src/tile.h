#ifndef TILE_
#define TILE_

#include <stdio.h>
#include "raylib.h"
#include <string>


#define FLOOR               0
#define WALL                1
#define STOPTILE            3
#define START               4
#define FLOOR_EMPTY         5
#define CONVEYOR_BLANK      6

#define MAX_INPUT_CHARS     15

extern int curr_tile;

typedef struct {
  Rectangle rect;
  int type;
  bool active;
  float rad;
} Tile;

extern int defWidth;
extern int defHeight;

extern int levelWidth;
extern int levelHeight;

extern Texture floor;
extern Texture wall;
extern Texture start;
extern Texture bg;
extern Texture stopTile;
extern Texture floorEmpty;
extern Texture conveyorBlank;

extern void loadTextures();
extern void unloadTextures();

extern void drawGrid(Tile tile[26][16]);
extern void initGid(Tile tile[26][16]);
extern void drawTiles(Tile tile[26][16]);
extern void updateSize(Tile tile[26][16]);
extern int writeToFile(Tile tile[26][16], char *index, char *lName, char *star2, char *star3, char *path);
extern bool checkName(char *name, int count);

#endif
