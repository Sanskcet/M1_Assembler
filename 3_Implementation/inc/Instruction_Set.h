#ifndef INSTRUCTION_SET_HELLO 
#define INSTRUCTION_SET_HELLO 

#include "Instruction_DataTypes.h"



//Declaration of Instructions
struct Instruction Instruction_List[]={

    //ORG Instruction
    {"ORG",0XFFFF,0,0},

    //MOV Instructions
    {"MOV",0X74,1,2},
    {"MOVX",0XE0,1,1},
    {"MOVC",0X83,1,1},

    //NOP Instruction
    {"NOP", 0x00 ,12,1},

    //Increment Decrement 
    {"INC",0x04,1,1},
    {"DEC",0x14,1,1},

    //Addition and Subraction 
    {"ADD",0X24,1,1},
    {"ADDC",0X34,1,1},
    {"SUBB",0X94,1,1},

    //Compare with Jump
    {"CJNE",0XB4,1,3},
    {"DJNZ",0XD5,1,2},

    //Jump 
    {"AJMP",0x01,2,2},
    {"LJMP",0x02,2,3},
    {"SJMP",0X80,1,2},

    //Jump with flag
    {"JBC",0x10,1,3},
    {"JB",0X20,1,3},
    {"JNB",0X30,1,3},
    {"JC",0X40,1,2},
    {"JNC",0X50,1,2},
    {"JZ",0X60,1,2},
    {"JNZ",0X70,1,2},

    //Jump Indirect
    {"JMP",0X73,1,1},

    //Call Subroutine and Return
    {"ACALL",0x11,1,2},
    {"LCALL",0x12,1,3},
    {"RET",0X22,1,1},
    {"RETI",0X32,1,1},

    //Rotate
    {"RR",0x03,1,1},
    {"RRC",0x13,1,1},
    {"RL",0X23,1,1},
    {"RLC",0X33,1,1},
    {"SWAP",0XC4,1,1},

    //Logical
    {"ANL",0X52,1,1},
    {"ORL",0X42,1,1},
    {"XRL",0X62,1,1},
    {"CPL",0XB2,1,1},
    {"CLR",0XC2,1,1},
    {"SETB",0XD2,1,1},

    //Exchange Instructions
    {"XCH",0XC5,1,1},
    {"XCHD",0XD6,1,1},

    //STACK Operations
    {"PUSH",0XC0,1,2},
    {"POP",0XD0,1,2},

    //Accumulator Instructions
    {"MUL",0XA4,1,1},
    {"DIV",0X84,1,1},
    {"DA",0XD4,1,1}
};

 
#endif