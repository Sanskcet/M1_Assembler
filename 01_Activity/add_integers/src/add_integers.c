#include "add_integers.h"
#include<stdio.h>

/**
 * @brief 
 * 
 * @param arg1 
 * @param arg2 
 * @param res
 * @brief Function Definition of Sum. 
 * @return func_return_type 
 */

func_return_type sum ( int arg1, int arg2, int* res){
    int sum = arg1 + arg2;
    if ( arg1 > 0 && arg2 > 0 && sum < 0 )
        return OVERFLOW;
    else if ( arg1 < 0 && arg2 < 0 && sum > 0 )
        return UNDERFLOW;
    else{
        *res = sum; 
        return SUCCESS;
    }
}