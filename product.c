//
// Created by omarm on 06/12/2021.
//

#include "product.h"
#include "matamikya.h"
#include "amount_set.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>


struct Product_t
{
    unsigned int id;
    char* name;
    double amount_of_sold;
    MatamikyaAmountType amountType;
    MtmProductData customData;
    MtmCopyData copyData;
    MtmFreeData freeData;
    MtmGetProductPrice prodPrice;
};

Product productCreate(const unsigned int id, const char *name,
                      const MatamikyaAmountType amountType,
                      const MtmProductData customData, MtmCopyData copyData,
                      MtmFreeData freeData, MtmGetProductPrice prodPrice) //i deleted: const double amount because it will be insered
                                                                       //like a "key" into the amount_set...
{
	
if(id<0 || name == NULL || copyData == NULL || freeData == NULL || prodPrice == NULL)
{
 return NULL;
}
	Product newProduct = malloc(sizeof(*newProduct));
	
	newProduct->name = NULL;
	newProduct->customData = NULL;

	if (!newProduct)
	{
		return NULL;
	}

	newProduct->id = id;
	

	newProduct->copyData = copyData;
	newProduct->freeData = freeData;
	
	char * new_name = malloc(sizeof(char) * (strlen(name) +1));
	if(new_name == NULL)
	{
		productDestroy(newProduct);
		return NULL;
	}
	strcpy(new_name, name);
    newProduct->name = new_name;
    newProduct->amount_of_sold = 0;
	newProduct->amountType = amountType;
	

	newProduct->customData = newProduct->copyData(customData);
	if(newProduct->customData == NULL)
	{
		productDestroy(newProduct);
		return NULL;
	}
	
	newProduct->prodPrice = prodPrice;

	return newProduct;
}

void productDestroy(Product product)
{
if (product == NULL)
    {
		return;
	}
	free(product->name);
	product->freeData(product->customData);
	free(product);
}

Product productCopy(Product product)//convert to asCopyElement at matamikya
{
	if (product == NULL) 
    {
		return NULL;
	}
	Product newProduct = productCreate(product->id ,product->name,product->amountType,
    product->customData, product->copyData, product->freeData, product->prodPrice);
    if (!newProduct) 
    {
		return NULL;
	}
	newProduct->amount_of_sold = product-> amount_of_sold;
	
	return newProduct;
}

int productCompare(Product product1,Product product2)
{
   /* if(product1 == NULL || product2 == NULL) 
    {
        return 
    }*/
	int temp= product1->id - product2->id;
	return temp;
}

int productGetId(Product product)
{
// if(!product)// i think no need cause we use this func in matamikya only if products not null.
return product->id;
}

char* productGetName(Product product)
{
	return product->name;
}

MatamikyaAmountType productGetAmountType(Product product)
{
	// if(!product)// i think no need cause we use this func in matamikya only if products not null.
return product->amountType;
}


void productChangeAmountOfSold(Product product,double delta )
{
    product->amount_of_sold +=delta;
}

int productGetAmountOfSold(Product product)
{
 return product->amount_of_sold;
}

double productGetPrice(Product product, double amount)
{
	return product->prodPrice(product->customData, amount);
}

double productGetPricePerUnit(Product product)
{
	double* tmp = product->customData;
	// return ((double*)product->customData)* ;
	return *tmp;
}