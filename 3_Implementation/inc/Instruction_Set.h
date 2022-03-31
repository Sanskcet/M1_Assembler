/**
 * @file Instruction_Set.h
 * @author Sanjeeve R (18euee122@skcet.ac.in)
 * @brief  Header file which has Instruction set of 8051
 * @version 0.1
 * @date 2022-03-30
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef INSTRUCTION_SET_HELLO 
#define INSTRUCTION_SET_HELLO 

#include "Instruction_DataTypes.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>


//Declaration of Instructions
struct Instruction Instruction_List[]={

    //ORG Instruction
    {"ORG",0,0XFFFF,0,0},

    //MOV Instructions
    {"MOV",1,0X74,1,2},
    {"MOVX",2,0XE0,1,1},
    {"MOVC",3,0X83,1,1},

    //NOP Instruction
    {"NOP",4,0x00 ,12,1},

    //Increment Decrement 
    {"INC",5,0x04,1,1},
    {"DEC",6,0x14,1,1},

    //Addition and Subraction 
    {"ADD",7,0X24,1,1},
    {"ADDC",8,0X34,1,1},
    {"SUBB",9,0X94,1,1},

    //Compare with Jump
    {"CJNE",10,0XB4,1,3},
    {"DJNZ",11,0XD5,1,2},

    //Jump 
    {"AJMP",12,0x01,2,2},
    {"LJMP",13,0x02,2,3},
    {"SJMP",14,0X80,1,2},

    //Jump with flag
    {"JBC",15,0x10,1,3},
    {"JB",16,0X20,1,3},
    {"JNB",17,0X30,1,3},
    {"JC",18,0X40,1,2},
    {"JNC",19,0X50,1,2},
    {"JZ",20,0X60,1,2},
    {"JNZ",21,0X70,1,2},

    //Jump Indirect
    {"JMP",22,0X73,1,1},

    //Call Subroutine and Return
    {"ACALL",23,0x11,1,2},
    {"LCALL",24,0x12,1,3},
    {"RET",25,0X22,1,1},
    {"RETI",26,0X32,1,1},

    //Rotate
    {"RR",27,0x03,1,1},
    {"RRC",28,0x13,1,1},
    {"RL",29,0X23,1,1},
    {"RLC",30,0X33,1,1},
    {"SWAP",31,0XC4,1,1},

    //Logical
    {"ANL",32,0X52,1,1},
    {"ORL",33,0X42,1,1},
    {"XRL",34,0X62,1,1},
    {"CPL",35,0XB2,1,1},
    {"CLR",36,0XC2,1,1},
    {"SETB",37,0XD2,1,1},

    //Exchange Instructions
    {"XCH",38,0XC5,1,1},
    {"XCHD",39,0XD6,1,1},

    //STACK Operations
    {"PUSH",40,0XC0,1,2},
    {"POP",41,0XD0,1,2},

    //Accumulator Instructions
    {"MUL",42,0XA4,1,1},
    {"DIV",43,0X84,1,1},
    {"DA",44,0XD4,1,1}
};

 
#endif