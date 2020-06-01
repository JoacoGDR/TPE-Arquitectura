#ifndef VIDEO_DRIVER_H
#define VIDEO_DRIVER_H

//static unsigned int SCREEN_WIDTH = 1024;
//static unsigned int SCREEN_HEIGHT = 768;

void init_VM_Driver();
void drawPixel(unsigned int x, unsigned int y, int color);
void clearVideoDisplay();


#endif
