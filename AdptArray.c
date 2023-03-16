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
    int array_size;
    PElement* pElemARR;
    COPY_FUNC copy_func;
    DEL_FUNC del_func;
    PRINT_FUNC print_func;
}AdptArray, *PAdptArray;


PAdptArray CreateAdptArray(COPY_FUNC copyFunc, DEL_FUNC delFunc, PRINT_FUNC printFunc){
    PAdptArray pAdptArray = (PAdptArray)malloc(sizeof(AdptArray));
    if(pAdptArray == NULL){
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
    if(pAdptArray == NULL){
        return FAIL;
    }
    if(num >= pAdptArray->array_size){
        if((newpElemArr = (PElement*)calloc((num+1), sizeof (PElement))) == NULL){
            return FAIL;
        }
        if(newpElemArr != NULL){
            memcpy(newpElemArr, pAdptArray->pElemARR, (pAdptArray->array_size) * sizeof (PElement));
        }
        if(pAdptArray->pElemARR != NULL){
            free(pAdptArray->pElemARR);
        }
        pAdptArray->pElemARR = newpElemArr;
    }
    if(pAdptArray->pElemARR[num] != NULL){
        pAdptArray->del_func(pAdptArray->pElemARR[num]);
    }
    pAdptArray->pElemARR[num] = pAdptArray->copy_func(pNewElement);
    pAdptArray->array_size = (num >= pAdptArray->array_size) ? (num + 1) : pAdptArray->array_size;
    return SUCCESS;
}


void DeleteAdptArray(PAdptArray pAdptArray){
    if(pAdptArray == NULL){
        return;
    }
    for(int i = 0; i < pAdptArray->array_size; ++i){
        if((pAdptArray->pElemARR)[i] != NULL){
            pAdptArray->del_func((pAdptArray->pElemARR)[i]);
        }
    }
    free(pAdptArray->pElemARR);
    free(pAdptArray);
}

PElement GetAdptArrayAt(PAdptArray pAdptArray, int num){
    if(pAdptArray == NULL){
        return NULL;
    }
    if(pAdptArray->array_size <= num){
        return NULL;
    }
    if(num < 0){
        return NULL;
    }
    if((pAdptArray->pElemARR)[num] == NULL){
        return NULL;
    }
    PElement temp = pAdptArray->copy_func((pAdptArray->pElemARR)[num]);
    return temp;
}

int GetAdptArraySize(PAdptArray pAdptArray){
    if(pAdptArray == NULL){
        return -1;
    }
    return pAdptArray->array_size;
}

void PrintDB(PAdptArray pAdptArray){
    if(pAdptArray == NULL){
        return;
    }
    for(int i = 0; i < pAdptArray->array_size; ++i){
        if((pAdptArray->pElemARR)[i] != NULL){
            pAdptArray->print_func(pAdptArray->pElemARR[i]); 
        }
    }
}














