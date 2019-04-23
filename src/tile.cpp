#include "tile.h"

int defWidth = 936;
int defHeight = 544;

int levelWidth = 26;
int levelHeight = 16;

Texture floor;
Texture wall;
Texture start;
Texture bg;

void loadTextures() {
    Image tempImage;
    
    tempImage = LoadImage("assets/floorBlank.png");
    ImageResizeNN(&tempImage, 36, 34);
    floor = LoadTextureFromImage(tempImage);
    UnloadImage(tempImage);

    tempImage = LoadImage("assets/wall.png");
    ImageResizeNN(&tempImage, 36, 34);
    wall = LoadTextureFromImage(tempImage);
    UnloadImage(tempImage);

    tempImage = LoadImage("assets/ball.png");
    ImageResizeNN(&tempImage, 36, 34);
    start = LoadTextureFromImage(tempImage);
    UnloadImage(tempImage);

    tempImage = LoadImage("assets/background1.png");
    ImageResizeNN(&tempImage, 156, 136);
    bg = LoadTextureFromImage(tempImage);
    UnloadImage(tempImage);
}

void unloadTextures() {
    UnloadTexture(floor);
    UnloadTexture(wall);
    UnloadTexture(start);
    UnloadTexture(bg);
}

void drawGrid(Tile tile[26][16]) {
    for(int i = 0; i < 26; i++)
        for(int x = 0; x < 16; x++) {
            if(tile[i][x].active) {
                DrawRectangleLinesEx(tile[i][x].rect, 1, LIGHTGRAY);
            }
        }
}

void initGid(Tile tile[26][16]) {
  for(int i = 0; i < 26; i++)
    for(int x = 0; x < 16; x++){
      tile[i][x].rect.x = i * 36 + 12;
      tile[i][x].rect.y = x * 34;
      tile[i][x].rect.width = 36;
      tile[i][x].rect.height = 34;
      tile[i][x].type = WALL;
      tile[i][x].active = true;
    }
}

void updateSize(Tile tile[26][16]) {
    int newWidth = defWidth / levelWidth;
    int newHeight = defHeight / levelHeight;

    for(int i = 0; i < 26; i++) {
        for(int x = 0; x < 16; x++) {


            if(i >= levelWidth || x >= levelHeight)
                tile[i][x].active = false;
            else
                tile[i][x].active = true;
        }
    }
}

void drawTiles(Tile tile[26][16]) {
  for(int i = 0; i < 6; i++) {
      for(int x = 0; x < 4; x++) {
          DrawTexture(bg, i * 156 + 12, x * 136, WHITE);
      }
  }

  for(int i = 0; i < 26; i++)
    for(int x = 0; x < 16; x++) {
      if(tile[i][x].active) {
          switch (tile[i][x].type) {
            case FLOOR:
              DrawTexture(floor, tile[i][x].rect.x, tile[i][x].rect.y, WHITE);
              //DrawRectangleRec(tile[i][x].rect, BLACK);
              break;
            case WALL:
              DrawTexture(wall, tile[i][x].rect.x, tile[i][x].rect.y, WHITE);
              //DrawRectangleRec(tile[i][x].rect, WHITE);
              break;
            case START:
              DrawTexture(start, tile[i][x].rect.x, tile[i][x].rect.y, WHITE);
              //DrawRectangleRec(tile[i][x].rect, GREEN);
              break;
          }
      }
    }
}

int writeToFile(Tile tile[26][16], char *index, char *lName, char *star2, char *star3, char *path) {
    FILE *fp;
    std::string finalPath;
    finalPath += path;
    finalPath += ".txt";

    fp = fopen(finalPath.c_str(), "w+");
    if(fp == NULL) return -1;
    if(fprintf(fp, "<") < 0) return -1;
    if(fprintf(fp, "%s", index) < 0) return -1;
    if(fprintf(fp, ">") < 0) return -1;

    if(fprintf(fp, "<") < 0) return -1;
    if(fprintf(fp, "%s", lName) < 0) return -1;
    if(fprintf(fp, ">") < 0) return -1;

    if(fprintf(fp, "<") < 0) return -1;
    if(fprintf(fp, "%s", star2) < 0) return -1;
    if(fprintf(fp, ">") < 0) return -1;

    if(fprintf(fp, "<") < 0) return -1;
    if(fprintf(fp, "%s", star3) < 0) return -1;
    if(fprintf(fp, ">") < 0) return -1;

    if(fprintf(fp, "\n") < 0) return -1;

    for(int x = 0; x < 16; x++) {
      for(int i = 0; i < 26; i++) {
        if(tile[i][x].active) {
            switch (tile[i][x].type) {
              case FLOOR:
                if(fprintf(fp, ".") < 0) return -1;
                break;
              case WALL:
                if(fprintf(fp, "#") < 0) return -1;
                break;
              case START:
                if(fprintf(fp, "s") < 0) return -1;
                break;
            }
        }
      }
      if(fprintf(fp, "\n") < 0) return -1;
    }
    fclose(fp);
    return 0;
}

bool checkName(char *name, int count) {
    int ret = false;
    for(int i = 0; i < count; i++) {
        if(name[i] == ' ') {
            name[i] = '_';
            ret = true;
        }
    }
    return ret;
}