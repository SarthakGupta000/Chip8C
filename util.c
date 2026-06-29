#include "util.h"

const int instNum = 4;
char *instructionMap[4] = {
    "MOV",
    "ADD",
    "SUB",
    "JMP"
};

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

char **splitProgram(char *program, size_t len) { // program must end in \n with \n between lines
    int numOfLines = 0;
    for (int i = 0; i < len - 1; i++) {
        if (program[i] == '\n') {
            numOfLines++;
        }
    }
    if (numOfLines == 0) {
        return NULL;
    }
    char **split = (char **) malloc(sizeof(char *) * numOfLines);
    for (int i = 0; i < numOfLines; i++) {
        split[i] = (char *) malloc(sizeof(char) * 25);
        for (int j = 0; j < 25; j++) {
            split[i][j] = '~';
        }
        split[i][24] = '\0';
    }
    int splitPointer = 0;
    int previous = -1; // drops back to next char which is *program
    for (int current = 0; current < len; current++) {
        if (program[current] == '\n') {
            int currentChar = 0;
            for (int buffer = (previous + 1); buffer < current; buffer++) {
                split[splitPointer][currentChar] = program[buffer];
                currentChar++;
            }
            split[splitPointer][currentChar] = '\0';
            splitPointer++;
            previous = current;
        }
    }
    return split;
}

char **splitLine(char *line, size_t len) { // line must end in space
    int numOfWords = 0;
    for (int i = 0; i < len - 1; i++) {
        if (line[i] == ' ') {
            numOfWords++;
        }
    }
    if (numOfWords == 0) {
        return NULL;
    }
    char **split = (char **) malloc(sizeof(char *) * numOfWords);
    for (int i = 0; i < numOfWords; i++) {
        split[i] = (char *) malloc(sizeof(char) * 25);
        for (int j = 0; j < 10; j++) {
            split[i][j] = '~';
        }
        split[i][(10 - 1)] = '\0';
    }
    int splitPointer = 0;
    int previous = -1; // drops back to next char which is *program
    for (int current = 0; current < len; current++) {
        if (line[current] == ' ') {
            int currentChar = 0;
            for (int buffer = (previous + 1); buffer < current; buffer++) {
                split[splitPointer][currentChar] = line[buffer];
                currentChar++;
            }
            split[splitPointer][currentChar] = '\0';
            splitPointer++;
            previous = current;
        }
    }
    return split;
}

void execute(char **line, struct CPU *cpu, size_t numOfLines) {
    int val;
    int inst = -1;
    for (int i = 0; i < instNum; i++) {
        val = 0;
        for (int j = 0; j < 3; j++) {
            if (instructionMap[i][j] == line[0][j]) {
                val++;
            }
        }
        if (val == 3) {
            inst = i;
        }
    }
    if (inst == -1) {
        return;
    }
    // MOV
    if (strcmp(instructionMap[inst], "MOV") == 0) {
        if (line[1][0] != 'R') {
            return;
        }
        int reg;
        if (line[1][1] == '0') {
            reg = 0;
        }
        else if (line[1][1] == '1') {
            reg = 1;
        }
        else if (line[1][1] == '2') {
            reg = 2;
        }
        else if (line[1][1] == '3') {
            reg = 3;
        }
        else {
            return;
        }
        cpu->registers[reg] = fetch(line[2], cpu);
    }
    // ADD
    if (strcmp(instructionMap[inst], "ADD") == 0) {
        if (line[1][0] != 'R') {
            return;
        }
        int reg;
        if (line[1][1] == '0') {
            reg = 0;
        }
        else if (line[1][1] == '1') {
            reg = 1;
        }
        else if (line[1][1] == '2') {
            reg = 2;
        }
        else if (line[1][1] == '3') {
            reg = 3;
        }
        else {
            return;
        }
        cpu->registers[0] += fetch(line[2], cpu);
    }
    // SUB
    if (strcmp(instructionMap[inst], "SUB") == 0) {
        if (line[1][0] != 'R') {
            return;
        }
        int reg;
        if (line[1][1] == '0') {
            reg = 0;
        }
        else if (line[1][1] == '1') {
            reg = 1;
        }
        else if (line[1][1] == '2') {
            reg = 2;
        }
        else if (line[1][1] == '3') {
            reg = 3;
        }
        else {
            return;
        }
        cpu->registers[0] -= fetch(line[2], cpu);
    }
    // JMP
    if (strcmp(instructionMap[inst], "JMP") == 0) {
        if (fetch(line[1], cpu) >= numOfLines) {
            return;
        }
        cpu->programCounter = fetch(line[1], cpu);
    }
}

void run(char *program, size_t numOfLines) {
    struct CPU *cpu = (struct CPU *) malloc(sizeof(struct CPU));
    cpu->programCounter = 0;
    for (int i = 0; i < 4; i++) {
        cpu->registers[i] = 0;
    }
    for (int i = 0; i < 4096; i++) {
        cpu->ram[i] = 0; // not in use yet
    }
    char **lines = splitProgram(program, (strlen(program) + 1));
    char ***split = (char ***) malloc(numOfLines * sizeof(char **));
    for (int i = 0; i < numOfLines; i++) {
        split[i] = splitLine(lines[i], (strlen(lines[i]) + 1));
    }
    while (cpu->programCounter < numOfLines) {
        if (strcmp("HLT", split[cpu->programCounter][0]) == 0) {
            return;
        }
        execute(split[cpu->programCounter], cpu, numOfLines);
        for (int i = 0; i < 4; i++) {
            printf("%d ", cpu->registers[i]);
        }
        printf("%d", cpu->programCounter);
        cpu->programCounter++;
        printf("\n");
    }
    free(lines);
    for (int i = 0; i < numOfLines; i++) {
        int j = 0;
        while (split[i][j] != NULL) { 
            free(split[i][j]); // Free individual words
            j++;
        }
        free(split[i]);
    }
    free(cpu);
}