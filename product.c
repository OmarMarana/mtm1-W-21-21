//
// Created by omarm on 06/12/2021.
//

#include "product.h"
#include "matamikya.h"

struct Product_t
{
    unsigned int id;
    char* name;
    double amount_of_sold;
    MatamikyaAmountType amount_type;
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
if(id<0 || name == NULL || amountType == NULL || customData == NULL || 
copyData == NULL || freeData == NULL || prodPrice == NULL)
Product newProduct = malloc(sizeof(*newProduct));
	if (!newProduct)
	{
		return NULL;
	}
	newProduct->id = id;
    newProduct->name = name;
    newProduct->amount_of_sold = 0;
	newProduct->amount_type = amount_type;
	newProduct->customData = customData;
	newProduct->copyData = copyData;
	newProduct->freeData = freeData;
	newProduct->prodPrice = prodPrice;

	return newProduct;
}

void productDestroy(Product product)
{
if (!product) {
		return;
	}
	free(product);
}

Product productCopy(Product product)//convert to asCopyElement at matamikya
{
	if (!product) 
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
    if(product1 == NULL || product2 == NULL) 
    {
        return 
    }
	if (product1->id == product2->id)
		return 0;
}

int productReturnId(Product product)
{
 if(!product)// i think no need cause we use this func in matamikya only if products not null.


}

