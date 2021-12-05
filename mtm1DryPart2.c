#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdio.h>
#include <stdbool.h>



typedef enum {
    SUCCESS = 0,
    MEMORY_ERROR,
    EMPTY_LIST,
    UNSORTED_LIST,
    NULL_ARGUMENT,
} ErrorCode;

typedef struct node_t {
    int value;
    struct node_t* next;
} *Node;


Node createNode();
void destroyLinkedList(Node node);
void maybeUpdateNodeToNext(bool iterate_tmp1, Node* tmp1, Node* tmp2);
int getMinOf2Numbers(int a, int b, bool* result);
int getListLength(Node list)
{
    int counter = 0;
    while (list !=NULL)
    {
        counter++;
        list = list->next;
    }
    return counter;

}
bool isListSorted(Node list)
{
    bool status = true;
    while (list!=NULL && list->next != NULL)
    {
        if( list->value > list->next->value)
        {
            status =false;

        }
        list = list->next;
    }
    return  status;

}
void printList(Node list)
{
    printf("the list contains : \n");
//    int list_len = getListLength(list);
    int index =1;
    while (list !=NULL)
    {
        printf("element in index %d is : %d \n",index, list->value);
        list = list->next;
    }
}


ErrorCode mergeSortedLists(Node list1, Node list2, Node* mergedOut);
//create a new node
Node createNode()
{
    Node node_to_create = malloc(sizeof(*node_to_create));
    if (node_to_create == NULL)
        return NULL;
    node_to_create->value = 0;
    node_to_create->next = NULL;
    return node_to_create;
}

//destroy a list
void destroyLinkedList(Node node)
{
    if (node == NULL)
    {
        return;
    }
    destroyLinkedList(node->next);
    free(node);
}

//set iterator
void maybeUpdateNodeToNext(bool iterate_node1, Node* node1, Node* node2)
{
    if (iterate_node1 == true)
    {
        *node1 = (*node1)->next;
    }
    else
    {
        *node2 = (*node2)->next;
    }
}

// gives the min between two numbers
//result will be true if a <= b
int getMinOf2Numbers(int num1, int num2, bool* result)
{
    if (num1 <= num2)
    {
        *result = true;
        return num1;
    }
    *result = false;
    return num2;
}

ErrorCode mergeSortedLists(Node list1, Node list2, Node* mergedOut)
{
    if (list1 == NULL || list2 == NULL)
    {
        *mergedOut = NULL;
        return EMPTY_LIST;


    }
    //if lists are not sorted
    if (!isListSorted(list1) || !isListSorted(list2))
    {

        *mergedOut = NULL;
        return UNSORTED_LIST;
    }


    Node head_of_list = createNode();
    if (head_of_list == NULL)
    {

        *mergedOut = NULL;
        return MEMORY_ERROR;
    }

    Node tmp_current_name = head_of_list, tmp_node_of_list1 = list1, tmp_node_of_list2 = list2;

    bool tmp1_is_min;

    head_of_list->value = getMinOf2Numbers(tmp_node_of_list1->value, tmp_node_of_list2->value,
                               &tmp1_is_min);
    int merged_lists_length = getListLength(list1) + getListLength(list2);

    Node current_node;
    for (int i = 0; i < merged_lists_length - 1; i++)
    {
        maybeUpdateNodeToNext(tmp1_is_min, &tmp_node_of_list1, &tmp_node_of_list2);

        current_node = createNode();

        if (current_node == NULL)
        {
            *mergedOut = NULL;
            destroyLinkedList(head_of_list);
            return MEMORY_ERROR;
        }

        tmp_current_name->next = current_node;//i changed the order between 2 lines here?

        if (tmp_node_of_list1 != NULL && tmp_node_of_list2 != NULL)
        {
            current_node->value = getMinOf2Numbers(tmp_node_of_list1->value, tmp_node_of_list2->value,
                                         &tmp1_is_min);
        }

        else if (tmp_node_of_list1 == NULL)
        {
            current_node->value = tmp_node_of_list2->value;
            tmp1_is_min = false;
        }
        else if (tmp_node_of_list2 == NULL)
        {
            current_node->value = tmp_node_of_list1->value;
            tmp1_is_min = true;
        }
        tmp_current_name = current_node;
    }
    *mergedOut = head_of_list;
    return SUCCESS;
}


int main()
{
    Node list1 = createNode();
    list1->value = -1;
    Node list2 = createNode();;
    list2->value = -1;

    Node tmp1 = list1;
    Node tmp2 = list2;
    for (int i = 0; i < 1000; i+= 100) {
        list1->next = createNode();
        list1->next->value = i;
        list1 = list1->next;
    }
    list1 = tmp1;
    printList(tmp1);


    for (int i = 30; i < 40; ++i) {
        list2->next = createNode();
        list2->next->value = i;
        list2 = list2->next;

    }
    list2 =tmp2;
    printList(tmp2);

    //check if lists aren't sorted
//    list2->value = 1000;

    Node merged;
    //check if arg is null
//        ErrorCode res = mergeSortedLists(NULL,list2,&merged);
    ErrorCode res = mergeSortedLists(list1,list2,&merged);
    if(res== SUCCESS)
    {
        if(merged==NULL)
        {
            printf("merged is null\n");
        }
        printf("SUCCESSS\n");
    }
    if(res== EMPTY_LIST)
    {
        if(merged==NULL)
        {
            printf("merged is null\n");
        }
        printf("EMPTY_LIST\n");
    }
    if(res== UNSORTED_LIST)
    {
        if(merged==NULL)
        {
            printf("merged is null\n");
        }
        printf("UNSORTED_LIST\n");
    }
    if(res == NULL_ARGUMENT)
    {
        if(merged==NULL)
        {
            printf("merged is null\n");
        }
        printf("NULL_ARGUMENT\n");
    }

    destroyLinkedList(list2);
    destroyLinkedList(list1);
    printList(merged);
    destroyLinkedList(merged);

    return 0;
}
