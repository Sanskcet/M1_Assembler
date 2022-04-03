/**
 * @file Instruction_Process_Methods.c
 * @author Sanjeeve R (18euee122@skcet.ac.in)
 * @brief  Contains function definitions for processing the instructions
 * @version 0.1
 * @date 2022-03-30
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "Instruction_DataTypes.h"
#include "Instruction_Process_Methods.h"
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

/**
 * @brief  Function which converts a nibble to hexadecimal
 * 
 * @param temp 
 * @return char 
 */
char nibble_to_hex(int temp){
    char res;
        switch ( temp ){
            case 10:
                res = 'A';break;
            case 11:
                res = 'B';break;
            case 12:
                res = 'C';break;
            case 13:
                res = 'D';break;
            case 14:
                res = 'E';break;
            case 15:
                res = 'F';break;
            default:
                res = (char) (temp + '0');
        }
    return res;
}

/**
 * @brief  convert a instruction in int value to char value to print in the file.
 * 
 * @param Hex_Code 
 * @return char* 
 */
char* inttohex(int Hex_Code){
    char *res = (char*) calloc(3, sizeof(char));
    *(res+1) = nibble_to_hex( (int) ((Hex_Code) & (0x0F)) );
    *res = nibble_to_hex( (int)( ( (Hex_Code) & (0xF0) ) >> 4 ));
    *(res+2) = '\0';
    return res;
}

/**
 * @brief Shifts the string to left i times
 * 
 * @param inst 
 * @param i 
 */
void shiftStringLeft(char inst[],int i){ //Shift String input given in inst by i char
    int k=0;
    while( (i+k) < strlen(inst) ){
        inst[k] = inst[k+i];
        k++;
    }
    inst[k]='\0';
}

/**
 * @brief Remove unwanted whitespaces in order to easily extract required information
 * 
 * @param inst 
 */
void Remove_Leading_Whitespaces(char inst[]){ //Remove white spaces in a string
    int i=0;
    while( inst[i] == ' ' ){
        i++;
    }
    shiftStringLeft( inst, i );
    
}

/**
 * @brief Read the opcode from inst string
 * 
 * @param inst 
 * @param Opcode 
 */
void Read_Opcode(char inst[],char* Opcode){ //Reads the Opcode of a Instruction
    int i=0;
    while( inst[i] != ' ' ){
        *(Opcode+i)=inst[i];
        i++;
    }
    shiftStringLeft(inst,i); 
    Remove_Leading_Whitespaces(inst);
}

/**
 * @brief Read the next operand from inst string
 * 
 * @param inst 
 * @param Operand_1 
 */
void Read_Operand(char inst[],char* Operand_1){ //Reads Next Operand of an Instruction
    char *c;
    c = strchr( inst, ',' );
    if( c == NULL ){
        Remove_Leading_Whitespaces( inst );
        strcpy( Operand_1, inst );
    }
    else{
    Remove_Leading_Whitespaces( inst );
    strncpy( Operand_1, inst, (c-inst) );
    Remove_Leading_Whitespaces( inst );
    shiftStringLeft( inst, c-inst+1 );
}
}


/**
 * @brief Get the Number of Operands for a corresponding opcode
 * 
 * @param Opcode 
 * @return int 
 */

int get_Number_of_Operands(char* Opcode){ //Returns the number of Operands in an Instruction
    if(!strcmp(Opcode,"RET") || !strcmp(Opcode,"RETI") || !strcmp(Opcode,"NOP"))
        return 0;
    else if(strcmp(Opcode,"CJNE") == 0)
        return 3;
    else if(!strcmp(Opcode,"DEC") || !strcmp(Opcode,"INC") || !strcmp(Opcode,"RR") || !strcmp(Opcode,"AJMP") || 
        !strcmp(Opcode,"LJMP") || !strcmp(Opcode,"SJMP") || !strcmp(Opcode,"JC") || !strcmp(Opcode,"JNC") || 
        !strcmp(Opcode,"JZ") || !strcmp(Opcode,"JNZ") || !strcmp(Opcode,"JMP") || !strcmp(Opcode,"ACALL") || 
        !strcmp(Opcode,"LCALL") || !strcmp(Opcode,"CPL") || !strcmp(Opcode,"CLR") || !strcmp(Opcode,"SETB") || 
        !strcmp(Opcode,"PUSH") || !strcmp(Opcode,"POP") || !strcmp(Opcode,"DA") || !strcmp(Opcode,"ORG") ||
        !strcmp(Opcode,"MUL") || !strcmp(Opcode,"DIV") ) 
        return 1;
    else
        return 2;
}

/**
 * @brief  Read the instruction from the file using file pointer *code and write it to the char pointer *inst
 * 
 * @param code 
 * @param inst 
 * @return char* 
 */
char* Read_Instruction(FILE *code,char* inst){ //Reads the instruction in the current line pointed by the File pointer
    return fgets(inst,26,code);  
}