#ifndef _SCREEN_DRIVER_
#define _SCREEN_DRIVER_

void drawString(char* string, int fontSize, int fontColor, int backgroundColor);
void init_screen_driver(int width, int height);
//void give_screen_parameters(int width, int height);
void drawNumber(int number, int fontSize, int fontColor, int backgroundColor);
void clearScreenDisplay();
void update_cursor();
void drawChar(char character, int fontSize, int fontColor, int backgroundColor);
void drawSquare(int x, int y, int color);

// sacar el drawNumber2 y tambien el drawCharInSpecificSpot, ya que ni deberia ser vista desde afuera
// ya que es muy "poderosa" (podes escribir en cualquier lado)
void drawCharInSpecificSpot(int x, int y, char character, int fontSize, int fontColor, int backgroundColor);
void drawNumber2(int x, int y, int number, int fontSize, int fontColor, int backgroundColor);

#endif
