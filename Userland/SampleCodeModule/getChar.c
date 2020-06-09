#include "syscalls.h"
#include "getChar.h"


char getChar() {
    char resp;
    syscall_read(2/*STD_INPUT*/, &resp, 1);
    return resp;
} 

void putChar(char * c){
    syscall_write(c);
}

void printf(char * string){
    syscall_write(string);
}