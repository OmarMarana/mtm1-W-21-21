//
// Created by omarm on 06/12/2021.
//

#include "stdbool.h"
#include "order.h"
#include "amount_set.h"
#include "product.h"

struct Order_t
{
    unsigned int id;
    AmountSet products;
    bool shipped;
};

Order orderCreate(unsigned int id)
{
    Order order_to_create = malloc(sizeof(*order_to_create));
    if(order_to_create == NULL)
    {
        return NULL;
    }

    //we get this id from the matamikya func
    order_to_create->id = id;
    order_to_create->products = asCreate()
    //as_to_create->head = nodeCreate();

    /*NOTE: iterator may need malloc*/
    return as_to_create;
}