#include <stdint.h>

typedef struct t_stackCDT {
    uint64_t r15;
    uint64_t r14;
    uint64_t r13;
    uint64_t r12;
    uint64_t r11;
    uint64_t r10;
    uint64_t r9;
    uint64_t r8;

    uint64_t rsi;
    uint64_t rdi;
    uint64_t rbp;

    uint64_t rdx;
    uint64_t rcx;
    uint64_t rbx;
    uint64_t rax;

    uint64_t gs;
    uint64_t fs;

// iret 
    uint64_t rip;
    uint64_t cs;
    uint64_t rflags;
    uint64_t rsp;
    uint64_t ss;
} t_stackCDT;

typedef t_stackCDT* t_stack;


char* regs[]= {"R15 ","R14 ","R13 ","R12 ","R11 ","R10 ","R9 ","R8 ","RSI ","RDI ","RBP ","RDX ","RCX ","RBX ","RAX ", "GS ", "FS ", "RIP ", "CS ", "RFLAGS ", "RSP ", "SS "};
