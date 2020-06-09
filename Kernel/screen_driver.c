#include <video_driver.h>
#include <font.h>
#include <lib.h>

#define SCREEN_1 0
#define SCREEN_2 1

#define SCREEN_CHAR_WIDTH 128
#define SCREEN_CHAR_HEIGHT 48
#define SCREEN_LIMIT 60
#define WALL 128/2

void drawChar2(char c, int fc, int bc);



void update_cursor();
void updateLines();

unsigned int screen_pixel_width;
unsigned int screen_pixel_height;

//Estas dos variables estan hechas para saber la posicion del "cursor" de pixel en la ULTIMA LÍNEA de la pantalla.
unsigned int pixelX;    //Estos son los x de pixeles. 
unsigned int pixelY;


// le pongo el +1 para que asi tambien pueda almacenar oraciones que son de justo 128 caracteres de largo
char screen[SCREEN_CHAR_HEIGHT][SCREEN_CHAR_WIDTH+1] = {"\0"};   

//estos son mis y e x en mi screen de caracteres.
int current_y;
int current_x;

int screenId;

//screenId va a ser 0 si es la primera pantalla, 1 si es la segunda.
void init_screen_driver(unsigned int width, unsigned int height,unsigned int Id) {
	screen_pixel_height = height; // viene con 768
	screen_pixel_width = width;   // viene con 1024
	
	screenId = Id;

	for(int j = 0; j<height; j++){
		drawPixel(WALL*(CHAR_WIDTH) - Id,j,0x33333);
	}
	drawString("hohola",0x333,0x000);

	current_y = SCREEN_CHAR_HEIGHT - 1;
	current_x = WALL*screenId;

	

 	pixelX = screenId*WALL*CHAR_WIDTH;  							
	pixelY = screen_pixel_height - CHAR_HEIGHT; 
}



void drawChar2(char character, int fontColor ,int backgroundColor){
	 if(character == '\n'){
		move_screen_upwards();
	 	pixelX = screenId*WALL*CHAR_WIDTH; //si es la segunda entonces empieza en WALL
		current_x = screenId*WALL;
	}

	else if(character == '\b'){
		if ( pixelX > screenId*WALL*CHAR_WIDTH){
		 	pixelX -= CHAR_WIDTH;
			clearCharDisplay (pixelX, pixelY);
			screen[current_y][--current_x] = '\0'; //Con esto soluciono el problema que tenia que al escribir por ejemplo "hola", borrar la "a" y enter, salia "hola".
			//current_x -= 1; //porque si llegue al final deberia poder borrar, y volver a escribir, pero el if de mas abajo no me dejaria hacerlo si no hago eso
		}else{
			current_x = pixelX;
			clearCharDisplay (pixelX, pixelY);
		}
	}
    


	else{ 
			if(current_x <= (SCREEN_LIMIT+WALL*screenId)){
				screen[current_y][current_x] = character;
						current_x += 1;
						int aux_x = pixelX;
						int aux_y = pixelY;
						char bitsIsPresent;
						unsigned char* toDraw = charBitmap(character);
						for(int i = 0; i<CHAR_HEIGHT; i++){
							for(int j=0; j<CHAR_WIDTH; j++){
								bitsIsPresent = (1 << (CHAR_WIDTH - j)) & toDraw[i];
								if(bitsIsPresent)
									drawPixel(aux_x, aux_y, fontColor);
								else
									drawPixel(aux_x, aux_y, backgroundColor);
								aux_x += 1;
							}
							aux_x = pixelX;
							aux_y += 1;
						}

				//hay que ver como modificamos esta función
				update_cursor();
		}
	}
				
}





void update_cursor() {
	if( pixelX < (((SCREEN_LIMIT+screenId*WALL) - 1)*CHAR_WIDTH) ) {
	 	pixelX += CHAR_WIDTH;
	} else {

	 	pixelX = screenId*WALL;
	}
}


void drawString(char* string, int fontColor, int backgroundColor) {
	while(*string){
		drawChar2(*string,fontColor,backgroundColor);
		string++;
	}
}


void drawCharInSpecificSpot(int x, int y, char character,  int fontColor, int backgroundColor){
	int aux_x = x;
	int aux_y = y;
	char bitsIsPresent;
	unsigned char* toDraw = charBitmap(character);
	for(int i = 0; i<CHAR_HEIGHT; i++){
		for(int j=0; j<CHAR_WIDTH; j++){
			bitsIsPresent = (1 << (CHAR_WIDTH - j)) & toDraw[i];
			if(bitsIsPresent)
				drawPixel(aux_x, aux_y, fontColor);
			else
				drawPixel(aux_x, aux_y, backgroundColor);
			aux_x += 1;
		}
		aux_x = x;
		aux_y += 1;
	}
}



void move_screen_upwards() {
	int width_position_to_write_next = screenId*WALL;
	int height_position_to_write_next = 0;

	for(int i=0; i< SCREEN_CHAR_HEIGHT-1; i++) {
	
		char* line_to_copy = screen[i+1];
	
		for(int j=screenId*WALL; line_to_copy[j]!='\0'; j++) {
			screen[height_position_to_write_next][width_position_to_write_next] = line_to_copy[j];
			drawCharInSpecificSpot(width_position_to_write_next * CHAR_WIDTH, height_position_to_write_next * CHAR_HEIGHT, line_to_copy[j],  0xFFFFFF, 0x000000);
			width_position_to_write_next+=1;
		}
	
		screen[height_position_to_write_next][width_position_to_write_next] = '\0';
		
		// tambien tengo que limpiar el resto de la linea que quedo.
		for(int k = width_position_to_write_next; k < (SCREEN_LIMIT+WALL*screenId) ; k++) {
			clearCharDisplay(k * CHAR_WIDTH, height_position_to_write_next * CHAR_HEIGHT);
		}

	
		width_position_to_write_next = screenId*WALL;
		height_position_to_write_next += 1;
	}
	// tengo que vaciar la ultima linea de la pantalla y la de la matriz
	for(int i = screenId*WALL; i < (SCREEN_LIMIT+WALL*screenId) ; i++) {
		clearCharDisplay(i * CHAR_WIDTH, screen_pixel_height - CHAR_HEIGHT);
		screen[height_position_to_write_next][i] = '\0';
	}
}




//borra un caracter
void clearCharDisplay(int x, int y) {
	int aux_x=x;
	int aux_y=y;
	int black_color = 0x000000;
	for(int i = 0; i < CHAR_HEIGHT; i++) { 
		for(int j = 0; j < CHAR_WIDTH; j++) {
			drawPixel(aux_x, aux_y, black_color);
			aux_x+=1;
		}
		aux_x=x;
		aux_y+=1;
	}
}




