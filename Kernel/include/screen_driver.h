#ifndef _SCREEN_DRIVER_
#define _SCREEN_DRIVER_

void drawString(char* string,  int fontColor, int backgroundColor);
void init_screen_driver(int width, int height);


void clearScreenDisplay();
void update_cursor();
void drawChar(char character, int fontSize, int fontColor, int backgroundColor);



void drawCharInSpecificSpot(int x, int y, char character,  int fontColor, int backgroundColor);

void drawString2(char * c, int length);

#endif
