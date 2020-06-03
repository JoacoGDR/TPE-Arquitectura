#include <keyboard.h>
#include <video_driver.h>
#include <screen_driver.h>  // solo para probar los drawString y esos


#define KEYBOARD_BUFFER_SIZE 100

 int getKey(); 
void update_keyboard_buffer(char letra);

char keyboard_buffer[KEYBOARD_BUFFER_SIZE] = {0};

char caps_lock = 0;
char shift_pressed = 0;
char ctrl_pressed = 0;
char alt_pressed = 0;
char esc_pressed = 0;

int keyboard_buffer_actual_position = 0;

int keyboard_handler(){
	char letra = get_letter_code();

	if(letra == -1){
		return -1;
	}
	else{
		update_keyboard_buffer(letra); 
		return 1;
		//drawString(keyboard_buffer, 10, 0x000000, 0xFFFFFF);
		//drawChar(letra, 10, 0x000000, 0xFFFFFF);
	}
}

// Si es ctrl,shift, etc prendo el flag, y retorno -1. Sino retorno el caracter correspondiente
char get_letter_code(){
	int c = getKey(); //aca obtengo el codigo de la letra
	/* while(c>=0x81) {
	 	c = getKey();   // este while es para filtrar los break code
	 }*/
	int len = sizeof(map);
 
	switch(c){
		case L_SHIFT:
		case R_SHIFT:
				shift_pressed = 1;return -1;			
		case L_SHIFT_RELEASED:
		case R_SHIFT_RELEASED:
				shift_pressed = 0;return -1;

		case L_CTRL:
				ctrl_pressed = 1;return -1;
		case L_CTRL_RELEASED:
				ctrl_pressed = 0;return -1;

		case L_ALT:
				alt_pressed = 1;return -1;
		case L_ALT_RELEASED:
				alt_pressed = 0;return -1;

		case CAPSLOCK:
				if(caps_lock == 0){
					caps_lock = 1;
				}else{ 
					caps_lock = 0;
					}
					return -1;
		case ESC:
				esc_pressed = 1;return -1;
		case ESC_RELEASED:
				esc_pressed = 0;return -1;

		case DOWN:
		case UP:
		case LEFT:
		case RIGHT:
		case TAB:
			return -1;

		//Si no es ninguna tecla especial, entonces debe ser una letra/numero/signo
		default:
			if (c > 0  &&  c < len  &&  map[c]!='\0'){
				if(shift_pressed == 0){
					if(caps_lock == 0){
						//Busco en la tabla en minuscula:
							return map[c];
					}
					else if(caps_lock == 1){
						//Busco en la tabla en MAYUSCULA
						if(isLetra(c))
							return map_shift[c];
						return map[c];
					}
				}
				if(shift_pressed == 1){
					if(caps_lock == 0){
						//Busco en la tabla en MAYUSCULA
						return map_shift[c];
					}
					else if(caps_lock == 1){
						//Busco en la tabla en minuscula
						if(isLetra(c))
							return map[c];
						return map_shift[c];
					}
				}		
			}
			else{
				//drawString("nada",5,0x000000,0x0000FF);
				return -1;
			}

			break;
	}

	return -1;
}

void update_keyboard_buffer(char letra) {
	if(keyboard_buffer_actual_position == KEYBOARD_BUFFER_SIZE)
		keyboard_buffer_actual_position = 0;
	keyboard_buffer[keyboard_buffer_actual_position] = letra;
	keyboard_buffer_actual_position++;
}

void clear_keyboard_buffer() {
	// no se como hacer esto ¿llenar con ceros?
	keyboard_buffer_actual_position = 0;
	
}

char get_keyboard_buffer() {
	if(keyboard_buffer_actual_position == 0)
		return keyboard_buffer[KEYBOARD_BUFFER_SIZE - 1];
	return keyboard_buffer[keyboard_buffer_actual_position - 1];
}

int isLetra(int n){
	if(n >= 0x10 && n <=0x19)
		return 1;
	if(n >= 0x1E  && n <= 0x26)
		return 1;
	if(n >= 0x2C &&  n <= 0x32)
		return 1;
	return 0;
}