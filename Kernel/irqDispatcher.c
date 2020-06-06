#include <time.h>
#include <stdint.h>

static void int_20();
extern void timer_handler();
extern void keyboard_handler();
void int_21(uint64_t * stackPointer);



void irqDispatcher(uint64_t irq, uint64_t * stackPointer) {
	switch (irq) {
		case 0:
			int_20();
			break;
		case 1:
			int_21(stackPointer);
			break;
		
	}
	return;
}

void int_20() {   //TIMER TICK
	timer_handler();
}

void int_21(uint64_t * stackPointer) {  // TECLADO
	keyboard_handler(stackPointer);
	
}




