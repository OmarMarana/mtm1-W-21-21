//
// Created by omarm on 06/12/2021.
//

#ifndef MTM1_PRODUCT_H
#define MTM1_PRODUCT_H

#include <stdio.h>
#include "matamikya.h"
#include "amount_set.h"

typedef enum {
    PRODUCT_OUT_OF_MEMORY,
    PRODUCT_NULL_ARGUMENT,
    PRODUCT_SUCCESS
} ProductResult ;

typedef struct Product_t *Product;

/**
* productCreate: Allocates a new empty product.
*
* @param player_id- The id of second student in this game. Must be positive.
* @param result - The winner in this game.
* @param time - How long this game is.

* @return
* 	NULL - if one of the parameters is NULL or allocations failed.
* 	A new roduct in case of success.
*/
Product productCreate(const unsigned int id, const char *name,
                      const MatamikyaAmountType amountType,
                      const MtmProductData customData, MtmCopyData copyData,
                      MtmFreeData freeData, MtmGetProductPrice prodPrice);
                      

/**
* gameDestroy: Free a game from memory.
*
* @param game - The game to free from memory. If game is NULL nothing will be done.
*/
void productDestroy(Product product);

/**
* gameCopy: Creates a copy of target game.
*
* @param game - Target game.
*
* @return
* 	NULL if a NULL was sent or a memory allocation failed.
* 	A Game containing the same elements as game otherwise.
*/
Product productCopy(Product product);


//return 0 if same id
int productCompare(Product product1,Product product2);
int productGetId(Product product);
char* productGetName(Product product);
MatamikyaAmountType productGetAmountType(Product product);

void productChangeAmountOfSold(Product product,double delta);
int productGetAmountOfSold(Product product);

double productGetPrice(Product product, double amount);
double productGetPricePerUnit(Product product);

// ********************************************
// כתיבת תיעודים לכל הפונקציות בקבצי ה h
// ********************************************



 #endif //MTM1_PRODUCT_H
