/*****************************************************************//**
 * \file   Stack.h
 * \brief  
 * 
 * \author mtcig
 * \date   May 2024
 *********************************************************************/
#include <stdbool.h>
#pragma once

// =====================================================
// Depth First Algorithm : STACK
// =====================================================

//funções da stack

int push(int stack[], int top, int item);
int pop(int stack[], int top);
int peek(int stack[], int top);
bool isStackEmpty(int top);