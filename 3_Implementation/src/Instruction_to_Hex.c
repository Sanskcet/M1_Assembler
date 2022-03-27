#include <string.h>
#include <stdlib.h>
#include "Instruction_Set.h"
#include <stdio.h>


int match_Opcode(char Opcode[]){
    int k=0;
    while(strcmp(Opcode,Instruction_List[k].OPCODE)){
        k++;
        
        if(k>=46){
            return 50;
        }
    } 
    return k;
}

int Modifiers(char Operands[]){
    
    if( (Operands[0]=='A') && (strlen(Operands)==1) )
        return 0x04;
    else if(strcmp(Operands , "@R0")==0)
        return 0x06;
    else if(strcmp(Operands , "@R1")==0)
        return 0x07;    
    else if(strcmp(Operands , "R0")==0)
        return 0x08;
    else if(strcmp(Operands , "R1")==0)
        return 0x09;
    else if(strcmp(Operands , "R2")==0)
        return 0x0A;
    else if(strcmp(Operands , "R3")==0)
        return 0x0B;
    else if(strcmp(Operands , "R4")==0)
        return 0x0C;
    else if(strcmp(Operands , "R5")==0)
        return 0x0D;
    else if(strcmp(Operands , "R6")==0)
        return 0x0E;
    else if(strcmp(Operands , "R7")==0)
        return 0X0F;
    else if(strchr(Operands , 'H'))
        return 0x05;
    else
        return 0;
}
int parse_Modifier(int hex_Code,char Operand[]){
    int temp;
    if(temp=Modifiers(Operand)){
       // printf("%d\n",temp);
        hex_Code=hex_Code/16;
        hex_Code=hex_Code*16 + temp;
    }
}
int process_Hex_Code_0(char Operand_0[],char Operand_1[],char Operand_2[],int k){
    int hex_Code=0;
    
    //printf("%s",Instruction_List[k].OPCODE);
    //MOV INSTRUCTION PROCESSING
    if(strcmp(Instruction_List[k].OPCODE, "MOV" )==0){
        if(Operand_1[0]=='#'){
            if(strcmp(Operand_0 , "DPTR")==0){
                hex_Code=0x90;
            }
            else{      
                   
                hex_Code=Instruction_List[k].hex_value;
                hex_Code=parse_Modifier(hex_Code,Operand_0);
            }
        }

        //MOV BIT
        else if ( (strlen( Operand_0 ) == 1 || strlen( Operand_1 ) == 1 ) && ( Operand_0[0] == 'C' || Operand_1[0] == 'C') ){
            if(Operand_0[0] == 'C'){
                hex_Code = 0xA2;
            }
            else if( Operand_1[0] == 'C'){
                hex_Code = 0x92;
            }
        }

        //MOV WITH DIRECT MEMORY
        else if ( Operand_0[0] != '#' && Operand_1[0] != '#' && strlen( Operand_0) > 1 && strlen ( Operand_1) > 1){
                hex_Code = 0x85;
                if ( Operand_0[0] == 'R' || Operand_0[0] == '@' ){
                    hex_Code = 0xA8;
                    hex_Code=parse_Modifier(hex_Code,Operand_0);
                }
                else if ( Operand_1[0] == 'R' || Operand_1[0] == '@' ){ 
                    hex_Code=parse_Modifier(hex_Code,Operand_1);
                }
        }
        
        //MOV WITH ACCUMULATOR
        else if ( Operand_0[0] == 'A' && strlen(Operand_0)==1){
                hex_Code=0xE5;
                hex_Code=parse_Modifier(hex_Code,Operand_1);
        }
        else if ( Operand_1[0] == 'A' && strlen(Operand_1)==1){
                hex_Code = 0xF5;
                hex_Code = parse_Modifier(hex_Code,Operand_0);
        }
    }

    //ADD INSTRUCTION
    else if(strcmp(Instruction_List[k].OPCODE, "ADD" )==0){
            hex_Code = Instruction_List[k].hex_value;
            hex_Code = parse_Modifier(hex_Code,Operand_1);             
    }

    //ADDC INSTRUCTION
    else if(strcmp(Instruction_List[k].OPCODE, "ADDC" )==0){
            hex_Code = Instruction_List[k].hex_value;
            hex_Code = parse_Modifier(hex_Code,Operand_1);             
    }

    //SUBB INSTRUCTION
    else if(strcmp(Instruction_List[k].OPCODE, "SUBB" )==0){
            hex_Code = Instruction_List[k].hex_value;
            hex_Code = parse_Modifier(hex_Code,Operand_1);             
    }

    //EXCHANGE INSTRUCTION
    else if(strcmp(Instruction_List[k].OPCODE, "XCH" )==0){
            hex_Code = Instruction_List[k].hex_value;
            hex_Code = parse_Modifier(hex_Code,Operand_1);             
    }

    //EXCHANGE DIRECT INSTRUCTION
    else if(strcmp(Instruction_List[k].OPCODE, "XCHD" )==0){
            hex_Code = Instruction_List[k].hex_value;
            hex_Code = parse_Modifier(hex_Code,Operand_1);             
    }

    //INC INSTRUCTION
    else if(strcmp(Instruction_List[k].OPCODE, "INC" )==0){
        if(strcmp(Operand_0 , "DPTR")==0){
                hex_Code=0xA3;
        }   
        else{         
            hex_Code = Instruction_List[k].hex_value;
            hex_Code = parse_Modifier(hex_Code,Operand_0);             
        }
    }

    //DEC INSTRUCTION
    else if(strcmp(Instruction_List[k].OPCODE, "DEC" )==0){

        hex_Code = Instruction_List[k].hex_value;
        hex_Code = parse_Modifier(hex_Code,Operand_0);             

    }

    //COMPARE WITH JUMP INSTRUCTION
    else if(strcmp(Instruction_List[k].OPCODE, "CJNE" )==0){

        if( strcmp(Operand_0,"A") == 0 && strchr(Operand_1,'H') ){

            hex_Code = 0xB5;

        }
        else{

            hex_Code = Instruction_List[k].hex_value;
            hex_Code = parse_Modifier(hex_Code,Operand_0);   

        }

    }

    //DJNZ INSTRUCTION
    else if(strcmp(Instruction_List[k].OPCODE, "DJNZ" )==0){

        hex_Code = Instruction_List[k].hex_value;
        hex_Code = parse_Modifier(hex_Code,Operand_0);             

    }

    //JBC INSTRUCTION
    else if(strcmp(Instruction_List[k].OPCODE, "JBC" )==0) hex_Code = Instruction_List[k].hex_value;

    //JB INSTRUCTION
    else if(strcmp(Instruction_List[k].OPCODE, "JB" )==0) hex_Code = Instruction_List[k].hex_value;

    //JNB INSTRUCTION
    else if(strcmp(Instruction_List[k].OPCODE, "JNB" )==0) hex_Code = Instruction_List[k].hex_value;

    //JC INSTRUCTION
    else if(strcmp(Instruction_List[k].OPCODE, "JC" )==0) hex_Code = Instruction_List[k].hex_value;    

    //JNC INSTRUCTION
    else if(strcmp(Instruction_List[k].OPCODE, "JNC" )==0) hex_Code = Instruction_List[k].hex_value;

    //JZ INSTRUCTION
    else if(strcmp(Instruction_List[k].OPCODE, "JZ" )==0) hex_Code = Instruction_List[k].hex_value;

    //JNZ INSTRUCTION
    else if(strcmp(Instruction_List[k].OPCODE, "JNZ" )==0) hex_Code = Instruction_List[k].hex_value;

    //JMP INSTRUCTION
    else if(strcmp(Instruction_List[k].OPCODE, "JMP" )==0) hex_Code = Instruction_List[k].hex_value;    

    //LCALL 
    else if(strcmp(Instruction_List[k].OPCODE, "LCALL" )==0) hex_Code = Instruction_List[k].hex_value;

    //RET INSTRUCTION
    else if(strcmp(Instruction_List[k].OPCODE, "RET" )==0) hex_Code = Instruction_List[k].hex_value;

    //RETI INSTRUCTION
    else if(strcmp(Instruction_List[k].OPCODE, "RETI" )==0) hex_Code = Instruction_List[k].hex_value;

    //RL INSTRUCTION
    else if(strcmp(Instruction_List[k].OPCODE, "RL" )==0) hex_Code = Instruction_List[k].hex_value;

    //RLC INSTRUCTION
    else if(strcmp(Instruction_List[k].OPCODE, "RLC" )==0) hex_Code = Instruction_List[k].hex_value;    

    //RR 
    else if(strcmp(Instruction_List[k].OPCODE, "RR" )==0) hex_Code = Instruction_List[k].hex_value;

    //RRC INSTRUCTION
    else if(strcmp(Instruction_List[k].OPCODE, "RRC" )==0) hex_Code = Instruction_List[k].hex_value;

    //SWAP INSTRUCTION
    else if(strcmp(Instruction_List[k].OPCODE, "SWAP" )==0) hex_Code = Instruction_List[k].hex_value;
   
    //LOGICAL INSTRUCTION
    else if( strcmp( Instruction_List[k].OPCODE, "ANL") || strcmp( Instruction_List[k].OPCODE, "ORL") || strcmp( Instruction_List[k].OPCODE, "XRL") ){
        hex_Code=Instruction_List[k].hex_value;
        if ( Operand_1[0] == '#' && strchr(Operand_0, 'H')){
            
        }
        else if ( strcmp( Operand_0, "C") == 0 && strcmp( Instruction_List[k].OPCODE, "ORL"))
            hex_Code = 0x72;
        else if ( strcmp( Operand_0, "C") == 0 && strcmp( Instruction_List[k].OPCODE, "ANL"))
            hex_Code = 0x82;
        else if ( strcmp(Operand_1, "A") == 0 ){
            hex_Code = 0x52;
        }
        else {
            hex_Code = parse_Modifier(hex_Code,Operand_0);
        }
    }

    //NOP INSTRUCTION
    else if(strcmp(Instruction_List[k].OPCODE, "NOP" )==0) hex_Code = Instruction_List[k].hex_value;
    
    //MUL INSTRUCTION
    else if(strcmp(Instruction_List[k].OPCODE, "MUL" )==0) hex_Code = Instruction_List[k].hex_value;

    //DIV INSTRUCTION
    else if(strcmp(Instruction_List[k].OPCODE, "DIV" )==0) hex_Code = Instruction_List[k].hex_value;

    //DA INSTRUCTION
    else if(strcmp(Instruction_List[k].OPCODE, "DA" )==0) hex_Code = Instruction_List[k].hex_value;

    //PUSH INSTRUCTION
    else if(strcmp(Instruction_List[k].OPCODE, "PUSH" )==0) hex_Code = Instruction_List[k].hex_value;

    //POP INSTRUCTION
    else if(strcmp(Instruction_List[k].OPCODE, "POP" )==0) hex_Code = Instruction_List[k].hex_value;

    //SETB INSTRUCTION
    else if(strcmp(Instruction_List[k].OPCODE, "SETB" ) == 0){
        if ( strcmp( Operand_0, "C") == 0 ) {
            hex_Code = 0xD3;
        }
        else { 
            hex_Code = 0xD2;
        }
    }  

    //CLR INSTRUCTION
    else if(strcmp(Instruction_List[k].OPCODE, "CLR" ) == 0){
        if ( strcmp( Operand_0, "C") == 0 ) {
            hex_Code = 0xC3;
        }
        else if ( strcmp( Operand_0, "A") == 0 ) {
            hex_Code = 0xE4;
        }
        else { 
            hex_Code = 0xC2;
        }
    }

    //CPL INSTRUCTION
    else if(strcmp(Instruction_List[k].OPCODE, "CPL" ) == 0){
        if ( strcmp( Operand_0, "C") == 0 ) {
            hex_Code = 0xB3;
        }
        else if ( strcmp( Operand_0, "A") == 0 ) {
            hex_Code = 0xF4;
        }
        else { 
            hex_Code = 0xB2;
        }
    }

    return hex_Code;
}



char* process_Hex_Code_1(char Operand_0[],char Operand_1[],char Operand_2[],int k){
    char *hex_Code_1=(char*)malloc(2*sizeof(char)); //Allocate memory for return string
    char Op[6];
    if( k == 1 || k == 32 || k == 33 || k == 34 || ( k >= 7 && k <= 9 ) || ( k >= 38 && k <=39 )){ //For MOV Instruction
        if(strcmp(Operand_0,"DPTR") == 0 || Operand_0[0] == '@' || Operand_0[0] == 'R' ) //DPTR or Indirect addressing or Register addressing
            strcpy(Op,Operand_1);    

        else if ( strlen(Operand_0) == 1 && !( Operand_0[0] >= '0' && Operand_0[0] <= '9') ){ //MOV A or C
            strcpy(Op,Operand_1);  
        }

        else
        {
            strcpy(Op,Operand_0);
        }

        if(Op[0]=='#'){//Check if it's a immidiate value or not
            hex_Code_1[0]=(char)Op[1];
            hex_Code_1[1]=(char)Op[2];
            }
        else{
            hex_Code_1[0]=(char)Op[0];
            hex_Code_1[1]=(char)Op[1];
            }
    }
    else if ( k == 5 || k == 6 || k == 40 || k == 41 || ( k >= 27 && k <= 37 )){ //For ADD, ADDC, SUBB, INC, DEC Instruction
        if(Operand_0[0]=='#'){//Check if it's a immidiate value or not
            hex_Code_1[0]=(char)Operand_0[1];
            hex_Code_1[1]=(char)Operand_0[2];
            }
        else{
            hex_Code_1[0]='0';
            hex_Code_1[1]='0';
        }
    }
    else if ( k >= 42 && k <= 44 ){ //For MUL DIV DA
        hex_Code_1[0]='0';
        hex_Code_1[1]='0';               
    }
    else if ( k == 10 ) {
        if(Operand_1[0]=='#'){//Check if it's a immidiate value or not
            hex_Code_1[0]=(char)Operand_1[1];
            hex_Code_1[1]=(char)Operand_1[2];
            }
        else{
            hex_Code_1[0]=(char)Operand_1[0];
            hex_Code_1[1]=(char)Operand_1[1];
            }       
    }
    else if ( k == 11 ) {
        if ( Operand_0[0] == 'R' ){
            strcpy( hex_Code_1, Operand_1 );
        }
        else{
            strcpy( hex_Code_1, Operand_0 );
        }
    }

    hex_Code_1[2]='\0';
    //printf("%s",hex_Code);
    //printf("%s\n",hex_Code_1);
    return hex_Code_1;
}

char* process_Hex_Code_2(char Operand_0[],char Operand_1[],char Operand_2[],int k){
    char Op[6];
    char *hex_Code=(char*)malloc(2*sizeof(char));
    if(strcmp(Operand_0,"DPTR")==0){
        strcpy(Op,Operand_1); 
        if(strchr(Op,'H')){//Check if it's a Hexadecimal Value or Decimal Value
        if(Op[0]=='#'){//Check if it's a immidiate value or not
            //printf("H\n");
            hex_Code[0]=Op[3];
            hex_Code[1]=Op[4];
        }
        else{
            hex_Code[0]=Op[2];
            hex_Code[1]=Op[3];
        }
    }
    else{
                //Code to convert Integer to Hex            
        }
    }

    else if ( strcmp(Operand_0,"A")==0 || Operand_0[0]=='@' || Operand_0[0]=='R' || strcmp(Operand_1,"A")==0 || Operand_1[0]=='@' || Operand_1[0]=='R' ) {
        hex_Code[0]='0';
        hex_Code[1]='0';
    }

    else{

        if(Operand_1[0]=='#'){//Check if it's a immidiate value or not
                hex_Code[0]=(char)Operand_1[1];
                hex_Code[1]=(char)Operand_1[2];
            }
        else{
                hex_Code[0]=(char)Operand_1[0];
                hex_Code[1]=(char)Operand_1[1];
            }

    }   

    hex_Code[2]='\0';
    //printf("%s\n",hex_Code);
    return hex_Code;
}