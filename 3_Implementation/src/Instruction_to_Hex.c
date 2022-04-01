/**
 * @file Instruction_to_Hex.c
 * @author Sanjeeve R (18euee122@skcet.ac.in)
 * @brief  Contains function definitions required to convert an Instruction to the equivalent Hex Code
 * @version 0.1
 * @date 2022-03-30
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "Instruction_Set.h"

int match_Opcode(char Opcode[]){ //Matches the Opcode in the Instruction to that in the Instruction_Set.h file
    int k=0;
    while(strcmp(Opcode,Instruction_List[k].OPCODE)){
        k++;
        
        if(k>=46){ //45 Instructions are defined. If k value is greater than 45, return 50 which means to raise error.
            return 50;
        }
    } 
    return k;
}

int Modifiers(char Operands[]){ //Preset Modifiers for the Instruction
    
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
int parse_Modifier(int hex_Code, char Operand[]){ //Incorporate the Modifier with the hex code
    int temp;
    if( temp = Modifiers(Operand) ){
        hex_Code = hex_Code/16;
        hex_Code = hex_Code*16 + temp;
    }
}
int process_Hex_Code_0(char Operand_0[],char Operand_1[],char Operand_2[],int k){ //Process the first hex code
    int hex_Code=0;
    switch ( k ){
    //MOV INSTRUCTION PROCESSING
    case 1:
        if( Operand_1[0] == '#' ){
            if( strcmp(Operand_0 , "DPTR") == 0){
                hex_Code = 0x90;
            }
            else{      
                hex_Code = Instruction_List[k].hex_value;
                hex_Code = parse_Modifier(hex_Code,Operand_0);
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
    break;
    
    //MOVX INSTRUCTION
    case 2:
        if( strcmp( Operand_0, "A") == 0){
            if ( strcmp( Operand_1, "@DPTR") == 0 ){
                hex_Code = 0xE0;
            }
            else if ( strcmp( Operand_1, "@R0") == 0 ){
                hex_Code = 0xE2;
            }
            else if ( strcmp( Operand_1, "@R1") == 0 ){
                hex_Code = 0xE3;
            }
        }
        else{
            if ( strcmp( Operand_0, "@DPTR") == 0 ){
                hex_Code = 0xF0;
            }
            else if ( strcmp( Operand_0, "@R0") == 0 ){
                hex_Code = 0xF2;
            }
            else if ( strcmp( Operand_0, "@R1") == 0 ){
                hex_Code = 0xF3;
            }
        }
    break;

    //ADD INSTRUCTION
    case 7:
            hex_Code = Instruction_List[k].hex_value;
            hex_Code = parse_Modifier(hex_Code,Operand_1);             
    break;

    //ADDC INSTRUCTION
    case 8:
            hex_Code = Instruction_List[k].hex_value;
            hex_Code = parse_Modifier(hex_Code,Operand_1);             
    break;

    //SUBB INSTRUCTION
    case 9:
            hex_Code = Instruction_List[k].hex_value;
            hex_Code = parse_Modifier(hex_Code,Operand_1);             
    break;

    //EXCHANGE INSTRUCTION
    case 38:
            hex_Code = Instruction_List[k].hex_value;
            hex_Code = parse_Modifier(hex_Code,Operand_1);             
    break;

    //EXCHANGE DIRECT INSTRUCTION
    case 39:
            hex_Code = Instruction_List[k].hex_value;
            hex_Code = parse_Modifier(hex_Code,Operand_1);             
    break;

    //INC INSTRUCTION
    case 5:
        if(strcmp(Operand_0 , "DPTR")==0){
                hex_Code=0xA3;
        }   
        else{         
            hex_Code = Instruction_List[k].hex_value;
            hex_Code = parse_Modifier(hex_Code,Operand_0);             
        }
    break;

    //DEC INSTRUCTION
    case 6:

        hex_Code = Instruction_List[k].hex_value;
        hex_Code = parse_Modifier(hex_Code,Operand_0);             
    break;

    //COMPARE WITH JUMP INSTRUCTION
    case 10:

        if( strcmp(Operand_0,"A") == 0 && strchr(Operand_1,'H') ){

            hex_Code = 0xB5;

        }
        else{

            hex_Code = Instruction_List[k].hex_value;
            hex_Code = parse_Modifier(hex_Code,Operand_0);   

        }

    break;

    //DJNZ INSTRUCTION
    case 11:

        hex_Code = Instruction_List[k].hex_value;
        hex_Code = parse_Modifier(hex_Code,Operand_0);             

    break;

    //JBC INSTRUCTION
    case 15: hex_Code = Instruction_List[k].hex_value; break;

    //JB INSTRUCTION
    case 16: hex_Code = Instruction_List[k].hex_value; break;

    //JNB INSTRUCTION
    case 17: hex_Code = Instruction_List[k].hex_value; break;

    //JC INSTRUCTION
    case 18: hex_Code = Instruction_List[k].hex_value; break;

    //JNC INSTRUCTION
    case 19: hex_Code = Instruction_List[k].hex_value; break;

    //JZ INSTRUCTION
    case 20: hex_Code = Instruction_List[k].hex_value; break;

    //JNZ INSTRUCTION
    case 21: hex_Code = Instruction_List[k].hex_value; break;

    //JMP INSTRUCTION
    case 22: hex_Code = Instruction_List[k].hex_value; break;

    //LCALL 
    case 24: hex_Code = Instruction_List[k].hex_value; break;

    //RET INSTRUCTION
    case 25: hex_Code = Instruction_List[k].hex_value; break;

    //RETI INSTRUCTION
    case 26: hex_Code = Instruction_List[k].hex_value; break;

    //RL INSTRUCTION
    case 29: hex_Code = Instruction_List[k].hex_value; break;

    //RLC INSTRUCTION
    case 30: hex_Code = Instruction_List[k].hex_value; break;

    //RR 
    case 27: hex_Code = Instruction_List[k].hex_value; break;

    //RRC INSTRUCTION
    case 28: hex_Code = Instruction_List[k].hex_value; break;

    //SWAP INSTRUCTION
    case 31: hex_Code = Instruction_List[k].hex_value; break;
   
    //LOGICAL INSTRUCTION
    case 32:
    case 33:
    case 34:
        hex_Code=Instruction_List[k].hex_value;
        if ( Operand_1[0] == '#' && strchr(Operand_0, 'H')){
            
        }
        else if ( strcmp( Operand_0, "C") == 0 && strcmp( Instruction_List[k].OPCODE, "ORL") )
            hex_Code = 0x72;
        else if ( strcmp( Operand_0, "C") == 0 && strcmp( Instruction_List[k].OPCODE, "ANL") )
            hex_Code = 0x82;
        else if ( strcmp(Operand_1, "A") == 0 ){
            hex_Code = 0x52;
        }
        else {
            hex_Code = parse_Modifier(hex_Code,Operand_0);
        }
    break;
    
    //NOP INSTRUCTION
    case 4: hex_Code = Instruction_List[k].hex_value; break;
    
    //MUL INSTRUCTION
    case 42: hex_Code = Instruction_List[k].hex_value; break;

    //DIV INSTRUCTION
    case 43: hex_Code = Instruction_List[k].hex_value; break;

    //DA INSTRUCTION
    case 44: hex_Code = Instruction_List[k].hex_value; break;

    //PUSH INSTRUCTION
    case 40: hex_Code = Instruction_List[k].hex_value; break;

    //POP INSTRUCTION
    case 41: hex_Code = Instruction_List[k].hex_value; break;

    //SETB INSTRUCTION
    case 37:
        if ( strcmp( Operand_0, "C") == 0 ) {
            hex_Code = 0xD3;
        }
        else { 
            hex_Code = 0xD2;
        }
    break;

    //CLR INSTRUCTION
    case 36:
        if ( strcmp( Operand_0, "C") == 0 ) {
            hex_Code = 0xC3;
        }
        else if ( strcmp( Operand_0, "A") == 0 ) {
            hex_Code = 0xE4;
        }
        else { 
            hex_Code = 0xC2;
        }
    break;

    //CPL INSTRUCTION
    case 35: 
        if ( strcmp( Operand_0, "C") == 0 ) {
            hex_Code = 0xB3;
        }
        else if ( strcmp( Operand_0, "A") == 0 ) {
            hex_Code = 0xF4;
        }
        else { 
            hex_Code = 0xB2;
        }
    break;
    }
    return hex_Code;
}



char* process_Hex_Code_1(char Operand_0[],char Operand_1[],char Operand_2[],int k){ //Process the second hex code
    char *hex_Code_1 = (char*)malloc(2*sizeof(char)); //Allocate memory for return string
    char Op[6];
    if( k == 1 || k == 32 || k == 33 || k == 34 || ( k >= 7 && k <= 9 ) || ( k >= 38 && k <=39 )){ //For MOV, ORL, XRL, ANL, XCH, XCHD, ADD, ADDC, SUBB Instruction
        if( strcmp(Operand_0,"DPTR") == 0 ) //DPTR 
            strcpy( Op, Operand_1 );   
         
        else if ( ( strcmp(Operand_0,"A") == 0 ||  Operand_0[0] == '@' || Operand_0[0] == 'R') && ( strcmp(Operand_1,"A") == 0 || Operand_1[0] == '@' || Operand_1[0] == 'R') ){//Indirect addressing or Register addressing
            strcpy( Op, "00");
        }
        else if ( strcmp(Operand_0,"A") == 0 || Operand_0[0] == '@' || Operand_0[0] == 'R') //Indirect addressing or Register addressing
            strcpy( Op, Operand_1 ); 
        else if ( strlen(Operand_0) == 1 && !( Operand_0[0] >= '0' && Operand_0[0] <= '9') ){ //MOV A or C
            strcpy( Op, Operand_1 );  
        }

        else
        {
            strcpy(Op,Operand_0);
        }

        if( Op[0] == '#' ){//Check if it's a immidiate value or not
            hex_Code_1[0]=(char)Op[1];
            hex_Code_1[1]=(char)Op[2];
            }
        else{
            if(strlen(Op) == 1){
                hex_Code_1[0] = '0';
                hex_Code_1[1] = (char)Op[0];
            }
            else{
                hex_Code_1[0]=(char)Op[0];
                hex_Code_1[1]=(char)Op[1];
            }
        }
    }
    else if ( k == 5 || k == 6 || k == 40 || k == 41 || ( k >= 27 && k <= 31 ) || ( k >= 35 && k <= 37 ) ){ //For INC, DEC, PUSH, POP, LOGICAL Instruction
        if(Operand_0[0]=='#'){//Check if it's a immidiate value or not
            hex_Code_1[0]=(char)Operand_0[1];
            hex_Code_1[1]=(char)Operand_0[2];
        }
        else if ( strchr( Operand_0,'H') ){ //Check if it's a direct address or not
            hex_Code_1[0] = Operand_0[0];
            hex_Code_1[1] = Operand_0[1];
        }
        else{
            hex_Code_1[0]='0';
            hex_Code_1[1]='0';
        }
    }
    else if ( (k >= 42 && k <= 44) || k == 2 || k == 3 ){ //For MUL DIV DA MOVX MOVC
        hex_Code_1[0]='0';
        hex_Code_1[1]='0';               
    }
    else if ( k == 10 ) { //CJNE Instruction
 
        if(Operand_1[0]=='#'){//Check if it's a immidiate value or not
            hex_Code_1[0]=(char)Operand_1[1];
            hex_Code_1[1]=(char)Operand_1[2];
            }
        else{
            hex_Code_1[0]=(char)Operand_1[0];
            hex_Code_1[1]=(char)Operand_1[1];
            }       
    }
    else if ( k == 11 ) { //DJNZ Instruction
        if ( Operand_0[0] == 'R' ){
            strncpy( hex_Code_1, Operand_1, 2);
        }
        else{
            strncpy( hex_Code_1, Operand_0, 2);
        }
    }

    hex_Code_1[2]='\0';
    return hex_Code_1;
}

char* process_Hex_Code_2(char Operand_0[],char Operand_1[],char Operand_2[],int k,int Number_of_Operands){ //Process third Hex Code
    char Op[6];
    char *hex_Code=(char*)malloc(2*sizeof(char));
    if( Number_of_Operands == 2 ){ //Check if Number of Operands in the instruction is 2
        if( strcmp( Operand_0, "DPTR" ) == 0 ){
            strcpy( Op, Operand_1 ); 
            if( strchr(Op,'H') ){//Check if it's a Hexadecimal Value or Decimal Value
            if( Op[0] == '#' ){//Check if it's a immidiate value or not
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

        else if ( strcmp(Operand_0,"A")==0 || strcmp(Operand_0,"C")==0 || Operand_0[0]=='@' || Operand_0[0]=='R' || strcmp(Operand_1,"A")==0 || Operand_1[0]=='@' || Operand_1[0]=='R' || strcmp(Operand_1,"C")==0 ) {
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
    }
    else if ( Number_of_Operands == 1 ){ //Check if Number of Operands is One
            hex_Code[0] = '0';
            hex_Code[1] = '0';
    }
    else { //If Number of Operands is three viz CJNE
        hex_Code[0] = Operand_2[0];
        hex_Code[1] = Operand_2[1];
    }   

    hex_Code[2]='\0';
    return hex_Code;
}