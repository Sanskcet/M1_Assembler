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

char* inttohex(int Hex_Code){
    char *res = (char*) calloc(3, sizeof(char));
    *(res+1) = nibble_to_hex( (int) ((Hex_Code) & (0x0F)) );
    *res = nibble_to_hex( (int)( ( (Hex_Code) & (0xF0) ) >> 4 ));
    *(res+2) = '\0';
    printf("%s\n",res);
    return res;
}
void shiftStringLeft(char inst[],int i){ //Shift String input given in inst by i char
    int k=0;
    while( (i+k) < strlen(inst) ){
        inst[k]=inst[k+i];
        k++;
    }
    inst[k]='\0';
}

void Remove_Whitespaces(char inst[]){ //Remove white spaces in a string
    int i=0;
    while(inst[i]==' '){
        i++;
    }
    shiftStringLeft(inst,i);
    
}
void Read_Opcode(char inst[],char* Opcode){ //Reads the Opcode of a Instruction
    int i=0;
    while(inst[i]!=' '){
        *(Opcode+i)=inst[i];
        i++;
    }
    shiftStringLeft(inst,i); 
    Remove_Whitespaces(inst);
}
void Read_Operand(char inst[],char* Operand_1){ //Reads Next Operand of an Instruction
    char *c;
    c = strchr( inst, ',' );
    if( c == NULL ){
        Remove_Whitespaces( inst );
        strcpy( Operand_1, inst );
    }
    else{
    Remove_Whitespaces( inst );
    strncpy( Operand_1, inst, (c-inst) );
    Remove_Whitespaces( inst );
    shiftStringLeft( inst, c-inst+1 );
}
    

}

int get_Number_of_Operands(char* Opcode){ //Returns the number of Operands in an Instruction
    if(!strcmp(Opcode,"RET") || !strcmp(Opcode,"RETI") || !strcmp(Opcode,"NOP"))
        return 0;
    else if(!strcmp(Opcode,"CJNE"))
        return 3;
    else if(!strcmp(Opcode,"DEC") || !strcmp(Opcode,"INC") || !strcmp(Opcode,"RR") || !strcmp(Opcode,"AJMP") || 
        !strcmp(Opcode,"LJMP") || !strcmp(Opcode,"SJMP") || !strcmp(Opcode,"JC") || !strcmp(Opcode,"JNC") || 
        !strcmp(Opcode,"JZ") || !strcmp(Opcode,"JNZ") || !strcmp(Opcode,"JMP") || !strcmp(Opcode,"ACALL") || 
        !strcmp(Opcode,"LCALL") || !strcmp(Opcode,"CPL") || !strcmp(Opcode,"CLR") || !strcmp(Opcode,"SETB") || 
        !strcmp(Opcode,"PUSH") || !strcmp(Opcode,"POP") || !strcmp(Opcode,"DA") || !strcmp(Opcode,"ORG"))
        return 1;
    else
        return 2;
}

char* Read_Instruction(FILE *code,char* inst){ //Reads the instruction in the current line pointed by the File pointer
    return fgets(inst,26,code);  
}