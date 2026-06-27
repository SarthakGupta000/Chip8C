#include <stdint.h>
#include <stdlib.h>
#define STRING_VAR(variable) #variable // converts enum

enum Instructions { // o signifies empty space to keep it in 3 bytes
    MOV,
    ADD,
    SUB,
    JMP,
};

int instructionMap[4][3];

struct CPU {
    uint8_t ram[4096];
    uint8_t registers[4];
    uint8_t programCounter;
    // uint8_t stackPointer;
    // uint8_t stck[16];
    // uint8_t zeroFlag;
    // uint8_t carryFlag;
};

void mapInstructions();

uint8_t fetch(char *reg); // like R0 R1 R2 R3 and also all 1 byte integers

char **splitProgram(char *program);

char **splitLine(char *line);

uint8_t execute(char **line); // split line as input

void run(char *program);