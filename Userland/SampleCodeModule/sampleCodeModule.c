/* sampleCodeModule.c */


extern void start_VM_Driver(int screenId); //Se encuentra en libasm.asm (de userland)
void putchar(char * c);
char getChar();
void start_shell();
void get_temp();
int do_intel(void);
int do_amd(void);
void printregs(int eax, int ebx, int ecx, int edx);
void getCpuID();
void calculator_main();



extern void get_brand();

int main() {

	syscall_write("");

	start_VM_Driver(0);

	syscall_write("Welcome to the Benson OS!\n");
	syscall_write("Press TAB to save registers!\n");
	syscall_write("Press left shift to switch between screens\n");
	syscall_write("The terminal will be initiated first.\n");
	
	start_shell();


	return 1;
}