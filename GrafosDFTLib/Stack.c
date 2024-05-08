/*****************************************************************//**
 * \file   Stack.c
 * \brief  Funções para trabalhar com stack
 * 
 * \author mtcig
 * \date   May 2024
 *********************************************************************/

#include <stdbool.h>
#include "Stack.h"


//======================================================
//Stack Functions
//======================================================
int push(int stack[], int top, int item) {
    stack[++top] = item;
    return top;
}

int pop(int stack[], int top) {
    return --top;
}

int peek(int stack[], int top) {
    return stack[top];
}

bool isStackEmpty(int top) {
    return (top == -1);
}