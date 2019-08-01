#include "tile.h"

int defWidth = 936;
int defHeight = 544;

int levelWidth = 26;
int levelHeight = 16;

Texture floor;
Texture wall;
Texture start;
Texture bg;
Texture stopTile;
Texture floorEmpty;
Texture conveyorBlank;

int curr_tile = 0;

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

    tempImage = LoadImage("assets/stopTile.png");
    ImageResizeNN(&tempImage, 36, 34);
    stopTile = LoadTextureFromImage(tempImage);
    UnloadImage(tempImage);

    tempImage = LoadImage("assets/floorEmpty.png");
    ImageResizeNN(&tempImage, 36, 34);
    floorEmpty = LoadTextureFromImage(tempImage);
    UnloadImage(tempImage);

    tempImage = LoadImage("assets/conveyorBlank.png");
    ImageResizeNN(&tempImage, 36, 34);
    conveyorBlank = LoadTextureFromImage(tempImage);
    UnloadImage(tempImage);
}

void unloadTextures() {
    UnloadTexture(floor);
    UnloadTexture(wall);
    UnloadTexture(start);
    UnloadTexture(bg);
    UnloadTexture(stopTile);
    UnloadTexture(floorEmpty);
    UnloadTexture(conveyorBlank);
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
      tile[i][x].rad = 0;
    }
}

void updateSize(Tile tile[26][16]) {
    int newWidth = defWidth / levelWidth;
    int newHeight = defHeight / levelHeight;

    int newXStart = defWidth/2 - newWidth/2;
    int newYStart = defHeight/2 - newHeight/2;

    for(int i = 0; i < 26; i++) {
        for(int x = 0; x < 16; x++) {
            tile[i][x].rect.x = i * 36 + 12 + ((26 - levelWidth) * 18);
            tile[i][x].rect.y = x * 34 + ((16 - levelHeight) * 17);

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
              tile[i][x].rad = 0;
              //DrawRectangleRec(tile[i][x].rect, BLACK);
              break;
            case WALL:
              DrawTexture(wall, tile[i][x].rect.x, tile[i][x].rect.y, WHITE);
              tile[i][x].rad = 0;
              //DrawRectangleRec(tile[i][x].rect, WHITE);
              break;
            case START:
              DrawTexture(start, tile[i][x].rect.x, tile[i][x].rect.y, WHITE);
              tile[i][x].rad = 0;
              //DrawRectangleRec(tile[i][x].rect, GREEN);
              break;
            case STOPTILE:
              DrawTexture(stopTile, tile[i][x].rect.x, tile[i][x].rect.y, WHITE);
              tile[i][x].rad = 0;
              //DrawRectangleRec(tile[i][x].rect, GREEN);
              break;
            case FLOOR_EMPTY:
              DrawTexture(floorEmpty, tile[i][x].rect.x, tile[i][x].rect.y, WHITE);
              tile[i][x].rad = 0;
            //DrawRectangleRec(tile[i][x].rect, GREEN);
              break;
            case CONVEYOR_BLANK:
              if(tile[i][x].rad == 0)
                DrawTextureEx(conveyorBlank, (Vector2){tile[i][x].rect.x, tile[i][x].rect.y}, tile[i][x].rad, 1.0f, WHITE);
              if(tile[i][x].rad == 90)
                DrawTextureEx(conveyorBlank, (Vector2){tile[i][x].rect.x + 36, tile[i][x].rect.y}, tile[i][x].rad, 1.0f, WHITE);
              if(tile[i][x].rad == 180)
                DrawTextureEx(conveyorBlank, (Vector2){tile[i][x].rect.x + 36, tile[i][x].rect.y + 34}, tile[i][x].rad, 1.0f, WHITE);
              if(tile[i][x].rad == 270)
                DrawTextureEx(conveyorBlank, (Vector2){tile[i][x].rect.x, tile[i][x].rect.y + 34}, tile[i][x].rad, 1.0f, WHITE);
              //DrawRectangleRec(tile[i][x].rect, GREEN);
              break;
          }
      }
      else {
          tile[i][x].type = WALL;
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

    for(int x = 0; x < levelHeight; x++) {
      for(int i = 0; i < levelWidth; i++) {
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
              case STOPTILE:
                if(fprintf(fp, "x") < 0) return -1;
                break;
              case FLOOR_EMPTY:
                if(fprintf(fp,"d") < 0) return -1;
                break;
              case CONVEYOR_BLANK:
                if(tile[i][x].rad == 0)
                  if(fprintf(fp, "^") < 0) return -1;
                if(tile[i][x].rad == 90)
                  if(fprintf(fp, ">") < 0) return -1;
                if(tile[i][x].rad == 180)
                  if(fprintf(fp, "v") < 0) return -1;
                if(tile[i][x].rad == 270)
                  if(fprintf(fp, "<") < 0) return -1;
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

void draw_selector(int x, int y, int type, bool selected) {
    switch (type) {
      case FLOOR:
        DrawTexture(floor, x + 2, y + 2, WHITE);
        //DrawRectangleRec(tile[i][x].rect, BLACK);
        break;
      case WALL:
        DrawTexture(wall, x + 2, y + 2, WHITE);
        //DrawRectangleRec(tile[i][x].rect, WHITE);
        break;
      case START:
        DrawTexture(start, x + 2, y + 2, WHITE);
        //DrawRectangleRec(tile[i][x].rect, GREEN);
        break;
      case STOPTILE:
        DrawTexture(stopTile, x + 2, y + 2, WHITE);
        //DrawRectangleRec(tile[i][x].rect, GREEN);
        break;
      case FLOOR_EMPTY:
        DrawTexture(floorEmpty, x + 2, y + 2, WHITE);
      //DrawRectangleRec(tile[i][x].rect, GREEN);
        break;
      case CONVEYOR_BLANK:
        DrawTexture(conveyorBlank, x + 2, y + 2, WHITE);
        break;
    }
    DrawText(TextFormat("%d", type + 1), x+ 19, y + 38 + 20 - 20, 15, BLACK);
    if(selected) {
        DrawRectangleLines(x, y, 38, 36, PURPLE);
        DrawRectangleLines(x+1, y+1, 36, 35, PURPLE);
        DrawRectangleLines(x+2, y+1, 35, 34, PURPLE);
    }
    else
        DrawRectangleLines(x, y, 38, 36, BLACK);
}
