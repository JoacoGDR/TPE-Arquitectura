#include "shell.h"



#define SCREEN_LIMIT 120

void inforeg();
int screen_width;
int screen_height;
char buffer[SCREEN_LIMIT] = {'\0'};
int buffer_size = 0;
int getCommand();
void executeCommand(int command);
int strcmp();
char getChar();
void putChar(char * c);
void get_temp();

void start_shell(/*int width, int height*/){
    //screen_width = width;
   // screen_height = height;
    
    syscall_write(">>", 2);
    

    shell_main();

}
//Problema actual: si borro despues al apretar enter, me tira con las letras borradas...
void shell_main(){
	char * c;
	while(1){
		//syscall_write(getChar(), 1);
	    c = getChar();
		if(c != -1){
            get_temp();
            if(c == '\b'){
                if(buffer_size != 0){
                    buffer[buffer_size] = '\0';
                    buffer_size--;   
                     putChar(&c);

                }
            }
            else if(c=='\n'){
            
                buffer[buffer_size] = '\0';
                
                putChar(&c); //tiro un enter y despues me fijo de printear lo que sigue, pasaba que ponia todo junto y despues largaba un enter.

                //los commands se guardan en un arreglo, entonces nos devuelve la posicion de dicho command QUE QUERES?!
                int command = getCommand();
                if(command != -1){
                    executeCommand(command);
                    
                }else
                {
                    syscall_write("Command not found\n", 18);
                }
                buffer_size = 0; 
                 syscall_write(">>", 2);
                
                
            }
            else if(buffer_size < SCREEN_LIMIT){
                buffer[buffer_size] = c;
                buffer_size++;
                 putChar(&c);
            }
            //putChar(&c); este no lo uso y lo pongo en todos salvo el enter por que? -> porque sino cuando hago un enter, me lo tira y el ">>" queda volando y ta todo mal.
           
        }
 
    }
}

int getCommand(){
    for(int i = 0; i < NUMBER_OF_COMMANDS; i++){
        if(strcmp(commands[i], buffer) == 1) {
            return i;
        }
    }
    return -1;
    }



//retorna 1 si son iguales
int strcmp(char * str1, char*str2){
    int i= 0;
    for(i; str1[i] || str2[i]; i++){
        if(str1[i] != str2[i])
            return 0;
    }
    if(str1[i] != str2[i])
        return 0;
    return 1;
}



void executeCommand(int id){
    switch(id){
        case 0:
            inforeg();
    }
}

