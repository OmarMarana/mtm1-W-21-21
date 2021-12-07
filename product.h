//
// Created by omarm on 06/12/2021.
//

#ifndef MTM1_PRODUCT_H
#define MTM1_PRODUCT_H

#include <stdio.h>
#include "matamikya.h"

typedef enum {
    PRODUCT_OUT_OF_MEMORY,
    PRODUCT_NULL_ARGUMENT,
    PRODUCT_SUCCESS
} ProductResult ;

typedef struct product_t *Product;

/**
* productCreate: Allocates a new empty product.
*
* @param player_id- The id of second student in this game. Must be positive.
* @param result - The winner in this game.
* @param time - How long this game is.

* @return
* 	NULL - if one of the parameters is NULL or allocations failed.
* 	A new roduct in case of success.
*/
Product productCreate(const unsigned int id, const char *name,
                      const double amount, const MatamikyaAmountType amountType,
                      const MtmProductData customData, MtmCopyData copyData,
                      MtmFreeData freeData, MtmGetProductPrice prodPrice);

/**
* gameDestroy: Free a game from memory.
*
* @param game - The game to free from memory. If game is NULL nothing will be done.
*/
void productDestroy(Product product);

/**
* gameCopy: Creates a copy of target game.
*
* @param game - Target game.
*
* @return
* 	NULL if a NULL was sent or a memory allocation failed.
* 	A Game containing the same elements as game otherwise.
*/
Product productCopy(Product product);


//return 0 if same id
int productCompare(Product product);
int productReturnId(Product product);




/**
* gameReturnPlayer: Return the first player in this game.
*
* @param game - Target game.
*
* @return
* 	-1 if a NULL pointer was sent.
* 	Otherwise the id of the second student in this game.
*/
int gameReturnPlayer(Game game);

/**
* gameReturnTime: Returns the time of this game.
*
* @param game - Target game.
*
* @return
* 	-1 if a NULL pointer was sent.
* 	Otherwise the time of this game.
*/
int gameReturnTime(Game game);

/**
*  gameReturnResult: Returns the winner of this game.
*
* @param game - Target game.
*
* @return
* 	-1 if a NULL pointer was sent.
* 	Otherwise the winner of this game.
*/
Winner gameReturnResult(Game game);




/**
* gameSetPlayer: Sets the id of the first student in this game.
*
* @param game - Target game.
* @param player - The new first student.
*
* @return
* 	GAME_NULL_ARGUMENT if a NULL pointer was sent or invalid.
*/
GameResult gameSetPlayer(Game game, int player);

/**
* gameSetWinner: Sets the winner of this game.
*
* @param game - Target game.
* @param result - The new winner.
*
* @return
* 	GAME_NULL_ARGUMENT if a NULL pointer was sent or invalid.
*/
GameResult gameSetWinner(Game game, Winner result);

/**
* gameSetTime: Sets the time of this game.
*
* @param game - Target game.
* @param time - The new time.
*
* @return
* 	GAME_NULL_ARGUMENT if a NULL or invalid pointer was sent.
*/
GameResult gameSetTime(Game game, int time);

#endif //MTM1_PRODUCT_H
