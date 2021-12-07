//
// Created by omarm on 06/12/2021.
//

#ifndef MTM1_ORDER_H
#define MTM1_ORDER_H

typedef struct Order_t *Order;

typedef enum MatamikyaResult_t {
    ORDER_SUCCESS = 0,
    ORDER_NULL_ARGUMENT,
    ORDER_OUT_OF_MEMORY,
    ORDER_INVALID_NAME,
    ORDER_INVALID_AMOUNT,
    ORDER_PRODUCT_ALREADY_EXIST,
    ORDER_PRODUCT_NOT_EXIST,
    ORDER_ORDER_NOT_EXIST,
    ORDER_INSUFFICIENT_AMOUNT,
} MatamikyaResult;




Order orderCreate();

void orderDestroy(Order order);

Order orderCopy(Order order);

//compare ids
int orderCompare(Order order1, Order order2);




#endif //MTM1_ORDER_H



