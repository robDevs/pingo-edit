#ifndef TILE_
#define TILE_

#include <stdio.h>
#include "raylib.h"
#include <string>


#define FLOOR   0
#define WALL    1
#define START   3
#define MAX_INPUT_CHARS     15

typedef struct {
  Rectangle rect;
  int type;
  bool active;
} Tile;

extern int defWidth;
extern int defHeight;

extern int levelWidth;
extern int levelHeight;

extern Texture floor;
extern Texture wall;
extern Texture start;
extern Texture bg;

extern void loadTextures();
extern void unloadTextures();

extern void drawGrid(Tile tile[26][16]);
extern void initGid(Tile tile[26][16]);
extern void drawTiles(Tile tile[26][16]);
extern void updateSize(Tile tile[26][16]);
extern int writeToFile(Tile tile[26][16], char *index, char *lName, char *star2, char *star3, char *path);
extern bool checkName(char *name, int count);

#endif
