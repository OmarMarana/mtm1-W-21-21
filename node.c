#include "node.h"
#include "amount_set_str.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

//The struct definition:
struct node_t
{
    char * name;
    int amount;
    struct node_t *next;
};

/*Creates empty node
  return NULL if malloc failed.
  else, return the node*/
Node nodeCreate()
{
    Node new_node = malloc(sizeof(*new_node));
    if(new_node == NULL)
    {
        return NULL;   
    }

    new_node->name = NULL;
    new_node->amount = 0;
    new_node->next = NULL;

    return new_node;
}


void nodeDestroy(Node list)
{
    while(list != NULL)
    {
        Node node_to_delete = list;
        list = list->next;
        nodeFree(node_to_delete);
    }
}


void nodeFree(Node node )
{   
    free(node->name);
    free(node);
}





/*  add element to the map's Node.
    the new element will be in-place in LOW to HIGH order by comapre-key.
    You must check (before using this function) if new_node is not in the list already.
    this function assumes that 'new_node' is not in the list.

    NodeResult nodeAdd(Node node_head, Node new_node, compareMapKeyElements compare_key_func);

*/
NodeResult nodeAdd(Node node_head, Node new_node, CmpFunction strcmp) // may have to change strcmp name bcus the name exists already
{
    if(node_head == NULL || new_node == NULL)
    {
        return NODE_NULL_ARGUMENT;
    }

    Node temp_previous = node_head;
    Node temp = nodeGetNext(node_head);

    while(temp != NULL)
    {
        int compare_result = strcmp(new_node->name,temp->name);
        if( compare_result > 0 )
        {
            temp_previous = temp;
            temp = nodeGetNext(temp);
        }
        else if (compare_result < 0)
        {
            nodeSetNext(temp_previous, new_node);
            nodeSetNext(new_node, temp);
            return NODE_SUCCESS;
        }
    }

    nodeSetNext(temp_previous, new_node);

    return NODE_SUCCESS;
}

/* ******************** */
/* ******* GET ******** */
/* ******************** */

/* return the next node */
Node nodeGetNext(Node node)
{
    if(node == NULL)
    {
        return NULL;
    }
    return node->next;
}

/* return the node's name. */
char* nodeGetName(Node node)
{
    if(node == NULL)
    {
        return NULL;
    }
    return node->name;
}



/* set the node's name. */
void nodeSetname(Node node, char* name)
{
    if(node == NULL || name == NULL )
    {
        return;
    }
    node->name = name;
}

/* set the node's next node. */
void nodeSetNext(Node node, Node next)
{
    if(node == NULL)
    {
        return;
    }
    node->next = next;
}

int nodeGetAmount(Node node)
{
    return node->amount;
}

void nodeSetAmount(Node node,int amount)
{
    if(node==NULL)
    {
        return;
    }
    node->amount = amount;
}

////should check if all the function un the h.file are here






