/**
 * @file Instruction_DataTypes.h
 * @author Sanjeeve R (18euee122@skcet.ac.in)
 * @brief  Header file to contain the user defined data types used in the project
 * @version 0.1
 * @date 2022-03-30
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef INSTRUCTION_DATATYPES_H
#define INSTRUCTION_DATATYPES_H

//New Data Type for Instruction
struct Instruction{ 
    char OPCODE[6];
    int index;
    int hex_value;
    int machine_cycles;
    int size;
};

extern struct Instruction Instruction_List[46];

#endif