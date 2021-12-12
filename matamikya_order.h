//
// Created by omarm on 06/12/2021.
//

#ifndef MATAMIKYA_ORDER_H
#define MATAMIKYA_ORDER_H
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


/**
 * orderCreate: Allocates a new empty amount order.
 *
 * @param id - none negative number.
 * @return
 *     NULL - if one of the parameters is unlegal or allocations failed.
 *     A new order in case of success.
 */
Order orderCreate(unsigned int id);

/**
* orderDestroy: Free a order from memory.
*
* @param order - The order to free from memory. If order is NULL nothing will be done.
*/
void orderDestroy(Order order);

/**
* orderCopy: Creates a copy of target order.
*
* @param order - Target order.
*
* @return
* 	NULL if a NULL was sent or a memory allocation failed.
* 	A Order containing the same elements as order otherwise.
*/
Order orderCopy(Order order);

/**
* orderCompare: compares the id of 2 orders.
*
* @param order1 - Target order 1.
* @param order1 - Target order 2.
*
* @return
* 	positive number if the id of the first order is bigger than the id of the second order.
* 	negative number if the id of the first order is smaller than the id of the second order.
* 	0 otherwise.
*/
int orderCompare(Order order1, Order order2);

/**
* orderGetProducts: return the amount set of products in this order.
*
* @param order - Target order.
*
* @return
*  the amount set of products in this order.
*/
AmountSet orderGetProducts(Order order);

/**
* orderGetId: return the id of this order.
*
* @param order - Target order.
*
* @return
*  the id of this order.
*/
unsigned int orderGetId(Order order);


#endif //MATAMIKYA_ORDER_H



