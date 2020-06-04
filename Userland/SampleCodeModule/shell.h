#define NUMBER_OF_COMMANDS 3

static char* commands[] = {"inforeg", "printmem", "help"};
static char* descriptions[] = {": imprime el valor de los registros", " [direccion]: volcado de memoria de 32 Bytes a partir de la direccion", ": Brinda informacion de cada comando"};


void executeCommand(int command);
int getCommand();
void help();