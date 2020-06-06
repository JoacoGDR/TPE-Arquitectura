#define NUMBER_OF_COMMANDS 5

static char* commands[] = {"inforeg", "printmem", "help", "testDiv0", "testInvalidOpcode"};
static char* descriptions[] = {": imprime el valor de los registros", " [direccion]: volcado de memoria de 32 Bytes a partir de la direccion", ": Brinda informacion de cada comando", ": Excepcion de dividir por 0, printea los registros", ": Excepcion de codigo de operacion invalida. Printea registors"};


void executeCommand(int command);
int getCommand();
void help();