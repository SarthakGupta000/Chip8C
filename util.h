#include <stdint.h>
#include <string.h>
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
    // uint8_t stack[16];
    // uint8_t zeroFlag;
    // uint8_t carryFlag;
};

uint8_t fetch(char *reg, struct CPU *cpu); // like R0 R1 R2 R3 and also all 1 byte integers

char **splitProgram(char *program, size_t len);

char **splitLine(char *line, size_t len);

void execute(char **line, struct CPU *cpu, size_t numOfLines); // split line as input

void run(char *program, size_t numOfLines);