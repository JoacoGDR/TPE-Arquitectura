
//#include <registers.h>
#include <stdint.h>

#define ZERO_EXCEPTION_ID 0
#define INVALID_OPCODE 6
#define BLACK 0x000000
#define WHITE 0xffffff

/*
static void zero_division();
void putHexa( uint64_t * value);
void printBase(uint64_t value, uint64_t base);
uint64_t uintToBase(uint64_t value, char * buffer, uint64_t base);
*/

//static void zero_division(uint64_t * sp);
drawString(char * s, int fc, int bc); 
void drawChar2(char c, int fc, int bc);

void exceptionDispatcher(int exception, uint64_t *stackPointer);
void putHexa( uint64_t  value);
void printBase(uint64_t value, uint64_t base);
uint64_t uintToBase(uint64_t value, char * buffer, uint64_t base);


static char buffer[64] = { '0' }; // esto es para imprimir hexa



void printRegisters(uint64_t* stackPointer){
	

	 char* regs[]= {"RAX: ","RBX: ","RCX: ","RDX: ","RBP: ","RDI: ","RSI: ","R8: ","R9: ","R10: ","R11: ","R12: ","R13: ","R14: ","R15: "};

	 /*
	 stack frame tiene la direccion del
	 r15. adelante esta r14 y asi sucesivamente. uno antes de r15 esta la direccion
	 de retorno de la handler que seria el rip.
	 */

	 int j=0;
	 int i=0;
	for (i = 14, j=0; i>=0; i--, j++){
		drawChar2('\n', 0xffffff, 0x000000);
		drawString(regs[i], 0xffffff, 0x000000);
		
		putHexa(stackPointer[j]);
	}
//	newLine();
//	putStr("RIP ", colour);
//	putHexa(stackPointer[j], colour);
//	newLine();
// char* regs[]= {"R15 ","R14 ","R13 ","R12 ","R11 ","R10 ","R9 ","R8 ","RSI ","RDI ","RBP ","RDX ","RCX ","RBX ","RAX ", };
}


void exceptionDispatcher(int exception, uint64_t *stackPointer) {
	if (exception == ZERO_EXCEPTION_ID)
		drawString("DIVISION POR CERO", 0x000000, 0xffffff);

	else if(exception == INVALID_OPCODE)
		drawString("CODIGO DE OPERACION INVALIDO", 0x000000, 0xffffff);

	printRegisters(stackPointer);
}

/*static void zero_division(uint64_t *stackPointer) {
	drawString("DIVISION POR CERO", 0x000000, 0xffffff);

	
}*/


//pasar de uint64_t a hexa y de ahi imprmir en pantalla
void putHexa( uint64_t  value){ 
  	printBase(value, 16);
}

void printBase(uint64_t value, uint64_t base)
{
    uintToBase(value, buffer, base);
    drawString(buffer, WHITE,BLACK);
}


uint64_t uintToBase(uint64_t value, char * buffer, uint64_t base) {
    char *p = buffer;
    char *p1, *p2;
    uint64_t digits = 0;
    
    //Calculate characters for each digit
    do {
        uint64_t remainder = value % base;
        *p++ = (remainder < 10) ? remainder + '0' : remainder + 'A' - 10;
        digits++;
    }
    while (value /= base);
    // Terminate string in buffer.
    *p = 0;
    //Reverse string in buffer.
    p1 = buffer;
    p2 = p - 1;
    while (p1 < p2) {
        char tmp = *p1;
        *p1 = *p2;
        *p2 = tmp;
        p1++;
        p2--;
    }
    return digits;
}















/*

void exceptionDispatcher(int exception, t_stack stackPointer) {
	if (exception == ZERO_EXCEPTION_ID){
		drawString("ERROR: DIVISION POR 0");
	}
	else if(exception == OTRA_EXCEPTION_ID){
		drawString("ERROR: OTRA EXCEPCION");//esto tiene que ser otro mensaje de excepción!!!
		
	}
	printStackFrame(stackPointer); //Te pisa la IP con la IP que tenía guardada.
}
*/

/*
void printStackFrame(t_stack stackFrame) {

    for (int i = 0; i < sizeof(*stackFrame) / sizeof(uint64_t); i++){
	    drawString("\n", WHITE, BLACK);

        drawString(regs[i], WHITE, BLACK);

		drawString("\n", WHITE, BLACK);

        //putHexa(((uint64_t*)stackFrame)[i]);
    }
    drawString("\n",WHITE,BLACK);
}



/*
//pasar de uint64_t a hexa y de ahi imprmir en pantalla
void putHexa( uint64_t *  value){ 
  	printBase((uint64_t)*value, 16);
}

void printBase(uint64_t value, uint64_t base)
{
    uintToBase(value, buffer, base);
    drawString(buffer, WHITE,BLACK);
}


uint64_t uintToBase(uint64_t value, char * buffer, uint64_t base) {
    char *p = buffer;
    char *p1, *p2;
    uint64_t digits = 0;
    
    //Calculate characters for each digit
    do {
        uint64_t remainder = value % base;
        *p++ = (remainder < 10) ? remainder + '0' : remainder + 'A' - 10;
        digits++;
    }
    while (value /= base);
    // Terminate string in buffer.
    *p = 0;
    //Reverse string in buffer.
    p1 = buffer;
    p2 = p - 1;
    while (p1 < p2) {
        char tmp = *p1;
        *p1 = *p2;
        *p2 = tmp;
        p1++;
        p2--;
    }
    return digits;
}
*/