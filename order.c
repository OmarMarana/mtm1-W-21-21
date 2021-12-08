//
// Created by omarm on 06/12/2021.
//

#include "order.h"
#include "amount_set.h"
#include "product.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

struct Order_t
{
    unsigned int id;
    AmountSet products;
    
};

Order orderCreate(unsigned int id)
{
    Order order_to_create = malloc(sizeof(*order_to_create));
    if(order_to_create == NULL)
    {
        return NULL;
    }

    order_to_create->products =NULL;

    //we get this id from the matamikya func
    order_to_create->id = id;
    
    order_to_create->products = asCreate((CopyASElement)productCopy,(FreeASElement)productDestroy,
    (CompareASElements)productCompare);
    if( order_to_create->products == NULL)
    {
        orderDestroy(order_to_create);
        return  NULL;   
    }

    return order_to_create;
}


void orderDestroy(Order order)
{
    if(order == NULL)
    {
        return ;
    }
    asDestroy(order->products);
    free(order);
}

Order orderCopy(Order order)
{
    if(order == NULL)
    {
        return NULL;
    }

    Order order_to_create = malloc(sizeof(*order_to_create));
    if(order_to_create == NULL)
    {
        return NULL;
    }

    AmountSet new_products_as = asCopy(order->products);
    if(new_products_as == NULL)
    {
        orderDestroy(order_to_create);
        return NULL;
    }
    order_to_create->products = new_products_as;
    order_to_create->id = order->id;
    

    return order_to_create;  
}

int orderCompare(Order order1, Order order2)
{
    int delta = order1->id - order2->id;
    return delta;
}

AmountSet orderGetProducts(Order order)
{
    return order->products;
}

unsigned int orderGetId(Order order)
{
    return order->id;
}