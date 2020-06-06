#include <screen_driver.h>
#include <keyboard.h>

#define STD_OUTPUT 1  // salida por pantalla
#define STD_INPUT 2
#define TIMER 3

/*char get_keyboard_buffer();
int keyboard_buffer_is_empty();*/

//extern int segundos();
//extern int minutos();
//extern int horas();

void syscall_dispatcher(int ID, int file_descriptor, char* string, int length){
	char aux2;
	int aux;
	switch(ID){
		case 4:{
			switch(file_descriptor){
				case STD_OUTPUT:{
					drawString(string, 0xFFFFFF, 0x000000); 
				}
			}
			break;
		}
		case 3:{
			aux = keyboard_handler(); 
			switch(file_descriptor) {
				case STD_INPUT:{
					if(aux == 1){
						aux2 = get_keyboard_buffer(); 
						string[0] = aux2;
					} else {
						string[0] = -1;
					}
					break;
				}
				//case TIMER:{
				//	int seg = segundos();
				//	int min = minutos();
				//	int hora = horas();
				//	string[0]=hora/10 + 0x30; string[1]=hora%10 + 0x30;
				//	string[3]=min/10 + 0x30; string[4]=min%10 + 0x30;
				//	string[6]=seg/10 + 0x30; string[7]=seg%10 + 0x30;
				//	break;
				//}
			}
			break;
		}
		case 2:{
			switch(file_descriptor){
				case STD_OUTPUT:{
					drawString("Imprimiendo informacion de los registros: \n",0xfffff,0x0000);
					printRegs(); //hay que hacerlo. 
				break;
				}

			}
			break;
		}
	}
}

