#include <screen_driver.h>
#include <keyboard.h>


#define STD_OUTPUT 1  // salida por pantalla
#define STD_INPUT 2
#define TIMER 3

#define READ 3
#define WRITE 4
#define CLEAR_VIEW 6
#define REGISTERS 2



extern int seconds();
extern int minutes();
extern int hours();

void syscall_dispatcher(int ID, int file_descriptor, char* string, int length){ 
	char aux2;
	int aux;
	switch(ID){
		
		case CLEAR_VIEW:{
			clearScreenDisplay();break;
		}


		case WRITE:{
			switch(file_descriptor){
				case STD_OUTPUT:{
					drawString(string, 0xFFFFFF, 0x000000); 
				}

			}
			break;
		}
		case READ:{
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
				case TIMER:{
					int sec = seconds();
					int min = minutes();
					int hour = hours();
					string[0]=hour/10 + 0x30; string[1]=hour%10 + 0x30;
					string[3]=min/10 + 0x30; string[4]=min%10 + 0x30;
					string[6]=sec/10 + 0x30; string[7]=sec%10 + 0x30;
					break;
				}
			}
			break;
		}
		case REGISTERS:{
			switch(file_descriptor){
				case STD_OUTPUT:{
					drawString("Imprimiendo informacion de los registros: \n",0xfffff,0x0000);
					printRegs();  
				break;
				}

			}
			break;
		}
	}
}

