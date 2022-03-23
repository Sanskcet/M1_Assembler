#ifndef INSTRUCTION_DATATYPES_H
#define INSTRUCTION_DATATYPES_H

//New Data Type for Instruction
struct Instruction{ 
    char OPCODE[6];
    int hex_value;
    int machine_cycles;
    int size;
};

extern struct Instruction Instruction_List[46];

#endif