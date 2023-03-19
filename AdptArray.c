//
// Created by lidor on 3/16/23.
//
/**
 * i have used the solutions of tichnut maarahot 1 exam question number 4
 */


#include "stdio.h"
#include <stdlib.h>
#include "AdptArray.h"
#include "string.h"

typedef struct AdptArray_{
    int array_size; // the size of the adaptive array
    PElement* pElemARR; // pointer to the elemnts in the adaptive array
    COPY_FUNC copy_func;
    DEL_FUNC del_func;
    PRINT_FUNC print_func;
}AdptArray;


PAdptArray CreateAdptArray(COPY_FUNC copyFunc, DEL_FUNC delFunc, PRINT_FUNC printFunc){
    PAdptArray pAdptArray = (PAdptArray)malloc(sizeof(AdptArray)); // memory alocation
    if(pAdptArray == NULL){ // check if the allocation worked
        return NULL;
    }
    pAdptArray ->array_size = 0; 
    pAdptArray ->pElemARR = NULL;
    pAdptArray ->del_func = delFunc;
    pAdptArray ->copy_func = copyFunc;
    pAdptArray ->print_func = printFunc;
    return pAdptArray;
}

Result SetAdptArrayAt(PAdptArray pAdptArray, int num, PElement pNewElement){
    PElement* newpElemArr;
    if(pAdptArray == NULL){ // check if the adaptive array that we have got isn't null
        return FAIL;
    }
    if(num >= pAdptArray->array_size){ // if the array is smaller than the index we need to insert an element to...
        if((newpElemArr = (PElement*)calloc((num+1), sizeof (PElement))) == NULL){ // allocate memory + initializiation
            return FAIL;
        }
        if(newpElemArr != NULL){ // if the memory allocation was successfull
            memcpy(newpElemArr, pAdptArray->pElemARR, (pAdptArray->array_size) * sizeof (PElement)); // copy all the elemnts from the old place inn memory to the ne place
        }
        if(pAdptArray->pElemARR != NULL){
            free(pAdptArray->pElemARR); // clear all the old memory that we have used
        }
        pAdptArray->pElemARR = newpElemArr; // define the new elemnt
    }
    if(pAdptArray->pElemARR[num] != NULL){// check if the place we want to insert the new elemnt isn't null
        pAdptArray->del_func(pAdptArray->pElemARR[num]);// delete the item in the specific place
    }
    pAdptArray->pElemARR[num] = pAdptArray->copy_func(pNewElement); // insert a copy of the new item
    pAdptArray->array_size = (num >= pAdptArray->array_size) ? (num + 1) : pAdptArray->array_size; // adjust the array size
    return SUCCESS;
}


void DeleteAdptArray(PAdptArray pAdptArray){
    if(pAdptArray == NULL){ // check if the adaptive array that we have got isn't null
        return;
    }
    for(int i = 0; i < pAdptArray->array_size; ++i){ // loop that runs on the whole array
        if((pAdptArray->pElemARR)[i] != NULL){// if the cell isn't empty
            pAdptArray->del_func((pAdptArray->pElemARR)[i]);//delete the elemnt in this cell
        }
    }
    free(pAdptArray->pElemARR);// free the memory that holds the elemnt
    free(pAdptArray);// free the memory that holds the adaptive array
}

PElement GetAdptArrayAt(PAdptArray pAdptArray, int num){
    if(pAdptArray == NULL){// check if the adaptive array that we have got isn't null
        return NULL;
    }
    if(pAdptArray->array_size <= num){// check if the requested place exists in the adaptive array
        return NULL;
    }
    if(num < 0){// check if the requested place isn't negative
        return NULL;
    }
    if((pAdptArray->pElemARR)[num] == NULL){ // check if there is any elemnt in the requested place
        return NULL;
    }
    PElement temp = pAdptArray->copy_func((pAdptArray->pElemARR)[num]);// making a copy of the element
    return temp; //returning the element
}

int GetAdptArraySize(PAdptArray pAdptArray){
    if(pAdptArray == NULL){// check if the adaptive array that we have got isn't null
        return -1;
    }
    return pAdptArray->array_size;// return the array size
}

void PrintDB(PAdptArray pAdptArray){
    if(pAdptArray == NULL){// check if the adapt array isn't null
        return;
    }
    for(int i = 0; i < pAdptArray->array_size; ++i){// loop that runs on the whole array
        if((pAdptArray->pElemARR)[i] != NULL){// print the element in the array if it isn't null
            pAdptArray->print_func(pAdptArray->pElemARR[i]); 
        }
    }
}














