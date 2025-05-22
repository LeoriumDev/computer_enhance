#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>

const char* reg_names_byte[8] = {
    "al", "cl", "dl", "bl", "ah", "ch", "dh", "bh"
};

const char* reg_names_word[8] = {
    "ax", "cx", "dx", "bx", "sp", "bp", "si", "di"
};

void disassembler(uint8_t* bytes) {
    uint8_t opcode = bytes[0] >> 2;
    bool direction = bytes[0] & 0x02;
    bool word_size = bytes[0] & 0x01;

    uint8_t mod = bytes[1] >> 6;
    uint8_t reg = bytes[1] >> 3 & 0x07;
    uint8_t rm = bytes[1] & 0x07;

    char instruction[10] = {};
    char source[10] = {};
    char destination[10] = {};

    if (opcode == 0b100010) {
        strcpy(instruction, "mov");
    }

    if (mod == 0b11) {
        if (word_size) {
            strcpy(source, reg_names_word[reg]);
            strcpy(destination, reg_names_word[rm]);
        } else {
            strcpy(source, reg_names_byte[reg]);
            strcpy(destination, reg_names_byte[rm]);
        }
    }

    if (direction) {
        char temp[10] = {};
        strcpy(temp, source);
        strcpy(source, destination);
        strcpy(destination, temp);
    }

    printf("%s %s, %s\n", instruction, destination, source);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: ./<binaries> <file to disassemble>\n");
        exit(EXIT_FAILURE);
    }

    FILE* file;
    char* filename = argv[1];
    file = fopen(filename, "r");
    if (!file) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    printf("; %s disassembly:\nbits 16\n\n", filename);

    /* 8086/8088 Machine Instruction Format (Excerpt)
     *
     * BYTE 1
     * 1-6 OPCODE (operation/instruction code)
     * 7   D      (direction is to/from register, 
     *             1 means REG is the destination,
     *             0 means REG is the source)
     * 8   W      (word/byte operation, 0 = byte and 1 = word)
     *
     * BYTE 2
     * 1-2 MOD (register/memory mode with displacement length)
     * 3-5 REG (register operand / extension of opcode)
     * 6-8 R/M (register operand / registers to use in EA calculation)
     */
    uint8_t bytes[2];
    while (fread(bytes, 1, 2, file) == 2)
        disassembler(bytes);
    fclose(file);
    return 0;
}