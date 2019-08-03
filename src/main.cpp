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

    button save_button;
    save_button.clicked = false;
    save_button.x = screenWidth - 140;
    save_button.y = screenHeight - 60;
    save_button.text = "Save";

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
                SetMousePosition((Vector2){textBox2.rect.x, textBox2.rect.y});
            }

            else if(CheckCollisionPointRec(GetMousePosition(), textBox2.rect)) {
                SetMousePosition((Vector2){textBox3.rect.x, textBox3.rect.y});
            }

            else if(CheckCollisionPointRec(GetMousePosition(), textBox3.rect)) {
                SetMousePosition((Vector2){textBox4.rect.x, textBox4.rect.y});
            }

            else if(CheckCollisionPointRec(GetMousePosition(), textBox4.rect)) {
                SetMousePosition((Vector2){textBox5.rect.x, textBox5.rect.y});
            }

            else{
                SetMousePosition((Vector2){textBox1.rect.x, textBox1.rect.y});
            }
        }

        if(IsKeyReleased(KEY_ENTER)){
            if(checkName(textBox1.message, textBox1.letterCount)) conprint("Changed spaces to '_'", 1);
            if(writeToFile(tile, textBox2.message, textBox3.message, textBox4.message, textBox5.message, textBox1.message) == -1) conprint("Error saving!", CON_ERROR);
            else conprint("Save successful!", CON_SUCCESS);
        }

        if(IsKeyPressed(KEY_UP) && levelHeight < 16) {
            levelHeight += 1;
            updateSize(tile);
        }
        if(IsKeyPressed(KEY_DOWN) && levelHeight > 2) {
            levelHeight -= 1;
            updateSize(tile);
        }

        if(IsKeyPressed(KEY_RIGHT) && levelWidth < 26) {
            levelWidth += 1;
            updateSize(tile);
        }
        if(IsKeyPressed(KEY_LEFT) && levelWidth > 2) {
            levelWidth -= 1;
            updateSize(tile);
        }
        if(!textBox1.mouseOnText && !textBox2.mouseOnText && !textBox3.mouseOnText &&!textBox4.mouseOnText && !textBox5.mouseOnText) {
          if(IsKeyPressed(KEY_ONE))
              curr_tile = 0;
          if(IsKeyPressed(KEY_TWO))
              curr_tile = 1;
          if(IsKeyPressed(KEY_THREE))
              curr_tile = 2;
          if(IsKeyPressed(KEY_FOUR))
              curr_tile = 3;
          if(IsKeyPressed(KEY_FIVE))
              curr_tile = 4;
          if(IsKeyPressed(KEY_SIX))
              curr_tile = 5;
        }

        //move with mouse wheel scroll
        curr_tile += GetMouseWheelMove();
        //check if mouse scroll was too far.
        if(curr_tile > 5)
            curr_tile = 0;
        if(curr_tile < 0)
            curr_tile = 5;

        for(int i = 0; i < 26; i++)
          for(int x = 0; x < 16; x++) {
            Vector2 mousePoint = GetMousePosition();
            if(CheckCollisionPointRec(mousePoint, tile[i][x].rect) && tile[i][x].active) {
              if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                if(curr_tile == START) {
                    for(int j = 0; j < 26; j++)
                        for(int k = 0; k < 16; k++)
                            if(tile[j][k].type == START) tile[j][k].type = WALL;
                }
                tile[i][x].type = curr_tile;                
              }
              else if(IsMouseButtonPressed(MOUSE_RIGHT_BUTTON)) {
                if(tile[i][x].type == CONVEYOR_BLANK)
                    tile[i][x].rad += 90;
                if(tile[i][x].rad >= 360)
                    tile[i][x].rad = 0;
              }

            }
          }


          if(save_button.update() == 1) {
              if(checkName(textBox1.message, textBox1.letterCount)) conprint("Changed spaces to '_'", 1);
              if(writeToFile(tile, textBox2.message, textBox3.message, textBox4.message, textBox5.message, textBox1.message) == -1) conprint("Error saving!", CON_ERROR);
              else conprint("Save successful!", CON_SUCCESS);
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

             //DrawText("Press Enter to Save to file.", textBox1.rect.x + textBox1.rect.width + 20, screenHeight - 20, 20, BLACK);

             DrawRectangle(screenWidth/2-(40*6/2), screenHeight-50, 40*6, 50, GRAY);
             for(int i = 0; i < 6; i++) {
                 draw_selector(screenWidth/2-(38*6/2)+i*38, screenHeight-50, i, curr_tile == i);
                 Vector2 mousePoint = GetMousePosition();
                 if(CheckCollisionPointRec(mousePoint, (Rectangle){(float)screenWidth/2-(38*6/2)+i*38, (float)screenHeight-50, 36, 34})) {
                   if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                     curr_tile = i;
                   }
                 }
             }

             save_button.draw();

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
