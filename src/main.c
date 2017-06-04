#include <stdio.h>
#include <stdlib.h>

#include "../assembler/main.h"

#define byte char
#define MEM_LIM 64*1024

typedef struct {
byte op;
byte arg;
} inst;

typedef struct {
    byte a;
    byte x;
    inst ir;
    byte sp;
    byte pc;
    byte r1;
    byte r2;
    byte r3;
    byte r4;
    byte *memory;
    byte *in_memory;
    byte *out_memory;
} machine;

byte add(byte a, byte b) {
    return a+b;
}

byte sub(byte a, byte b) {
    return a-b;
}

int assemble(FILE *fp) {
while () {

}
}

int main() {
    printf("Romulus10's 8-bit machine.");
    machine mech = (machine) {
        .a = 0,
        .x = 0,
        .ir = 0,
        .sp = 0,
        .pc = 0,
        .r1 = 0,
        .r2 = 0,
        .r3 = 0,
        .r4 = 0,
        .memory = malloc(MEM_LIM*sizeof(byte)),
        .in_memory = malloc(MEM_LIM*sizeof(byte)),
        .out_memory = malloc(MEM_LIM*sizeof(byte))
    };
    return 0;
}