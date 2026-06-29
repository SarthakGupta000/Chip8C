#include "util.h"

char *program = "MOV R0 5 \nMOV R1 10 \nADD R0 3 \nJMP 5 \nMOV R2 27 \nHLT \n";

int main() {
    run(program, 6);
}