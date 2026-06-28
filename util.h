#include <stdint.h>
#include <stdlib.h>
#define STRING_VAR(variable) #variable // converts enum

const int instNum = 4;
char *instructionMap[instNum] = {
    "MOV",
    "ADD",
    "SUB",
    "JMP"
};

struct CPU {
    uint8_t ram[4096];
    uint8_t registers[4];
    uint8_t programCounter;
    // uint8_t stackPointer;
    // uint8_t stck[16];
    // uint8_t zeroFlag;
    // uint8_t carryFlag;
};

uint8_t fetch(char *reg, struct CPU *cpu); // like R0 R1 R2 R3 and also all 1 byte integers

char **splitProgram(char *program, size_t len);

char **splitLine(char *line);

uint8_t execute(char **line, struct CPU *cpu); // split line as input

void run(char *program);