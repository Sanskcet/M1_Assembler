/**
 * @file Instruction_Process_Methods.h
 * @author Sanjeeve R (18euee122@skcet.ac.in)
 * @brief Header file to declare functions required for processing instructions
 * @version 0.1
 * @date 2022-03-30
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef INSTRUCTION_PROCESS_H
#define INSTRUCTION_PROCESS_H

#include "Instruction_DataTypes.h"
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

char nibble_to_hex(int temp);
char* inttohex(int Hex_Code);
char* Read_Instruction(FILE *code,char* inst);
void Read_Opcode(char inst[],char* Opcode);
void Read_Operand(char inst[],char* Operand_1);
void shiftStringLeft(char inst[],int i);
int get_Number_of_Operands(char* Opcode);
void Remove_Leading_Whitespaces(char inst[]);

int process_Hex_Code_0(char Operand_0[],char Operand_1[],char Operand_2[],int k);
char* process_Hex_Code_1(char Operand_0[],char Operand_1[],char Operand_2[],int k);
char* process_Hex_Code_2(char Operand_0[],char Operand_1[],char Operand_2[],int k,int Number_of_Operands);
int match_Opcode(char Operands[]);

#endif