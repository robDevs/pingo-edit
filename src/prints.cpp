#include "prints.h"

std::vector<Message> messageList;

textBox::textBox(int x, int y, int w, int h, int max) {
    for(int i = 0; i < MAX_INPUT_CHARS + 1; i++) {
        message[i] = '\0';
    }
    this->rect.x = x;
    this->rect.y = y;
    this->rect.width = w;
    this->rect.height = h;
    this->max = max;
    this->mouseOnText = false;
    this->letterCount = 0;
    this->framesCounter = 0;
}

void textBox::update() {

    if (CheckCollisionPointRec(GetMousePosition(), rect)) mouseOnText = true;
    else mouseOnText = false;

    if (mouseOnText)
    {
        int key = GetKeyPressed();

        // NOTE: Only allow keys in range [32..125]
        if ((key >= 32) && (key <= 125) && (letterCount < max))
        {
            message[letterCount] = (char)key;
            letterCount++;
        }

        if (IsKeyPressed(KEY_BACKSPACE) && letterCount > 0)
        {
            letterCount--;
            message[letterCount] = '\0';

            if (letterCount < 0) letterCount = 0;
        }
    }

    if (mouseOnText) framesCounter++;
    else framesCounter = 0;
}

void textBox::draw() {
    DrawRectangleRec(rect, LIGHTGRAY);

    if (mouseOnText) DrawRectangleLines(rect.x, rect.y, rect.width, rect.height, VIOLET);
    else DrawRectangleLines(rect.x, rect.y, rect.width, rect.height, DARKGRAY);

    DrawText(message, rect.x + 5, rect.y + 8, 20, VIOLET);

    if (mouseOnText)
    {
        if (letterCount < MAX_INPUT_CHARS)
        {
            // Draw blinking underscore char
            if (((framesCounter/20)%2) == 0) DrawText("_", rect.x + 8 + MeasureText(message, 20), rect.y + 12, 20, VIOLET);
        }
    }
}

void conprint(const char *message, int level) {
    Message newMessage;
    newMessage.message = message;
    newMessage.timer = (60*5);
    newMessage.level = level;
    newMessage.fade = 225 / 2;

    messageList.push_back(newMessage);
}

void showNotifs() {
    for(int i = 0; i < 4; i++) {
        if(i >= messageList.size()) break;
        Rectangle MessageBox;

        MessageBox.x = screenWidth - 320;
        MessageBox.y = i*60;
        MessageBox.width = 300;
        MessageBox.height = 50;

        Color color;
        color.r = 0;
        color.g = 0;
        color.b = 0;
        color.a = messageList[i].fade;

        DrawRectangleRec(MessageBox, color);

        messageList[i].timer--;
        if(messageList[i].timer <= 0) messageList[i].fade--;
        if(messageList[i].fade <= 0) messageList.erase(messageList.begin() + i);

        switch (messageList[i].level) {
            case CON_NORMAL:
                color.r = 255;
                color.g = 255;
                color.b = 255;
                break;
            case CON_WARN:
                color.r = 255;
                color.g = 255;
                color.b = 50;
                break;
            case CON_ERROR:
                color.r = 255;
                color.g = 0;
                color.b = 0;
                break;
            case CON_SUCCESS:
                color.r = 0;
                color.g = 255;
                color.b = 0;
                break;
            default: break;
        }

        DrawText(messageList[i].message, MessageBox.x + 5, MessageBox.y + 25 - 10, 20, color);
    }
}
