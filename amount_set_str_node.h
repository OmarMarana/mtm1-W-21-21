#ifndef AMOUNT_SET_STR_NODE_H_
#define AMOUNT_SET_STR_NODE_H_

#ifndef AMOUNT_SET_STR_H_
#include "amount_set_str.h"
#endif

typedef struct node_t *Node;

typedef int (*CmpFunction)(const char*, const char*);


/** Type used for returning error codes from node functions */
typedef enum NodeResult_t {
    NODE_SUCCESS = 1,
    NODE_OUT_OF_MEMORY,
    NODE_NULL_ARGUMENT
} NodeResult;

/* compare_key_func may have to be renamed due to conventions */
Node nodeCreate();
NodeResult nodeAdd(Node node_head, Node new_node, CmpFunction strcmp);

/* Returns the node with the same key. null if not found.  */
//Node nodeGetByKey(Node list, MapKeyElement key, compareMapKeyElements compare_func);

/*Destroys a linked list*/
//void nodeDestroy(Node list, freeMapDataElements freeDataElement,freeMapKeyElements freeKeyElement);

void nodeDestroy(Node list);


/*Frees a single node in a list using the free function supplied by the user*/
void nodeFree(Node node);

void NodeSetTheName(Node node, char* name);

int nodeGetAmount(Node node);
void nodeSetAmount(Node node,int amount);



/* get */
Node nodeGetNext(Node node);
char* nodeGetName(Node node);
//MapDataElement nodeGetData(Node node);

/* set */
 void nodeSetNext(Node node, Node next);

#endif /* AMOUNT_SET_STR_NODE_H_ */
