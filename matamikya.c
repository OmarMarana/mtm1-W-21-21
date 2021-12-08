//
// Created by omarm on 06/12/2021.
//
#include "matamikya.h"
#include "amount_set.h"
#include "order.h"
#include "product.h"
#include "set.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define FIRST_SMALL_LETTER 'a'
#define Last_SMALL_LETTER 'z'
#define FIRST_CAPITAL_LETTER 'A'
#define LAST_CAPITAL_LETTER 'Z'
#define FIRST_DIGGIT 0
#define LAST_DIGGIT 9
#define HALF 0.5


struct Matamikya_t
{
    AmountSet products;
    Set orders;
    unsigned int num_of_orders_created ;
};

//returns true if the name starts with a letter or a number
static bool checkIfNameStartWithLetterOrNumber(const char* name)
{
    if((name[0] >= FIRST_SMALL_LETTER && name[0] <= Last_SMALL_LETTER) || 
    (name[0] >= FIRST_CAPITAL_LETTER && name[0] <= LAST_CAPITAL_LETTER) || 
    (name[0] >= FIRST_DIGGIT && name[0] <= LAST_DIGGIT))
    {
        return true;
    }
    return false;
}


static bool checkIfConsistentWithAmountType(const double amount, const MatamikyaAmountType amountType)
{
    int amount_int = (int)amount;
    int delta = amount - amount_int;
    if(amountType == MATAMIKYA_INTEGER_AMOUNT)
    {
        return delta == 0;
    }
    else if(amountType == MATAMIKYA_HALF_INTEGER_AMOUNT)
    {
        return delta == 0 || delta == HALF;
    }

    return true;
}


Matamikya matamikyaCreate()
{
    
    Matamikya new_matamikya = malloc(sizeof(*new_matamikya));
    new_matamikya->products = NULL;
    new_matamikya->orders = NULL;
    new_matamikya->num_of_orders_created = 0;
    if(new_matamikya==NULL)
    {
        return NULL;
    }
    AmountSet new_products_as = asCreate((CopyASElement)productCopy,(FreeASElement)productDestroy,
    (CompareASElements)productCompare);
    if(new_products_as == NULL)
    {
        matamikyaDestroy(new_matamikya);
        return NULL;
    }
    
    new_matamikya->products = new_products_as;

    Set new_orders = setCreate((copySetElements)orderCopy, (freeSetElements)orderDestroy,
    (compareSetElements) orderCompare);
    if(new_orders ==NULL)
    {
        matamikyaDestroy(new_matamikya);
        return NULL;
    }

    new_matamikya->orders = new_orders;
    
    return new_matamikya;
   
}

void matamikyaDestroy(Matamikya matamikya)
{
    if(matamikya==NULL)
    {
        return;
    }
    asDestroy(matamikya->products);
    setDestroy(matamikya->orders);
    free(matamikya);
}

MatamikyaResult mtmNewProduct(Matamikya matamikya, const unsigned int id, const char *name,
                              const double amount, const MatamikyaAmountType amountType,
                              const MtmProductData customData, MtmCopyData copyData,
                              MtmFreeData freeData, MtmGetProductPrice prodPrice)
{
    
    if(matamikya == NULL ||  name ==NULL || customData == NULL || copyData == NULL || freeData == NULL
    || prodPrice == NULL )
    {
        return MATAMIKYA_NULL_ARGUMENT;
    }
    if(strlen(name) == 0 || checkIfNameStartWithLetterOrNumber(name)==false)
    {
        return MATAMIKYA_INVALID_NAME;
    }


    if(amount < 0 || checkIfConsistentWithAmountType(amount , amountType)== 0)
    {
        return MATAMIKYA_INVALID_AMOUNT; 
    }

    bool product_found= false;

    AS_FOREACH(Product, current_product, matamikya->products)
    {
        if(productGetId(((Product)current_product)) == id)
        {
            product_found = true;
        }

        //*********************************************************************
        //*********************************************************************
        //*********************************************************************
        //*********************************************************************
        //*********************************************************************
        // productDestroy(current_product);
        //*********************************************************************
        //*********************************************************************
        //*********************************************************************
        //*********************************************************************
        //*********************************************************************

    }

    if(product_found == true)
    {
        return MATAMIKYA_PRODUCT_ALREADY_EXIST;
    }


    // assuming that asRegister puts a copy of AsElement :
    Product new_product = productCreate(id,name,amountType,customData,copyData,freeData,prodPrice);
    if(new_product == NULL)
    {
        return MATAMIKYA_OUT_OF_MEMORY;
    }

    AmountSetResult register_res = asRegister(matamikya->products,new_product);
    if(register_res==AS_NULL_ARGUMENT)
    {
        productDestroy(new_product);
        return MATAMIKYA_NULL_ARGUMENT;
    }
    // AmountSetResult change_amount_res =asChangeAmount(matamikya->products,new_product,amount);
    asChangeAmount(matamikya->products,new_product,amount);

    productDestroy(new_product);
    return MATAMIKYA_SUCCESS;
    // check assert
}

MatamikyaResult mtmChangeProductAmount(Matamikya matamikya, const unsigned int id, const double amount)
{
    if(matamikya == NULL)
    {
        return MATAMIKYA_NULL_ARGUMENT;
    }
    
    AS_FOREACH(Product, current_product, matamikya->products)
    {
        if(productGetId(((Product)current_product)) == id)
        {
            if(checkIfConsistentWithAmountType(amount , productGetAmountType((Product)current_product))==false)
            {
                return MATAMIKYA_INVALID_AMOUNT; 
            }
            AmountSetResult change_amount_res = asChangeAmount(matamikya->products,current_product , amount);
            if(change_amount_res == AS_INSUFFICIENT_AMOUNT)
            {
                return MATAMIKYA_INSUFFICIENT_AMOUNT; 
            }
            if(change_amount_res == AS_SUCCESS)
            {
                return MATAMIKYA_SUCCESS;
            }
        }
       
        //*********************************************************************
        // productDestroy(current_product);
        //*********************************************************************
    
    }

    return MATAMIKYA_PRODUCT_NOT_EXIST; 
}


MatamikyaResult mtmClearProduct(Matamikya matamikya, const unsigned int id)
{
    if(matamikya == NULL)
    {
        return MATAMIKYA_NULL_ARGUMENT;
    }


    bool product_found= false;

    AS_FOREACH(Product, current_product, matamikya->products)
    {
        if(productGetId(((Product)current_product)) == id)
        {
            asDelete(matamikya->products, current_product);
            product_found = true;
            break;
        }
        
        //*********************************************************************
        //*********************************************************************
        //*********************************************************************
        //*********************************************************************
        //*********************************************************************
        // productDestroy(current_product);
        //*********************************************************************
        //*********************************************************************
        //*********************************************************************
        //*********************************************************************
        //*********************************************************************
    
    }

    if(product_found == false)
    {
        return MATAMIKYA_PRODUCT_NOT_EXIST;
    }

    SET_FOREACH(Order, current_order, matamikya->orders)
    {
        AS_FOREACH(Product, current_product, orderGetProducts((Order)current_order))
        {
            asDelete(orderGetProducts((Order)current_order),current_product);
            break;
        }
        //*******
        //check if setGetFirst and setGetNext return the element itself or a copy of it :C no sanwiches this time
        //*******
    }    
    
   return MATAMIKYA_SUCCESS; 
}


unsigned int mtmCreateNewOrder(Matamikya matamikya)
{
    if(matamikya == NULL)
    {
        return 0;
    }
    
    
    int new_order_id = matamikya->num_of_orders_created +1;
    Order new_order = orderCreate(new_order_id);
    if(new_order == NULL)
    {
        return 0;
    }

    SetResult res= setAdd(matamikya->orders, new_order);
    if(res != SET_SUCCESS)
    {
        orderDestroy(new_order);
        return 0;
    }

    matamikya->num_of_orders_created++;
    orderDestroy(new_order);
    return SET_SUCCESS;

        
}

MatamikyaResult mtmChangeProductAmountInOrder(Matamikya matamikya , const unsigned int orderId,
                                     const unsigned int productId, const double amount)
{

//  * if 'amount' < 0 then this amount should be decreased from the product in the order.
//  * if 'amount' > 0 then this amount should be added to the product in the order.
//  * if 'amount' = 0 then nothing should be done.
//  * please note:
//  *  1) If the amount to decrease('amount' < 0) is *larger or equal* then the amount of the product in the
//  *     order, then the product is removed entirely from the order.
//  *  2) If 'amount' > 0 and the product doesn't exist inside the order then you should add it to the order
//  *     with the amount given as argument.
   if(matamikya == NULL)
    {
      return MATAMIKYA_NULL_ARGUMENT;  
    }
      SET_FOREACH(Order, current_order, matamikya->orders)
    {
        if(orderGetId(current_order)==orderId)
        {
            AS_FOREACH(Product, current_product, orderGetProducts((Order)current_order))
            {
                if(productGetId(((Product)current_product)) == productId)
                {
                    if(checkIfConsistentWithAmountType(amount , productGetAmountType((Product)current_product))==false)
                    {
                      return MATAMIKYA_INVALID_AMOUNT;
                    }
                    AmountSetResult change_amount_res = asChangeAmount(orderGetProducts((Order)current_order),
                    current_product , amount);
                    double new_amount;
                    asGetAmount(orderGetProducts((Order)current_order, current_product, &new_amount);

                    if(change_amount_res == AS_INSUFFICIENT_AMOUNT || new_amount==0)
                    {
                        asDelete(orderGetProducts((Order)current_order, current_product);
                        return MATAMIKYA_SUCCESS;
                    }
                    //if we got here then the produts's amount has been changed successfully 
                    return MATAMIKYA_SUCCESS;
                    
                }
            }
            //*******
            //check if setGetFirst and setGetNext return the element itself or a copy of it :C no sanwiches this time
            //*******
            if(amount>0)
            {
                Product product_to_update;
                AS_FOREACH(Product, current_product, matamikya->products)
                {
                    if(productGetId((Product)current_product) ==productId)
                    {
                        product_to_update = current_product;
                    }
                }
                AmountSetResult register_res=asRegister(orderGetProducts((Order)current_order), product_to_update);
                if(register_res==AS_OUT_OF_MEMORY)
                {
                    return MATAMIKYA_OUT_OF_MEMORY;
                }
                asChangeAmount(orderGetProducts((Order)current_order),product_to_update,amount);
            }
            return MATAMIKYA_PRODUCT_NOT_EXIST;
        }
    }  
    return MATAMIKYA_ORDER_NOT_EXIST;
    
}



MatamikyaResult mtmShipOrder(Matamikya matamikya, const unsigned int orderId)
{
    if(matamikya == NULL)
    {
        return MATAMIKYA_NULL_ARGUMENT;

    }

    bool order_exist = false;
    Order order_to_ship = NULL;
    SET_FOREACH(Order, current_order, matamikya->orders)
    {
        if(orderGetId((Order)current_order) == orderId)
        {
            order_to_ship = (Order)current_order;
            order_exist = true;
            AS_FOREACH(Product, current_product_in_order, orderGetProducts((Order)current_order))
            {
                double order_product_amount; 
                double matamikya_product_amount;
                //************************************
                // check for errors in asGetAmount
                //************************************
                asGetAmount(orderGetProducts((Order)current_order),current_product_in_order,&order_product_amount);
                asGetAmount(matamikya->products, current_product_in_order ,&matamikya_product_amount);
                if(matamikya_product_amount < order_product_amount)
                {
                    return MATAMIKYA_INSUFFICIENT_AMOUNT;
                }
            }
            break;
        }
    }
    if(order_exist == false)
    {
        return MATAMIKYA_ORDER_NOT_EXIST;
    }

    //if reached this point then it means that the order exists and the amount is indeed sufficient
    //now the amount of each product in the order should be reduced from the product amount in the matamikya
    //the profits must be calculated and amount_sold in each prodct must be updated
    //and mfinally the order must be destroyed and removed from the orders SET in matamikya
    
    double order_product_amount; 
    AS_FOREACH(Product, current_order_product, orderGetProducts((Order)order_to_ship))
    {
        //change amount in AS product in matamikya
        //check AS functions errors
        asGetAmount(orderGetProducts((Order)order_to_ship), current_order_product, &order_product_amount);
        asChangeAmount(matamikya->products,current_order_product,order_product_amount);
    }
    
    
    /*
    MATAMIKYA_NULL_ARGUMENT - if a NULL argument is passed.
    MATAMIKYA_ORDER_NOT_EXIST - if matamikya does not contain an order with
    the given orderId.
    MATAMIKYA_INSUFFICIENT_AMOUNT - if the order contains a product with an amount
    that is larger than its amount in matamikya.
    MATAMIKYA_SUCCESS - if the order was shipped successfully.
    
    
    */
}
