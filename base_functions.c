#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "functions.h"

#define MAXPRODUCTS 100

struct TLIST* PRODUCTS = NULL;


int BASE_DELETE(struct TSHOP tsPRODUCT)
{
    struct TLIST* stPRODUCTS  = PRODUCTS;
    
    while (stPRODUCTS != NULL) {
        if (strcmp(PRODUCTS->PRODUCT.PRODUCT_NAME, tsPRODUCT.PRODUCT_NAME) == 0 
         && strcmp(PRODUCTS->PRODUCT.CATEGORY, tsPRODUCT.CATEGORY)         == 0)
        {
            if (stPRODUCTS->prev == NULL && stPRODUCTS->next == NULL) {
                PRODUCTS = NULL;
            } else if (stPRODUCTS->prev == NULL && stPRODUCTS->next != NULL) {
                stPRODUCTS->next->prev = NULL;
                free(stPRODUCTS);
            } else if (stPRODUCTS->prev != NULL && stPRODUCTS->next == NULL) {
                stPRODUCTS->prev->next = NULL;
            } else if (stPRODUCTS->prev != NULL && stPRODUCTS->next != NULL){
                stPRODUCTS->next->prev = stPRODUCTS->prev;
                stPRODUCTS->prev->next = stPRODUCTS->next;
            } else {
                return 0;
            }
            free(stPRODUCTS);
            return 1;
        }
        stPRODUCTS = stPRODUCTS->next;
    }
    
    return 0;
}

int BASE_UPDATE(struct TSHOP tsPRODUCT)
{
    struct TLIST* stPRODUCTS  = PRODUCTS;
    
    while (stPRODUCTS != NULL) {
        if (strcmp(PRODUCTS->PRODUCT.PRODUCT_NAME, tsPRODUCT.PRODUCT_NAME) == 0 
         && strcmp(PRODUCTS->PRODUCT.CATEGORY, tsPRODUCT.CATEGORY)         == 0)
        {
            stPRODUCTS->PRODUCT.PRICE = tsPRODUCT.PRICE;
            strcpy(stPRODUCTS->PRODUCT.NOTE, tsPRODUCT.NOTE);
            return 1;
        } 
        stPRODUCTS = stPRODUCTS->next;
    }
    
    return 0;
}

int BASE_INSERT(struct TSHOP tsPRODUCT)
{
    struct TLIST* stPRODUCTS  = PRODUCTS;
    struct TLIST* stPRODUCTS2 = PRODUCTS;
    
    if (stPRODUCTS != NULL) {
        
        while (stPRODUCTS->next != NULL) {
            stPRODUCTS->next;
        }
        
        stPRODUCTS2          = (struct TLIST*) calloc(100, sizeof(struct TLIST));
        if (!stPRODUCTS2) {
            return 0;
        }
        stPRODUCTS2->PRODUCT = tsPRODUCT;
        stPRODUCTS2->next    = NULL;
        stPRODUCTS2->prev    = stPRODUCTS;
        
        stPRODUCTS->next     = stPRODUCTS2;
    }
    else {
        PRODUCTS          = (struct TLIST*) calloc(100, sizeof(struct TLIST));
        if (!PRODUCTS) {
            return 0;
        }
        PRODUCTS->PRODUCT = tsPRODUCT;
        PRODUCTS->next    = NULL;
        PRODUCTS->prev    = NULL;
    }
    
    return 1;
}