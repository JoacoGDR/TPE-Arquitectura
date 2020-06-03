#include <video_driver.h>
#include <font.h>
#include <lib.h>
#define SCREEN_CHAR_LENGTH 129
#define SCREEN_CHAR_WIDTH 48
#define SCREEN_LIMIT 120
/*
int strlen(char*);
int getNumberLength(int);
char* num_to_string(int);
void drawNumber(int, int, int, int);
void clearCharDisplay(int width_position, int height_position);
void move_screen_upwards();
void drawCharInSpecificSpot(int x, int y, char character, int fontSize, int fontColor, int backgroundColor);

*/
void drawChar2(char c, int fc, int bc);
void drawSquare(int x, int y, int color);
void drawString(char* string, int fontSize, int fontColor, int backgroundColor);
void drawString2(char * str, int l);
void update_cursor();
void updateLines();

unsigned int screen_width;
unsigned int screen_height;

/* these next 2 variables are used just to know the cursor position in the LAST row of the screen*/
/* therefore, the height variable will never change */
unsigned int width_position_last_row; 
unsigned int height_position_last_row;

// le pongo el +1 para que asi tambien pueda almacenar oraciones que son de justo 128 caracteres de largo
char lines[48][128+1] = {"\0"};   
int current_line_height = 47;
int current_line_width = 0;

void init_screen_driver(unsigned int width, unsigned int height) {
	screen_height = height; // viene con 768
	screen_width = width;   // viene con 1024
	width_position_last_row = 0;  							//
	height_position_last_row = screen_height - CHAR_HEIGHT; //>>$: hola
	//drawSquare(200, 200, 0xcccccc);
	//drawChar2('A');
	
	
	
}
void drawChar2(char character, int fontColor ,int backgroundColor){
	 //int fontColor = 0x666666;
	 //backgroundColor = 0xffffff;

	 if(character == '\n'){
		move_screen_upwards();
		width_position_last_row = 0;
		current_line_width = 0;
	}
 /// aaaaaaa
	else if(character == '\b'){
		if(width_position_last_row > 0){
			width_position_last_row -= CHAR_WIDTH;
			clearCharDisplay(width_position_last_row, height_position_last_row);
			current_line_width--; //porque si llegue al final deberia poder borrar, y volver a escribir, pero el if de mas abajo no me dejaria hacerlo si no hago eso
		}else{
			height_position_last_row -= CHAR_HEIGHT;
			width_position_last_row = SCREEN_LIMIT - CHAR_WIDTH;//screen_width-CHAR_WIDTH;
			current_line_width = width_position_last_row;
			clearCharDisplay(width_position_last_row, height_position_last_row);
		}
	}
    

	/*else if(character == '\b'){
		if(width_position_last_row > 1){
			width_position_last_row -= CHAR_WIDTH;
			drawChar2(' ', 0x000000, 0x000000);
			width_position_last_row -= CHAR_WIDTH;
		}
		else if(width_position_last_row == 0){
			
		}
		else if(width_position_last_row == 1){
			width_position_last_row = screen_width;
			height_position_last_row -= CHAR_HEIGHT;
			drawChar2(' ', 0x000000, 0x000000);
			width_position_last_row -= CHAR_WIDTH;
			
		}
	}*/

	else{ 
			if(current_line_width <= SCREEN_LIMIT){
				lines[current_line_height][current_line_width] = character;
						current_line_width += 1;
						int aux_x = width_position_last_row;
						int aux_y = height_position_last_row;
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
							aux_x = width_position_last_row;
							aux_y += 1;
						}
				update_cursor();
		}
	}
				
}

/*
for(j ...){
	lines[last_row-2][j] = lines[last_row-1][j];
	lines[last_row-1][j] = 0;
}
lines[i][j] = lines[i+1][j];
lines[last_row][j] = '_';
*/



void update_cursor() {
	if( width_position_last_row < screen_width - CHAR_WIDTH ) {
		width_position_last_row += CHAR_WIDTH;
	} else {
		//move_screen_upwards();
	 	width_position_last_row = 0;
	}
}

//CAMBIAR Y PONER EL STRLEN
void drawString(char* string, int fontSize, int fontColor, int backgroundColor) {
	//for(int i = 0; i < 3/*strlen(string)*/; i++){
	//	drawChar2(string[i], fontSize, fontColor, backgroundColor*/);
	//}
	while(*string){
		drawChar2(*string,0x666666,0xffffff);
		string++;
	}
 

}


void drawCharInSpecificSpot(int x, int y, char character, int fontSize, int fontColor, int backgroundColor){
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
	int width_position_to_write_next = 0;
	int height_position_to_write_next = 0;

	for(int i=0; i<48-1; i++) {
	
		char* line_to_copy= lines[i+1];
	
		for(int j=0; line_to_copy[j]!='\0'; j++) {
			lines[height_position_to_write_next][width_position_to_write_next] = line_to_copy[j];
			drawCharInSpecificSpot(width_position_to_write_next * CHAR_WIDTH, height_position_to_write_next * CHAR_HEIGHT, line_to_copy[j], 10, 0xFFFFFF, 0x000000);
			width_position_to_write_next+=1;
		}
	
		lines[height_position_to_write_next][width_position_to_write_next] = '\0';
		
		// tambien tengo que limpiar el resto de la linea que quedo.
		for(int k = width_position_to_write_next; k < screen_width/CHAR_WIDTH; k++) {
			clearCharDisplay(k * CHAR_WIDTH, height_position_to_write_next * CHAR_HEIGHT);
		}
	
		width_position_to_write_next = 0;
		height_position_to_write_next += 1;
	}
	// tengo que vaciar la ultima linea de la pantalla y la de la matriz
	for(int i = 0; i < screen_width/CHAR_WIDTH; i++) {
		clearCharDisplay(i * CHAR_WIDTH, screen_height - CHAR_HEIGHT);
		lines[height_position_to_write_next][i] = '\0';
	}
}

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

/*
void give_screen_parameters(unsigned int width, unsigned int height) {
	screen_height = height; // viene con 768
	screen_width = width;   // viene con 1024
	width_position_last_row = 0;
	height_position_last_row = screen_height - CHAR_HEIGHT;
}
*/
//
/* lo comento a luego vemos que metemos de aca:

void update_cursor() {
	if( width_position_last_row < screen_width - CHAR_WIDTH ) {
		width_position_last_row += CHAR_WIDTH;
	} else {
		move_screen_upwards();
	 	width_position_last_row = 0;
	}
}

void drawNumber2(int x, int y, int number, int fontSize, int fontColor, int backgroundColor) {
	int number_length = getNumberLength(number);
	char* number_converted = num_to_string(number);
	int aux_x = x;
	for(int i=0; i<number_length; i++) {
		drawCharInSpecificSpot(aux_x, y, number_converted[i], fontSize, fontColor, backgroundColor);
		aux_x += CHAR_WIDTH;
	}
}



void drawChar(char character, int fontSize, int fontColor, int backgroundColor){
	if(character == '\n'){
		move_screen_upwards();
		width_position_last_row = 0;
		current_line_width = 0;
	}
	else if(character == '\b'){
		if(width_position_last_row>0){
			width_position_last_row-=CHAR_WIDTH;
			clearCharDisplay(width_position_last_row, height_position_last_row);
		}else{
			height_position_last_row-=CHAR_HEIGHT;
			width_position_last_row=screen_width-CHAR_WIDTH;
			clearCharDisplay(width_position_last_row, height_position_last_row);
		}
	}
	else{
		lines[current_line_height][current_line_width] = character;
		current_line_width+=1;

		int aux_x = width_position_last_row;
		int aux_y = height_position_last_row;
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
			aux_x = width_position_last_row;
			aux_y += 1;
		}
		update_cursor();
	}
}        


void move_screen_upwards() {
	int width_position_to_write_next = 0;
	int height_position_to_write_next = 0;

	for(int i=0; i<48-1; i++) {
	
		char* line_to_copy= lines[i+1];
	
		for(int j=0; line_to_copy[j]!='\0'; j++) {
			lines[height_position_to_write_next][width_position_to_write_next] = line_to_copy[j];
			drawCharInSpecificSpot(width_position_to_write_next * CHAR_WIDTH, height_position_to_write_next * CHAR_HEIGHT, line_to_copy[j], 10, 0xFFFFFF, 0x000000);
			width_position_to_write_next+=1;
		}
	
		lines[height_position_to_write_next][width_position_to_write_next] = '\0';
		
		// tambien tengo que limpiar el resto de la linea que quedo.
		for(int k = width_position_to_write_next; k < screen_width/CHAR_WIDTH; k++) {
			clearCharDisplay(k * CHAR_WIDTH, height_position_to_write_next * CHAR_HEIGHT);
		}
	
		width_position_to_write_next = 0;
		height_position_to_write_next+=1;
	}
	// tengo que vaciar la ultima linea de la pantalla y la de la matriz
	for(int i = 0; i < screen_width/CHAR_WIDTH; i++) {
		clearCharDisplay(i * CHAR_WIDTH, screen_height - CHAR_HEIGHT);
		lines[height_position_to_write_next][i] = '\0';
	}
}

void drawString(char* string, int fontSize, int fontColor, int backgroundColor) {
	for(int i=0; i<strlen(string); i++){
		drawChar(string[i], fontSize, fontColor, backgroundColor);
	}
}

void drawNumber(int number, int fontSize, int fontColor, int backgroundColor) {
	int is_negative_number = 0;
	if(number < 0) {
		is_negative_number = 1;
		number *= (-1);
	}

	int number_length = getNumberLength(number);
	char* number_converted = num_to_string(number);

	if(is_negative_number) {
		drawChar('-', fontSize, fontColor, backgroundColor);
	}

	for(int i=0; i<number_length; i++) {
		drawChar(number_converted[i], fontSize, fontColor, backgroundColor);
	}
}

void clearScreenDisplay() {
	width_position_last_row = 0;
	height_position_last_row = screen_height - CHAR_HEIGHT;
	clearVideoDisplay();
}

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



void init_screen_driver() {
	actual_width_position = 0; 
	actual_height_position = 0;
}

void update_cursor() {
	if( actual_width_position < SCREEN_WIDTH - CHAR_WIDTH ) {
		actual_width_position += CHAR_WIDTH;
	} else {
	 	actual_height_position += CHAR_HEIGHT;
	 	actual_width_position = 0;
	}
}


void drawChar(char character, int fontSize, int fontColor, int backgroundColor){
	if(character == '\n'){
		actual_width_position = 0;
		actual_height_position += CHAR_HEIGHT*2;
	}
	else if(character == '\b'){
		if(actual_width_position>0){
			actual_width_position-=CHAR_WIDTH;
			clearCharDisplay();
		}else{
			actual_height_position-=CHAR_HEIGHT;
			actual_width_position=SCREEN_WIDTH-CHAR_WIDTH;
			clearCharDisplay();
		}
	}
	else{
		int aux_x = actual_width_position;
		int aux_y = actual_height_position;
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
			aux_x = actual_width_position;
			aux_y += 1;
		}
		update_cursor();
	}
}

void drawString(char* string, int fontSize, int fontColor, int backgroundColor) {
	for(int i=0; i<strlen(string); i++){
		drawChar(string[i], fontSize, fontColor, backgroundColor);
	}
}

void drawNumber(int number, int fontSize, int fontColor, int backgroundColor) {
	int is_negative_number = 0;
	if(number < 0) {
		is_negative_number = 1;
		number *= (-1);
	}

	int number_length = getNumberLength(number);
	char* number_converted = num_to_string(number);

	if(is_negative_number) {
		drawChar('-', fontSize, fontColor, backgroundColor);
	}

	for(int i=0; i<number_length; i++) {
		drawChar(number_converted[i], fontSize, fontColor, backgroundColor);
	}
}

void clearScreenDisplay() {
	actual_width_position = 0;
	actual_height_position = 0;
	clearVideoDisplay();
}

void clearCharDisplay(){
	int aux_x=actual_width_position;
	int aux_y=actual_height_position;
	int black_color = 0x000000;
	for(int i = 0; i < CHAR_HEIGHT; i++) {
		for(int j = 0; j < CHAR_WIDTH; j++) {
			drawPixel(aux_x, aux_y, black_color);
			aux_x+=1;
		}
		aux_x=actual_width_position;
		aux_y+=1;
	}
}//*/

void drawSquare(int x, int y, int color){
	int aux_x=x;
	int aux_y=y;
	for(int i = 0; i < CHAR_HEIGHT; i++) {
		for(int j = 0; j < CHAR_WIDTH; j++) {
			drawPixel(aux_x, aux_y, color);
			aux_x+=1;
		}
		aux_x=x;
		aux_y+=1;
	}
} 

