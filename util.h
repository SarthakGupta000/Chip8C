#include <stdint.h>
#include <stdlib.h>

struct CPU {
    uint8_t ram[4096];
    uint8_t registers[4];
    uint8_t programCounter;
    // uint8_t stackPointer;
    // uint8_t stck[16];
    // uint8_t zeroFlag;
    // uint8_t carryFlag;
};

uint8_t fetch(char *reg); // like R0 R1 R2 R3

char **splitProgram(char *program);

char **splitLine(char *line);

uint8_t execute(char **line); // split line

void run(char *program);