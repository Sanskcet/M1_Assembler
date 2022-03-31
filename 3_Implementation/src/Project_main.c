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
#include "Instruction_Process_Methods.h"

#define Assembly_Code_Path "./test/test_code.asm"
#define Hex_File_Output_Path "./output/hex_file.hex"

int main(){

    FILE *code = fopen( Assembly_Code_Path, "r");
    FILE *out = fopen( Hex_File_Output_Path, "w+");
    char *ins;
    char *Opcode,*Operands[3];
  
    int Number_of_Operands;
    
    
    int i,k;
    int NOT_EOF=1;
    

   while(!feof(code)){//While not  at the end of file, execute the following codes

        ins=calloc(30,sizeof(char)); //Allocate memory for temporary variable ins
        ins=Read_Instruction(code,ins); //Read the Instruction in the line pointed by file pointer

        char inst[strlen(ins)]; //create a string of length of the instruction

        strcpy(inst,ins); //Copy the contents from temp variable to inst

        if(!feof(code))
            inst[strlen(inst)-1]='\0';//add end of line at the end

        free(ins); //free temporary variable

        int Hex_Code_Operand;
        char Hex_Code_1[3], Hex_Code_2[3];
        char res[7];
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
            free(Opcode);
            return 0;
        }
        else{
            

            Hex_Code_Operand = process_Hex_Code_0(Operands[0],Operands[1],Operands[2],k);  //Get first hexcode
            strcpy(Hex_Code_1 , process_Hex_Code_1(Operands[0],Operands[1],Operands[2],k)); //Get Second hexcode
            strcpy(Hex_Code_2 , process_Hex_Code_2(Operands[0],Operands[1],Operands[2],k,Number_of_Operands)); //Get third hexcode

        }
        strcpy( res, inttohex(Hex_Code_Operand) );
        strcat( res, Hex_Code_1 );
        strcat( res, Hex_Code_2 );
        printf("%x %s %s\n\n",Hex_Code_Operand,Hex_Code_1,Hex_Code_2);
        res[6]='\n';
        res[7]='\0';
        printf("%s\n",res);

        fwrite(res,1,sizeof(res),out);

        for(int j=0;j<Number_of_Operands;j++){ //Free memory allocated for Operands
            free(Operands[j]);
        }
        free(Opcode); //Free Memory allocated for Opcode
        
    }
   
    fclose(code); //Close the file
    fclose(out);//Close the output file
    
    return 0;
}