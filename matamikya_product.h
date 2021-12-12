//
// Created by omarm on 06/12/2021.
//

#ifndef MATAMIKYA_PRODUCT_H
#define MATAMIKYA_PRODUCT_H

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
* @param id - new product id. Must be non-negative, and unique.
* @param name - name of the product, e.g. "apple". Must be non-empty.
* @param amountType - defines what are valid amounts for this product.
* @param customData - pointer to product's additional data.
* @param copyData - function pointer to be used for copying product's additional data.
* @param freeData - function pointer to be used for free product data.
* @param prodPrice - function pointer to be used for getting the price of some
 *      product.

* @return
* 	NULL - if one of the parameters is NULL or un legal or allocations failed.
* 	A new product in case of success.
*/
Product productCreate(const unsigned int id, const char *name,
                      const MatamikyaAmountType amountType,
                      const MtmProductData customData, MtmCopyData copyData,
                      MtmFreeData freeData, MtmGetProductPrice prodPrice);


/**
* productDestroy: Free a product from memory.
*
* @param product - The product to free from memory. If product is NULL nothing will be done.
*/
void productDestroy(Product product);

/**
* productCopy: Creates a copy of target product.
*
* @param product - Target product.
*
* @return
* 	NULL if a NULL was sent or a memory allocation failed.
* 	A Product containing the same elements as product otherwise.
*/
Product productCopy(Product product);

/**
* productCompare: compares the id of 2 products.
*
* @param product1 - Target product 1.
* @param product1 - Target product 2.
*
* @return
* 	positive number if the id of the first product is bigger than the id of the second product.
* 	negative number if the id of the first product
 * 	is smaller than the id of the second product.
* 	0 otherwise.
*/
int productCompare(Product product1,Product product2);

/**
* productGetId: return the id of this product.
*
* @param product - Target product.
*
* @return
* the id of this product.
*/
int productGetId(Product product);

/**
* productGetName: return the name of this product.
*
* @param product - Target product.
*
* @return
* the name of this product.
*/
char* productGetName(Product product);

/**
* productGetAmountType: return the AmountType of this product.
*
* @param product - Target product.
*
* @return
* the AmountType of this product.
*/
MatamikyaAmountType productGetAmountType(Product product);

/**
* productChangeAmountOfSold: add delta to the amount of sold of this product.
*
* @param product - Target product.
* @param delta - The number of bought of this product.
*/
void productChangeAmountOfSold(Product product,double delta);

/**
* productGetAmountOfSold: return the amount of sold of this product.
*
* @param product - Target product.
*
* @return
* amount of sold of this product.
*/
int productGetAmountOfSold(Product product);

/**
* productGetPrice: return the price of this product according to the bought amount of it.
*
* @param product - Target product.
* @param amount - amount of bought.
*
* @return
* price of this product according to the bought amount of it.
*/
double productGetPrice(Product product, double amount);

/**
* productGetPrice: return the price of this product per unit.
*
* @param product - Target product.
*
* @return
* the price of this product per unit.
*/
double productGetPricePerUnit(Product product);


#endif //MATAMIKYA_PRODUCT_H
