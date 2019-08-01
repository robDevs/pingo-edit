#include "common.h"

int main()
{
    // Initialization
    //--------------------------------------------------------------------------------------

    char name[MAX_INPUT_CHARS + 1] = "\0";      // NOTE: One extra space required for line ending char '\0'
    int letterCount = 0;

    textBox textBox1(20, screenHeight - 90, 300, 30, MAX_INPUT_CHARS + 1);
    textBox textBox2(textBox1.rect.x + textBox1.rect.width + 10, screenHeight - 90, 50, 30, 4);
    textBox textBox3(textBox2.rect.x + textBox2.rect.width + 10, screenHeight - 90, 300, 30, MAX_INPUT_CHARS + 1);
    textBox textBox4(textBox3.rect.x + textBox3.rect.width + 10, screenHeight - 90, 50, 30, 4);
    textBox textBox5(textBox4.rect.x + textBox4.rect.width + 10, screenHeight - 90, 50, 30, 4);

    Tile tile[26][16];
    initGid(tile);

    InitWindow(screenWidth, screenHeight, "levelEditor");

    loadTextures();
    Image icon = LoadImage("assets/ball.png");
    SetWindowIcon(icon);

    SetTargetFPS(60);
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        // TODO: Update your variables here
        //----------------------------------------------------------------------------------
        textBox1.update();
        textBox2.update();
        textBox3.update();
        textBox4.update();
        textBox5.update();

        if(IsKeyReleased(KEY_TAB)) {
            if(CheckCollisionPointRec(GetMousePosition(), textBox1.rect)) {
                SetMousePosition(textBox2.rect.x, textBox2.rect.y);
            }

            else if(CheckCollisionPointRec(GetMousePosition(), textBox2.rect)) {
                SetMousePosition(textBox3.rect.x, textBox3.rect.y);
            }

            else if(CheckCollisionPointRec(GetMousePosition(), textBox3.rect)) {
                SetMousePosition(textBox4.rect.x, textBox4.rect.y);
            }

            else if(CheckCollisionPointRec(GetMousePosition(), textBox4.rect)) {
                SetMousePosition(textBox5.rect.x, textBox5.rect.y);
            }

            else{
                SetMousePosition(textBox1.rect.x, textBox1.rect.y);
            }
        }

        if(IsKeyReleased(KEY_ENTER)){
            if(checkName(textBox1.message, textBox1.letterCount)) conprint("Changed spaces to '_'", 1);
            if(writeToFile(tile, textBox2.message, textBox3.message, textBox4.message, textBox5.message, textBox1.message) == -1) conprint("Error saving!", CON_ERROR);
            else conprint("Save successful!", CON_SUCCESS);
        }

        if(IsKeyReleased(KEY_UP) && levelHeight < 16) {
            levelHeight += 1;
            updateSize(tile);
        }
        if(IsKeyReleased(KEY_DOWN) && levelHeight > 2) {
            levelHeight -= 1;
            updateSize(tile);
        }

        if(IsKeyReleased(KEY_RIGHT) && levelWidth < 26) {
            levelWidth += 1;
            updateSize(tile);
        }
        if(IsKeyReleased(KEY_LEFT) && levelWidth > 2) {
            levelWidth -= 1;
            updateSize(tile);
        }

        if(IsKeyReleased(KEY_ONE))
            curr_tile = WALL;
        if(IsKeyReleased(KEY_TWO))
            curr_tile = FLOOR;
        if(IsKeyReleased(KEY_THREE))
            curr_tile = STOPTILE;
        if(IsKeyReleased(KEY_FOUR))
            curr_tile = FLOOR_EMPTY;
        if(IsKeyReleased(KEY_FIVE))
            curr_tile = CONVEYOR_BLANK;

        for(int i = 0; i < 26; i++)
          for(int x = 0; x < 16; x++) {
            Vector2 mousePoint = GetMousePosition();
            if(CheckCollisionPointRec(mousePoint, tile[i][x].rect) && tile[i][x].active) {
              if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                tile[i][x].type = curr_tile;
              }
              else if(IsMouseButtonPressed(MOUSE_RIGHT_BUTTON)) {
                for(int j = 0; j < 26; j++)
                  for(int k = 0; k < 16; k++)
                    if(tile[j][k].type == START) tile[j][k].type = FLOOR;
                if(tile[i][x].type = CONVEYOR_BLANK)
                    tile[i][x].rad += 90;
                if(tile[i][x].rad >= 360)
                    tile[i][x].rad = 0;
              }

            }
          }

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(RAYWHITE);

             drawTiles(tile);


             showNotifs();

             textBox1.draw();
             textBox2.draw();
             textBox3.draw();
             textBox4.draw();
             textBox5.draw();
             DrawText("File name", textBox1.rect.x, textBox1.rect.y + textBox1.rect.height, 10, BLACK);
             DrawText("Index", textBox2.rect.x, textBox2.rect.y + textBox2.rect.height, 10, BLACK);
             DrawText("Level name", textBox3.rect.x, textBox3.rect.y + textBox3.rect.height, 10, BLACK);
             DrawText("2 stars", textBox4.rect.x, textBox4.rect.y + textBox4.rect.height, 10, BLACK);
             DrawText("3 stars", textBox5.rect.x, textBox5.rect.y + textBox5.rect.height, 10, BLACK);

             DrawText("Press Enter to Save to file.", textBox1.rect.x + textBox1.rect.width + 20, screenHeight - 20, 20, BLACK);


        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    unloadTextures();
    UnloadImage(icon);
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
