#include "amount_set_str.h"
#include "node.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define ITERATOR_UNDEFINED NULL
#define NULL_SET -1
#define INITIAL_AMOUNT 0


struct AmountSet_t
{
    int size;
    Node node_iterator;
    Node head;
    
};



AmountSet asCreate()
{
    AmountSet as_to_create = malloc(sizeof(*as_to_create));
    if(as_to_create == NULL)
    {
        return NULL;
    }
    as_to_create->size = 0;
    as_to_create->node_iterator = NULL;
    as_to_create->head = nodeCreate();

    //as_to_create->head = nodeCreate();

    /*NOTE: iterator may need malloc*/
    return as_to_create;
}

void asDestroy(AmountSet set)
{
    if(set == NULL)
    {
        return;
    }
    asClear(set);
    nodeFree(set->head);     // check for seg fault here
    free(set);
}

AmountSet asCopy(AmountSet set)
{
    if(set == NULL)
    {
        return NULL;
    }

    AmountSet set_copy = asCreate();

    if(set_copy == NULL)
    {
        return NULL;
    }

    set_copy->size= set->size;
    //set_copy->head= set->head;   if there are bugs then check here
    
    Node iterator_next = nodeGetNext(set->head);
    while(iterator_next  != NULL)
    {
        AmountSetResult set_register_result = asRegister(set_copy, nodeGetName(iterator_next));
        if(set_register_result != AS_SUCCESS) 
        {
            asDestroy(set_copy); 
            return NULL;
        }

        iterator_next = nodeGetNext(iterator_next);
    }

    // for(char* iterator = (char*) asGetFirst(set) ; iterator ;iterator = asGetNext(set))    
    // AS_FOREACH(char*, iterator, set)
    // {
    //     AmountSetResult set_register_result = asRegister(set_copy, nodeGetName(iterator));
    //     if(set_register_result != AS_SUCCESS) 
    //     {
    //         asDestroy(set_copy); 
    //         return NULL;
    //     }
    // } 

    set->node_iterator = ITERATOR_UNDEFINED;
    set_copy->node_iterator = ITERATOR_UNDEFINED;

    return set_copy;

}

int asGetSize(AmountSet set)
{
    if(set == NULL){
        return NULL_SET;
    }
    return set->size;
}

bool asContains(AmountSet set, const char* element)
{
    if(set == NULL || element == NULL)
    {
        return false;
    }

    Node iterator_next = nodeGetNext(set->head);

    while(iterator_next  != NULL)
    {
        if(strcmp(nodeGetName(iterator_next), element) == 0)
        {
            return true;
        }
        iterator_next = nodeGetNext(iterator_next);
    }
    
    return false;
}

AmountSetResult asGetAmount(AmountSet set, const char* element, double* outAmount)
{
    if(set == NULL || element == NULL || outAmount == NULL)
    {
        return AS_NULL_ARGUMENT;
    }

    Node current_node = nodeGetNext(set->head);

    while(current_node  != NULL)
    {
        if(strcmp(nodeGetName(current_node), element) == 0)
        {
            *outAmount = nodeGetAmount(current_node);
            return AS_SUCCESS;
        }
        current_node = nodeGetNext(current_node);
    }

    return AS_ITEM_DOES_NOT_EXIST; 
}

AmountSetResult asRegister(AmountSet set, const char* element)
{
    if(set == NULL || element == NULL)
    {
        return AS_NULL_ARGUMENT;
    }
    if(asContains(set ,element))
    {  
        return AS_ITEM_ALREADY_EXISTS;
    }

    Node new_node = nodeCreate();
    if(new_node == NULL)
    {
        return AS_OUT_OF_MEMORY;
    }

    
    char* copy_name = malloc(strlen(element) +1 );
    copy_name = strcpy(copy_name,element);
    if(copy_name == NULL)
    {
        nodeFree(new_node);
        return AS_OUT_OF_MEMORY;
    }

    nodeSetAmount(new_node, INITIAL_AMOUNT);
    NodeSetTheName(new_node, copy_name);

    NodeResult add_result = nodeAdd(set->head, new_node, strcmp);

    if(add_result == NODE_SUCCESS)
    {
        set->node_iterator = ITERATOR_UNDEFINED;
        set->size++;
        return AS_SUCCESS;
    }

    nodeFree(new_node); 
    
    
    /******************************************************************************/
    /******************************************************************************/
    /******************************************************************************/
    return AS_SUCCESS;   // return SUCCESS bcus there is nothing else to return 
    /******************************************************************************/
    /******************************************************************************/
    /******************************************************************************/
    

}

AmountSetResult asChangeAmount(AmountSet set, const char* element, double amount)
{
    if(set==NULL || element == NULL)
    {
        return AS_NULL_ARGUMENT;
    }
   
    Node current_node = nodeGetNext(set->head);
    while(current_node  != NULL)
    {
        if(strcmp(nodeGetName(current_node), element) == 0)
        {
            int new_amount = nodeGetAmount(current_node) + amount;
            if(new_amount < 0)
            {
                return AS_INSUFFICIENT_AMOUNT;
            }
            nodeSetAmount(current_node, new_amount); 
            return AS_SUCCESS;
        }
        current_node = nodeGetNext(current_node);
    }
    return AS_ITEM_DOES_NOT_EXIST;
}

AmountSetResult asDelete(AmountSet set, const char* element) // remember to update set size after this op
{
    if(set == NULL || element == NULL)
    {
        return AS_NULL_ARGUMENT;
    }

    Node current_node = nodeGetNext(set->head);
    Node previous_node = set->head;

    while(current_node != NULL)
    {
        if(strcmp(nodeGetName(current_node), element) == 0)
        {
            nodeSetNext(previous_node, nodeGetNext(current_node));
            nodeFree(current_node);
            set->size--;
            return AS_SUCCESS;
        }
        previous_node = nodeGetNext(previous_node);
        current_node = nodeGetNext(current_node);
    }

    set->node_iterator = ITERATOR_UNDEFINED;
    return AS_ITEM_DOES_NOT_EXIST;
}

AmountSetResult asClear(AmountSet set)
{
    if(set == NULL)
    {
        return AS_NULL_ARGUMENT;
    }
    nodeDestroy(nodeGetNext(set->head));
    nodeSetNext(set->head, NULL);
    set->size= 0;
    set->node_iterator= NULL;
    return AS_SUCCESS;   
}

char* asGetFirst(AmountSet set)// did not return a copy of the name 
{
    if(set == NULL)
    {
        return NULL;
    }

    set->node_iterator = (set->head);
    return asGetNext(set);
}


char* asGetNext(AmountSet set) // did not return a copy of the name 
{  
    if(set == NULL || nodeGetNext(set->node_iterator) == NULL ||
       set->node_iterator == ITERATOR_UNDEFINED)
    {
        return NULL;
    }

    set->node_iterator = nodeGetNext(set->node_iterator);

    return nodeGetName(set->node_iterator);
    
}