#define NUMBER_OF_COMMANDS 9

static char* commands[] = {"inforeg", "printmem", "help", "testDiv0", "testInvalidOpcode","time", "temp","clear", "brand"};
static char* descriptions[] = {": imprime el valor de los registros\n                 Presione TAB para guardarlos", " [direccion]: volcado de memoria de 32 Bytes\n            a partir de la direccion dada", 
                        ": Brinda informacion de cada comando", ": Excepcion de dividir por 0, printea los registros", ": Excepcion de codigo de operacion invalida. Printea registors",": Imprime el tiempo", ": Imprime la temperatura"
                        ,": Limpia la pantalla", ": Imprime la marca y modelo del procesador"};
void shell_main();

void executeCommand(int command);
int getCommand();
void help();