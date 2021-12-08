//
// Created by omarm on 06/12/2021.
//

#ifndef MTM1_ORDER_H
#define MTM1_ORDER_H
#include "amount_set.h"

typedef struct Order_t *Order;

typedef enum OrderResult_t {
    ORDER_SUCCESS = 0,
    ORDER_NULL_ARGUMENT,
    ORDER_OUT_OF_MEMORY,
    ORDER_INVALID_NAME,
    ORDER_INVALID_AMOUNT,
    ORDER_PRODUCT_ALREADY_EXIST,
    ORDER_PRODUCT_NOT_EXIST,
    ORDER_ORDER_NOT_EXIST,
    ORDER_INSUFFICIENT_AMOUNT,
} OrderResult;




Order orderCreate(unsigned int id);

void orderDestroy(Order order);

Order orderCopy(Order order);

//compare ids
int orderCompare(Order order1, Order order2);

AmountSet orderGetProducts(Order order);

unsigned int orderGetId(Order order)
{
    
}




#endif //MTM1_ORDER_H



