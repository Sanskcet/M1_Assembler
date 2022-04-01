#ifndef TEST
#define TEST

#include "unity.h"

#include "Instruction_Process_Methods.h"

void test_nibble_to_hex(void);
void test_inttohex(void);
void test_shiftStringLeft(void);
void test_Remove_Leading_Whitespaces(void);
void test_Read_Opcode(void);
void test_Read_Operand(void);
void test_get_Number_of_Operands(void);
void test_match_Opcode(void);
void test_process_Hex_Code_0(void);
void test_process_Hex_Code_1(void);
void test_process_Hex_Code_2(void);

char inst[5][20] = { 
    "MOV A,#70H", 
    "CJNE R1, #98H, 4", 
    "INC @R0", 
    "PUSH 80H", 
    "MUL AB" 
    };

void setUp(void)
{
}

void tearDown(void)
{

}

int main(){

    UNITY_BEGIN(); //Initialize Unity Test Framework
    /*Run Tests*/
    RUN_TEST(test_nibble_to_hex);
    RUN_TEST(test_inttohex);    
    RUN_TEST(test_shiftStringLeft);
    RUN_TEST(test_Remove_Leading_Whitespaces);
    RUN_TEST(test_Read_Opcode);
    RUN_TEST(test_Read_Operand);
    RUN_TEST(test_get_Number_of_Operands);
    RUN_TEST(test_match_Opcode);
    RUN_TEST(test_process_Hex_Code_0);
    RUN_TEST(test_process_Hex_Code_1);
    RUN_TEST(test_process_Hex_Code_2);
    return UNITY_END(); //Close Unity Test Framework
}

void test_nibble_to_hex(void)
{
    //Test - nibble_to_hex 
    TEST_ASSERT_EQUAL_CHAR('5',nibble_to_hex(5));
    TEST_ASSERT_EQUAL_CHAR('E',nibble_to_hex(14));
}

void test_inttohex(void){
    //Test - inttohex
    TEST_ASSERT_EQUAL_STRING("1F",inttohex(0x1F));
    TEST_ASSERT_EQUAL_STRING("FF",inttohex(0xFF));
    TEST_ASSERT_EQUAL_STRING("00",inttohex(0x00));
}

void test_shiftStringLeft(void){
    char test[] = "Hello World";
    shiftStringLeft(test ,5);

    //Test - shiftStringLeft
    TEST_ASSERT_EQUAL_STRING(test," World");
    
    strcpy( test, "Hello World" );
    shiftStringLeft(test ,11);

    TEST_ASSERT_EQUAL_STRING(test,"");

}

void test_Remove_Leading_Whitespaces(void){
    char test[] = "    Hello World";
    Remove_Leading_Whitespaces(test);

    //Test - Remove_Leading_Whitespaces
    TEST_ASSERT_EQUAL_STRING(test, "Hello World");
    strcpy(test,"Hello World");
    TEST_ASSERT_EQUAL_STRING(test, "Hello World");
}

void test_Read_Opcode(void){
    char test_res[5][5] = { "MOV", "CJNE", "INC", "PUSH", "MUL"};

    //Test - Read_Opcode
    for(int i = 0; i < 5; i++) { 
        char *Opcode = calloc(6,sizeof(char));
        Read_Opcode(inst[i],Opcode);
        TEST_ASSERT_EQUAL_STRING(Opcode, test_res[i]);
        free(Opcode);
    }
}

void test_Read_Operand(void){
    char test_res[5][5] = { 
        "A", "R1", "@R0", "80H", "AB"
        };

    //Test - Read_Operand
    for(int i = 0; i < 5; i++) { 
    char *Operand = calloc(6,sizeof(char));
    Read_Operand(inst[i],Operand);
    TEST_ASSERT_EQUAL_STRING(Operand, test_res[i]);
    free(Operand);
    }    
}

void test_get_Number_of_Operands(void){
    int test_res[5] = { 2 ,3 , 1, 1, 1};
    char inst_k[5][20] = { 
    "MOV A,#70H", 
    "CJNE R1, #98H, 4", 
    "INC @R0", 
    "PUSH 80H", 
    "MUL AB" 
    };

    //Test - get_Number_of_Operands
    for(int i = 0; i < 5; i++) { 
        char *Opcode = calloc(6,sizeof(char));
        Read_Opcode(inst_k[i],Opcode);
        TEST_ASSERT_EQUAL( get_Number_of_Operands(Opcode), test_res[i]);
        free(Opcode);
    }      
}

void test_match_Opcode(void){
    int test_res[5] = { 1 ,10 ,5 , 40, 42};
    char inst_k[5][20] = { 
    "MOV A,#70H", 
    "CJNE R1, #98H, 4", 
    "INC @R0", 
    "PUSH 80H", 
    "MUL AB" 
    };

    //Test - match_Opcode
    for(int i = 0; i < 5; i++) { 
        char *Opcode = calloc(6,sizeof(char));
        Read_Opcode(inst_k[i],Opcode);
        TEST_ASSERT_EQUAL( match_Opcode(Opcode), test_res[i]);
        free(Opcode);
    }  
}
void test_process_Hex_Code_0(void){
    int test_res[5] = { 0x74, 0xB9, 0X06, 0XC0, 0XA4 };
    char inst_k[5][20] = { 
    "MOV A,#70H", 
    "CJNE R1, #98H, 4", 
    "INC @R0", 
    "PUSH 80H", 
    "MUL AB" 
    };
    
    //Test - parse_Modifier
    for(int i = 0; i < 5; i++) { 
        char *Opcode = calloc(6,sizeof(char));
        char *Operands[3];
        Read_Opcode(inst_k[i],Opcode);
        int k = get_Number_of_Operands(Opcode);
        int j=0;
        while( j < k ){
            Operands[j] = calloc(10,sizeof(char));//Allocate memory for Operand
            Read_Operand(inst_k[i],Operands[j]);// Read the next operand
            j++;
        }
        TEST_ASSERT_EQUAL( test_res[i], process_Hex_Code_0(Operands[0], Operands[1], Operands[2], match_Opcode(Opcode)));
        free(Opcode);
        for(int j = 0;j < k; j++){ //Free memory allocated for Operands
            free(Operands[j]);
        }
    }  
}

void test_process_Hex_Code_1(void){
    char test_res[5][3] = {"70" , "98", "00", "80", "00" };
    char inst_k[5][20] = { 
    "MOV A,#70H", 
    "CJNE R1, #98H, 4", 
    "INC @R0", 
    "PUSH 80H", 
    "MUL AB" 
    };
    
    //Test - process_Hex_Code_1
    for(int i = 0; i < 5; i++) { 
        char *Opcode = calloc(6,sizeof(char));
        char *Operands[3];
        Read_Opcode(inst_k[i],Opcode);
        int k = get_Number_of_Operands(Opcode);
        int j=0;
        while( j < k ){
            Operands[j] = calloc(10,sizeof(char));//Allocate memory for Operand
            Read_Operand(inst_k[i],Operands[j]);// Read the next operand
            j++;
        }

        TEST_ASSERT_EQUAL_STRING( test_res[i] , process_Hex_Code_1(Operands[0], Operands[1], Operands[2], match_Opcode(Opcode)));
        free(Opcode);
        for(int j = 0;j < k; j++){ //Free memory allocated for Operands
            free(Operands[j]);
        }
    }  
}

void test_process_Hex_Code_2(void){
    char test_res[5][3] = {"00" , "4", "00", "00", "00" };
    char inst_k[5][20] = { 
    "MOV A,#70H", 
    "CJNE R1, #98H, 4", 
    "INC @R0", 
    "PUSH 80H", 
    "MUL AB" 
    };
    
    //Test - process_Hex_Code_2
    for(int i = 0; i < 5; i++) { 
        char *Opcode = calloc(6,sizeof(char));
        char *Operands[3];
        Read_Opcode(inst_k[i],Opcode);
        int k = get_Number_of_Operands(Opcode);
        int j=0;
        while( j < k ){
            Operands[j] = calloc(10,sizeof(char));//Allocate memory for Operand
            Read_Operand(inst_k[i],Operands[j]);// Read the next operand
            j++;
        }

        TEST_ASSERT_EQUAL_STRING( test_res[i] , process_Hex_Code_2(Operands[0], Operands[1], Operands[2], match_Opcode(Opcode),j));
        free(Opcode);
        for(int j = 0;j < k; j++){ //Free memory allocated for Operands
            free(Operands[j]);
        }
    }  
}
#endif // TEST
