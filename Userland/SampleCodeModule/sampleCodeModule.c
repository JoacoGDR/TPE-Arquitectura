/* sampleCodeModule.c */

/**
 * Comentario para masomenos entender la logica de como se trabaja:
 * start_VM_Driver():
*	Funcion de libasm
*	realiza una int 0x82
*	en 0x82, cargamos (con el IDTloader) la interrupcion que hara que se llame a init_VM_Driver()
*	el cual luego llama a init_screen_driver()
*	Entonces de esta forma no estamos llamando directamente funciones del kernel asi como asi.
*
*/
extern void start_VM_Driver(); //Se encuentra en libasm.asm (de userland)
extern void syscall_write(char *, int);
void putchar(char * c);
char getChar();

int main() {
	// init_VM_Driver(); Esta es una funcion de Kernel, no deberia llamarla desde aca

	syscall_write("", 0);
	start_VM_Driver();
	syscall_write("hol", 3);
	
	char * c;
	while(1){


		//syscall_write(getChar(), 1);
	    c = getChar();
		if(c != -1)
			putChar(&c);

	}
	
	
	

	




	//start_window_A(); ponele que siempre arrancamos en la window A que es la del shell
	/*
		Entonces armamos un shell que tenga sus cosas, la linea para escribir comandos, que interprete dichos comandos y haga lo que se le pida
		Y quiza, en todo momento, arriba en la pantalla poner:
		"PARA CAMBIAR A LA OTRA VENTANA APRIETE: ctrl + 1, ctrl + 2"
		(Se me ocurre): Deberiamos guardarnos el estado en el que queda, osea estoy en la shell, tiro 4 instrucciones, voy
						a la caluladora, hago un calculo, vuelvo a la shell y quiero ver que las 4 instrucciones siguen ahi escritas
						y si vuelvo a la calculadora quiero que la cuenta siga ahi.




		En la calculadora tambien ponemos esto, y ademas ponemos las instrucciones para usar la calculadora:
		(se me ocurre): "Escriba la formula, solo se admiten numeros, (), *, %, +, - y '.'  " (lo de decimales luego lo vemos).
		seguido de un "=", y presione "enter". El resultado se mostrara en la casilla "RESULTADO".
		"Presione ctrl + backspace para borrar limpiar todo" (o cualquier otra tecla que definamos nosotros);

		Que hacemos internamente?
			Nos guardamos esa linea escrita.
			la parseamos y vamos viendo que los datos sean solo los admitidos
			hacemos el calculo respetando parentesis "()" y las precedencias correctas
			y luego imprimimos este valor en la posicion de "RESULTADO" predeterminada por nosotros.
	*/

	return 1;
}