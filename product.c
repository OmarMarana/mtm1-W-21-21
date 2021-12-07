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
    MtmProductData data;
    MtmCopyData copyData;
    MtmFreeData freeData;
    MtmGetProductPrice GetProductPrice;
};

Product productCreate(const unsigned int id, const char *name,
                      const double amount, const MatamikyaAmountType amountType,
                      const MtmProductData customData, MtmCopyData copyData,
                      MtmFreeData freeData, MtmGetProductPrice prodPrice) {



}

void productDestroy(Product product)
{

}

Product productCopy(Product product)//convert to asCopyElement
{

}

int productCompare(Product product)
{

}

int productReturnId(Product product)
{

}

