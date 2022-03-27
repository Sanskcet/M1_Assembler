#ifndef INSTRUCTION_PROCESS_H
#define INSTRUCTION_PROCESS_H

#include<stdio.h>
#include "Instruction_DataTypes.h"
#include<stdbool.h>

char* Read_Instruction(FILE *code,char* inst);
void Read_Opcode(char inst[],char* Opcode);
void Read_Operand(char inst[],char* Operand_1);
void shiftStringLeft(char inst[],int i);
int get_Number_of_Operands(char* Opcode);
void Remove_Whitespaces(char inst[]);

int process_Hex_Code_0(char Operand_0[],char Operand_1[],char Operand_2[],int k);
char* process_Hex_Code_1(char Operand_0[],char Operand_1[],char Operand_2[],int k);
char* process_Hex_Code_2(char Operand_0[],char Operand_1[],char Operand_2[],int k);
int match_Opcode(char Operands[]);

#endif