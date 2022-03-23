#include "Instruction_DataTypes.h"
#include<stdio.h>
#include<stdbool.h>
#include<string.h>

void shiftStringLeft(char inst[],int i){
    int k=0;
    while((i+k)<strlen(inst)){
        inst[k]=inst[k+i];
        k++;
    }
    inst[k]='\0';
}

void Remove_Whitespaces(char inst[]){
    int i=0;
    while(inst[i]==' '){
        i++;
    }
    shiftStringLeft(inst,i);
    
}
void Read_Opcode(char inst[],char* Opcode){
    int i=0;
    while(inst[i]!=' '){
        *(Opcode+i)=inst[i];
        i++;
    }
    shiftStringLeft(inst,i);
    Remove_Whitespaces(inst);
}
void Read_Operand(char inst[],char* Operand_1){
    char *c;
    c=strchr(inst,',');
    if(c==NULL){
        Remove_Whitespaces(inst);
        strcpy(Operand_1,inst);
    }
    else{
    strncpy(Operand_1,inst,(c-inst));
    Remove_Whitespaces(inst);
    shiftStringLeft(inst,c-inst+1);
}
    

}

int get_Number_of_Operands(char* Opcode){
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

char* Read_Instruction(FILE *code,char* inst){
    return fgets(inst,26,code);  
}