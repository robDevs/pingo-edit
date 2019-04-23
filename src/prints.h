#ifndef PRINTS_
#define PRINTS_

#include <vector>

#include "common.h"

#define CON_NORMAL  0
#define CON_WARN    1
#define CON_ERROR   2
#define CON_SUCCESS 3

typedef struct Message {
    const char *message;
    int timer;
    int level;
    int fade;
} Message;

typedef struct textBox{
    char message[MAX_INPUT_CHARS + 1];
    Rectangle rect;
    int max;
    bool mouseOnText;
    int letterCount;
    int framesCounter;
    textBox(int x, int y, int w, int h, int max);
    void update();
    void draw();
}textBox;

extern std::vector<Message> messageList;

extern void conprint(const char *message, int level);
extern void showNotifs();

#endif
