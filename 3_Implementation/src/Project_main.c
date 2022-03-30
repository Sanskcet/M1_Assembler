/**
 * @file Project_main.c
 * @author Sanjeeve R (18euee122@skcet.ac.in)
 * @brief  Main file of the project.
 * @version 0.1
 * @date 2022-03-30
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "Instruction_Process_Methods.h"

#define Assembly_Code_Path "./test/test_code.asm"

int main(){

    FILE *code=fopen(Assembly_Code_Path,"r");
    char *ins;
    char *Opcode,*Operands[3];
  
    int Number_of_Operands;
    
    
    int i,k;
    int NOT_EOF=1;
    

   while(NOT_EOF){

        ins=calloc(30,sizeof(char)); //Allocate memory for temporary variable ins
        ins=Read_Instruction(code,ins); //Read the Instruction in the line pointed by file pointer

        char inst[strlen(ins)]; //create a string of length of the instruction

        strcpy(inst,ins); //Copy the contents from temp variable to inst
        inst[strlen(inst)-1]='\0';//add end of line at the end
        free(ins); //free temporary variable
    if( strcmp( inst, "EOF" ) != 0 ){//Check wheather we have reached end of file
        
        int Hex_Code_Operand;
        char Hex_Code_1[3], Hex_Code_2[3];
        Opcode=calloc( 8, sizeof(char) );
        Read_Opcode( inst, Opcode );
        Number_of_Operands = get_Number_of_Operands(Opcode);
        printf("%s",Opcode);
        i=0;
        while( i < Number_of_Operands ){
            Operands[i] = (char*)calloc(10,sizeof(char));//Allocate memory for Operand
            Read_Operand(inst,Operands[i]);// Read the next operand
            printf("%s ",Operands[i]);
            i++;
        }
        printf("\n");
        k=match_Opcode(Opcode); //Find the index of the Opcode as per in Instruction _Set.h

        if(k==0){
            //If it's ORG, skip 
        }
        else if ( k == 4){ //If the Opcode is NOP

            Hex_Code_Operand = 0x00;
            strcpy( Hex_Code_1,  "00");
            strcpy( Hex_Code_2, "00");

        }
        else if( k == 50 ){ //If opcode is invalid
            printf("Error at line: %s\n",Opcode);
            for(int j=0;j<Number_of_Operands;j++){
                free(Operands[j]);
            }
            free(Opcode);
            return 0;
        }
        else{
            

            Hex_Code_Operand = process_Hex_Code_0(Operands[0],Operands[1],Operands[2],k);  //Get first hexcode
            strcpy(Hex_Code_1 , process_Hex_Code_1(Operands[0],Operands[1],Operands[2],k)); //Get Second hexcode
            strcpy(Hex_Code_2 , process_Hex_Code_2(Operands[0],Operands[1],Operands[2],k,Number_of_Operands)); //Get third hexcode
        }

        printf("%x %s %s\n\n",Hex_Code_Operand,Hex_Code_1,Hex_Code_2);

        for(int j=0;j<Number_of_Operands;j++){ //Free memory allocated for Operands
            free(Operands[j]);
        }
        free(Opcode); //Free Memory allocated for Opcode
        }
        else{
            NOT_EOF=0; //Flag to exit loop 
        }
        
    }
   
    fclose(code); //Close the file

    
    return 0;
}