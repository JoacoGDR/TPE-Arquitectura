extern void syscall_read(int, char*, int);
extern void syscall_write(char *, int);

char getChar() {
    char resp;
    syscall_read(2/*STD_INPUT*/, &resp, 1);
    return resp;
} 

void putChar(char * c){
    syscall_write(c, 1);
}

void print(char * string){
    while(*string){
        putChar(*string);
    }
}