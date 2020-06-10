#include "calculator.h"
#include "shell.h"
#include "syscalls.h"
#include "getChar.h"


#define EQUATION_LENGTH  60

#define PRENUM          0
#define OPERATOR        1
#define NUMBER          2
#define RIGHT_P         3
#define END             4

typedef struct
{
    char stk[EQUATION_LENGTH];
    int size;
}OPERATOR_STACK;

typedef struct
{
    double stk[EQUATION_LENGTH];
    int size;
    
}NUM_STACK;


int start_VM_driver(int screen);
int error_produced = 0;

char calc_buffer[EQUATION_LENGTH] = {'0'};
int buffer_pos = 0;

char getChar();
void putChar(char * c);

int parenthesis = 0;
int last_spaces = 0;
int total_spaces = 0;



OPERATOR_STACK os;
NUM_STACK ns;

void popNumStack (double * popped) {
    if(ns.size> 0){
        *popped = ns.stk[--ns.size]; 
    }
    else {
        error_produced = 1; //se toma como syntax error ya que si estuviese bien la expresion no puede pasar
    }

}

char popOperatorStack(){
    if(os.size > 0)
        return os.stk[--os.size];
    else {
        error_produced = 1;
        return -1; 
    }
}


void pushToNumStack(double n){
    ns.stk[ns.size++] = n;
}

void pushToOperatorStack(char op){
    os.stk[os.size++] = op;

}





void calculator_main(){

    
     os.size = 0;
     ns.size = 0;

    //start_VM_driver(1);
    printf("CALCULADORA\n---------------------------------------------\n\n");
    printf("Ingrese la operacion que desea\n Solo se aceptan numeros reales, +, -, *, /, (, )\n Cualquier otra expresion no sera admitida\nPresione = al terminar\n\n");

    printf(">>");

    get_expression(); //llena el calc_buffer con todos los datos de la expresion


}



void calculate(double * result){
    double num = 0;
    int state = PRENUM;
    int i = 0;
    int signNum = 1;
    int hasPoint = 0;
    double decimalAux = 0.1;

    while(i < EQUATION_LENGTH && ! error_produced){ //lo hacemos asi ya que o se encontrara un = y se terminara, o encontrara un '\0' y saldra con error
        switch(state){
            case PRENUM: 
                    if(calc_buffer[i] == '-'){
                        signNum *= -1;
                        state = PRENUM; 
                        i++;
                    }else if(calc_buffer[i] == '+'){
                        signNum *= 1;
                        state = PRENUM;
                        i++;
                    }else if( isDigit(calc_buffer[i]) ){
                        num = calc_buffer[i] - '0';
                        state = NUMBER;
                        i++;
                    }else if(calc_buffer[i] == '.'){
                        hasPoint = 1;
                        state = NUMBER;
                        i++;
                    }else if((calc_buffer[i] == '(') && signNum > 0){
                        pushToOperatorStack('(');
                        state = PRENUM; 
                        i++;

                    
                    }else if((calc_buffer[i] == '(') && signNum < 0){
                        state = PRENUM;
                        pushToNumStack(-1);
                        pushToOperatorStack('*');
                        pushToOperatorStack('(');
                        i++;
                    }else{
                    error_produced = 1;
                    break; 
                    }
                    break;

            case NUMBER: {
                if (isDigit(calc_buffer[i])){
                    if ( hasPoint == 0){
                        num*=10;
                        num+= calc_buffer[i] - '0';
                    }
                    else{
                    
                        decimalAux *= calc_buffer[i] - '0';
                        num += decimalAux;
                        decimalAux /= 10;
                    }
                    i++;
                }
                else if (calc_buffer[i] == '.'){
                    if (hasPoint == 1){
                        error_produced = 1;
                        break;
                    }
                    hasPoint = 1;
                    i++;
                }
                else if ( isOperator(calc_buffer[i]) ){
                    num*= signNum;
                    pushToNumStack(num);
                    num=0;
                    hasPoint = 0;
                    signNum = 1;
                    double aux;
                    double op1;
                    double op2;
                    switch (calc_buffer[i]){
                        case '+' : {
                            if (os.size > 0 && os.stk[os.size - 1] != '(') {
                                popNumStack(&op2);
                                popNumStack(&op1);
                                if (error_produced == 1){
                                    break;
                                }
                                else if ( os.stk[os.size - 1] == '+' ){
                                    aux = op1 + op2;
                                }
                                else if ( os.stk[os.size - 1] == '-' ){
                                    aux = op1 - op2;
                                }
                                else if ( os.stk[os.size - 1] == '*' ){
                                    aux = op1 * op2;
                                }
                                else if ( os.stk[os.size - 1] == '/' ){
                                    aux = op1 / op2;
                                }
                                pushToNumStack(aux);
                                popOperatorStack();
                                if (error_produced == 1){
                                    break;
                                }
                            }
                            pushToOperatorStack('+');
                            break;
                        }

                        case '-' : {

                            if (os.size > 0  && os.stk[os.size - 1] != '(') {
                                popNumStack(&op2);
                                popNumStack(&op1);
                                if (error_produced == 1){
                                    break;
                                }

                                else if ( os.stk[os.size - 1] == '+' ){
                                    aux = op1 + op2;
                                }
                                else if ( os.stk[os.size - 1] == '-' ){
                                    aux = op1 - op2;
                                }
                                else if ( os.stk[os.size - 1] == '*' ){
                                    aux = op1 * op2;
                                }
                                else if ( os.stk[os.size - 1] == '/' ){
                                aux = op1 / op2;
                                }
                                pushToNumStack(aux);
                                popOperatorStack();
                                if (error_produced == 1){
                                    break;
                                }
                            }
                            pushToOperatorStack('-');
                            break;
                        }

                        case '*' :{
                            
                            if (os.size > 0 && os.stk[os.size - 1] != '+' && os.stk[os.size - 1] != '-'  && os.stk[os.size - 1] != '(') {
                                popNumStack(&op2);
                                popNumStack(&op1);
                                if (error_produced == 1){
                                    break;
                                }

                            else if ( os.stk[os.size - 1] == '*' ){
                                    aux = op1 * op2;
                                }

                            else if ( os.stk[os.size - 1] == '/' ){
                                    aux = op1 / op2;
                                }
                                popOperatorStack();
                                pushToNumStack(aux);
                                if (error_produced == 1){
                                    break;
                                }
                            }
                        pushToOperatorStack('*'); 
                        break;
                        }

                        case '/' : {
                        
                            if (os.size > 0 && os.stk[os.size - 1] != '+' && os.stk[os.size - 1] != '-'  && os.stk[os.size - 1] != '(') {

                                popNumStack(&op2);
                                popNumStack(&op1);
                                if (error_produced == 1){
                                break;
                                }

                            else if ( os.stk[os.size - 1] == '*' ){
                                    aux = op1 * op2;
                                }

                                else if ( os.stk[os.size - 1] == '/' ){
                                    aux = op1 / op2;
                                }
                                popOperatorStack();
                                pushToNumStack(aux);
                                if (error_produced == 1){
                                break;
                                }
                            }
                        pushToOperatorStack('/'); 
                        break;
                        }
                            
                    }
                    state = OPERATOR;
                    i++;
                }
                else if (calc_buffer[i] == ')'  && os.stk[os.size - 1] != '('){
                    num*= signNum;
                    pushToNumStack(num);
                    num=0;
                    hasPoint = 0;
                    signNum = 1;
                    state = RIGHT_P;
                    i++;
                }
                
                else if (calc_buffer[i] == '='){
                    num *= signNum;
                    pushToNumStack(num);
                    state = END;
                }
                break;
            }
            

            case OPERATOR: {
                if (calc_buffer[i] == '+'){
                    signNum = 1;
                    i++;
                    state = PRENUM;
                }
                else if (calc_buffer[i] == '-'){
                    signNum = -1;
                    i++;
                    state = PRENUM;
                }
                else if (calc_buffer[i] == '('){
                    pushToOperatorStack('(');
                    signNum = 1;
                    i++;
                    state = PRENUM;
                }
                else if(isDigit(calc_buffer[i])){
                    num = calc_buffer[i] - '0';
                    i++;
                    state = NUMBER;
                }else{
                    error_produced = 1;
                }
                break;
            }   
            
            case RIGHT_P : {
                char operator;
                double op2;
                double op1;
                double aux;
            
                for (char c = popOperatorStack(); c != '(' ; c = popOperatorStack() ){
                    popNumStack(&op2);
                    popNumStack(&op1);
                    if (error_produced == 1){
                    break;
                    }

                else if (c == '+'){
                        aux = op1 + op2;
                    }
                    else if (c == '-'){ 
                        aux = op1 - op2;
                    }
                    else if (c == '*'){
                        aux = op1 * op2;
                    }
                    else if (c == '/'){
                        aux = op1 / op2;
                    }
                pushToNumStack(aux);
                }
                if (error_produced == 1){
                    break;
                }

                if (calc_buffer[i] == '='){
                    state = END;
                }
                else if ( isOperator(calc_buffer[i]) ){
                    switch (calc_buffer[i]){
                        case '+' : {
                            if (os.size > 0) {
                                popNumStack(&op2);
                                popNumStack(&op1);
                                if (error_produced == 1){
                                    break;
                                }
                                else if ( os.stk[os.size - 1] == '+' ){
                                    aux = op1 + op2;
                                }
                                else if ( os.stk[os.size - 1] == '-' ){
                                    aux = op1 - op2;
                                }
                                else if ( os.stk[os.size - 1] == '*' ){
                                    aux = op1 * op2;
                                }
                                else if ( os.stk[os.size - 1] == '/' ){
                                    aux = op1 / op2;
                                }
                                pushToNumStack(aux);
                                popOperatorStack();
                                if (error_produced == 1){
                                    break;
                                }
                            }
                            pushToOperatorStack('+');
                            break;
                        }

                        case '-' : {

                            if (os.size > 0) {
                                popNumStack(&op2);
                                popNumStack(&op1);
                                if (error_produced == 1){
                                    break;
                                }
                                else if ( os.stk[os.size - 1] == '+' ){
                                    aux = op1 + op2;
                                }
                                else if ( os.stk[os.size - 1] == '-' ){
                                    aux = op1 - op2;
                                }
                                else if ( os.stk[os.size - 1] == '*' ){
                                    aux = op1 * op2;
                                }
                                else if ( os.stk[os.size - 1] == '/' ){
                                    aux = op1 / op2;
                                }
                                pushToNumStack(aux);
                                popOperatorStack();
                                if (error_produced == 1){
                                    break;
                                }
                            }
                            pushToOperatorStack('-');
                            break;
                        }

                        case '*' :{
                            if (os.size > 0 && os.stk[os.size - 1] != '+' && os.stk[os.size - 1] != '-') {
                                popNumStack(&op2);
                                popNumStack(&op1);
                                if (error_produced == 1){
                                    break;
                                }

                            else if ( os.stk[os.size - 1] == '*' ){
                                    aux = op1 * op2;
                                }

                                if ( os.stk[os.size - 1] == '/' ){
                                aux = op1 / op2;
                                }
                                popOperatorStack();
                                pushToNumStack(aux);
                                if (error_produced == 1){
                                    break;
                                }
                            }
                        pushToOperatorStack('*'); 
                        break;
                        }

                        case '/' : {
                        
                            if (os.size > 0 && os.stk[os.size - 1] != '+' && os.stk[os.size - 1] != '-') {

                                popNumStack(&op2);
                                popNumStack(&op1);
                                if (error_produced == 1){
                                    break;
                                }

                                else if ( os.stk[os.size - 1] == '*' ){
                                    aux = op1 * op2;
                                }

                            else if ( os.stk[os.size - 1] == '/' ){
                                    aux = op1 / op2;
                                }
                                popOperatorStack();
                                pushToNumStack(aux);
                                if (error_produced == 1){
                                    break;
                                }
                            }
                        pushToOperatorStack('/'); 
                        break;
                        }
                            
                    }
                    state = OPERATOR;
                    i++;
                }
                else if (calc_buffer[i] != ')'){
                    error_produced = 1;
                }
                break;
                
            }

            case END : {
                double op2;
                double op1;
                double aux;
                if (ns.size > 1){
                    while(os.size > 0){
                    char c = popOperatorStack();
                    
                        popNumStack(&op2);
                        popNumStack(&op1);
                        if (error_produced == 1){ 
                            break;
                        }
                        else  if (c == '+'){
                            aux = op1 + op2;
                        }
                        else if (c == '-'){
                            aux = op1 - op2;
                        }
                        else if (c == '*'){
                            aux = op1 * op2;
                        }
                        else if (c == '/'){
                            aux = op1 / op2;
                        }
                        pushToNumStack(aux);
                    }
                }
                if (ns.size == 1 && os.size == 0){
                    popNumStack(result); //no puede tirar error porque si está vacío no entra al if
                }
                else {
                    error_produced = 1;
                }
                return;
            }

        }

        
    }
    return;
}















void get_expression(){
    double resp;
    char * c;
    while(1){
		
	    c = getChar();

        if(c == -2){
            start_VM_Driver(0);
            start_shell();
        }

		if(c != -1){
    
            if(c == '\b'){
                //Si lo que borro es un espacio, solo borro el espacio, mi buffer no es afectado, ya que los espacios no se guardan en este.
                if(last_spaces != 0){
                    last_spaces--;
                    total_spaces--;
                    putChar(&c);
                }

                else if(buffer_pos != 0){
                    calc_buffer[buffer_pos] = '\0';
                    buffer_pos--;   
                     putChar(&c);
                     if(isParenthesisLeft(calc_buffer[buffer_pos])){
                         parenthesis--;
                     }else if(isParenthesisRight(calc_buffer[buffer_pos])){
                         parenthesis++;
                     }

                }
            }

            else if(c == 'c'){
                
                syscall_clearView();
            }


            else if(c == '=' ){

                calc_buffer[buffer_pos++] = '=';
                calc_buffer[buffer_pos] = '\0';
                
                putChar("\n"); 

                if(parenthesis != 0){
                    printf("Syntax Error\n");
                }else{
                    calculate(&resp);
                }

                if(error_produced == 1){
                    printf("Syntax Error\n");
                }
                else {
                    print_answer(resp);
                }
                

               buffer_pos = 0;
               total_spaces = 0;
               last_spaces = 0;
               error_produced = 0;
               printf("\n>>");
                
                
            }
            else if((buffer_pos + total_spaces) < EQUATION_LENGTH){
                if(isValid(c)){
                     calc_buffer[buffer_pos] = c;
                     buffer_pos++;
                     putChar(&c);
                }else if(c == ' '){
                    putChar(&c); //Ponemos el espacio, pero no lo guardamos en ningun lado
                    last_spaces++;
                    total_spaces++;
                }
                
            }
           
           
        }
    }
}

int isDigit(int c)
{
    if (c >= '0' && c <= '9')
        return c;
    else
        return 0;
}

//Nos piden con 4 decimales
void print_answer(double ans){
    int ansInt = ans; //obtengo la parte entera
    int ansDec1 = (ans - ansInt) * 10;
    int ansDec2 = (int) ((ans - ansInt) * 100) %10;
    int ansDec3 = (int)((ans - ansInt) * 1000) %10;
    int ansDec4 = (int)((ans - ansInt) * 10000) %10;
    printInt(ansInt);
    if (ansDec4 != 0){
        printf(".");
        printInt(ansDec1);
        printInt(ansDec2);
        printInt(ansDec3);
        printInt(ansDec4);
    }

}

void intToString(int n, char * string){
    char buffer[50];
    int i = 0;
    int j = 0;

    if(n == 0){
        string[0] = '0';
        string[1] = '\0';
    }else{
        while(n != 0){
            buffer[i++] = n%10 +'0';
            n=n/10;
        }
        if(n < 0){
            buffer[i++] = '-';
        }

        buffer[i] = '\0';

        for(; i >= 0; i++){
            string[j++] = buffer[i];
        }
    }
}





int isValid(char c){
    if(c >= '0' && c <= '9')
        return 1;
    else if ( c =='*' || c == '/' || c == '-' || c == '+' || c == '.' || c == '=')
        return 1;
    else if(c == '('){
        parenthesis++;
        return 1;
    }

    else if(c == ')'){
        parenthesis--;
        return 1;
    }
        
    return 0;
}

int isParenthesisLeft(char c){
    return c == '(';
}


int isParenthesisRight (char c){
    return c == ')';
}

int isOperator (char c){
    int answ = (c == '+') || (c == '-') || (c == '*') || (c == '/');
    return answ;
}
