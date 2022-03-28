#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "Instruction_Process_Methods.h"


int main(){

    FILE *code=fopen("./test/test_code.asm","r");
    char *ins;
    char *Opcode,*Operands[3];
  
    int Number_of_Operands;
    
    
    int i,k;
    int NOT_EOF=1;
    

   while(NOT_EOF){
        ins=calloc(30,sizeof(char));
        ins=Read_Instruction(code,ins);

        char inst[strlen(ins)];


        //printf("%d\n",(int)strlen(ins));

        strcpy(inst,ins);
        inst[strlen(inst)-1]='\0';
        free(ins);
    if(strcmp(inst,"EOF") != 0){
        
        int Hex_Code_Operand;
        char Hex_Code_1[3],Hex_Code_2[3];
        Opcode=calloc(8,sizeof(char));
        Read_Opcode(inst,Opcode);
        Number_of_Operands=get_Number_of_Operands(Opcode);
            //printf("%d\n",Number_of_Operands);
        printf("%s ",Opcode);
        i=0;
        while(i<Number_of_Operands){
            Operands[i]=(char*)calloc(10,sizeof(char));
            Read_Operand(inst,Operands[i]);
            printf("%s ",Operands[i]);
            i++;
        }
        printf("\n");
        k=match_Opcode(Opcode);
        //printf("%d\n",k);
        if(k==0){
           
        }
        else if ( k == 4){
            Hex_Code_Operand = 0x00;
            strcpy( Hex_Code_1,  "00");
            strcpy( Hex_Code_2, "00");
        }
        else if(k==50){
            printf("Error at line: %s\n",Opcode);
            for(int j=0;j<Number_of_Operands;j++){
                free(Operands[j]);
            }
            free(Opcode);
            return 0;
        }
        else{
            

            Hex_Code_Operand = process_Hex_Code_0(Operands[0],Operands[1],Operands[2],k);  
            strcpy(Hex_Code_1 , process_Hex_Code_1(Operands[0],Operands[1],Operands[2],k));
            strcpy(Hex_Code_2 , process_Hex_Code_2(Operands[0],Operands[1],Operands[2],k,Number_of_Operands));

            //printf("%s\n",Operands[1]);
            //printf("%s\n",inst);
            //printf("%s\n",inst);
            //printf("%s",Hex_Code_2);
           
        
        // printf("%s\n",third_Token);
        }

        printf("%x %s %s\n\n",Hex_Code_Operand,Hex_Code_1,Hex_Code_2);

        for(int j=0;j<Number_of_Operands;j++){
            free(Operands[j]);
        }
        free(Opcode);
        }
        else{
            NOT_EOF=0;
        }
        
    }
   
    fclose(code);

    
    return 0;
}