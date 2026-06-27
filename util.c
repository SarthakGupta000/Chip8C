#include "util.h"

uint8_t fetch(char *reg, struct CPU *cpu) {
    if (reg[0] == 'R') {
        if (reg[1] == '0') {
            return cpu->registers[0];
        } else if (reg[1] == '1') {
            return cpu->registers[1];
        } else if (reg[1] == '2') {
            return cpu->registers[2];
        } else if (reg[1] == '3') {
            return cpu->registers[3];
        } else {
            return -1;
        }
    }
    char numList[10] = {
        '0',
        '1',
        '2',
        '3',
        '4',
        '5',
        '6',
        '7',
        '8',
        '9',
    };
    int var = 0;
    for (int i = 0; i < 10; i++) {
        if (numList[i] == reg[0]) {
            var = 1;
            break;
        }
    }
    if (var == 1) {
        return atoi(reg);
    }
    return -1;
}