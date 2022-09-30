#include<stdio.h>
#include<stdlib.h>

struct Node
{
    int data;
    struct Node *prev, *next;
};
/*
    function initLinkList will initialize the head of a linked list.
    parameter head represent the head of a linked list.
*/



void initLinkList(struct Node **head)
{
    *head = NULL;
}
/*
    function addToHead will insert a node which hold data into linked list from head of the linked list.
    parameter head represent the head of a linked list.
    parameter data represent the data to insert.
*/
void addToHead(struct Node **head, int data)
{
    //創建一個新的Node
    struct Node *buf_node = (struct Node*)malloc(sizeof(struct Node));
    buf_node->data = data;
    buf_node->prev = NULL;
    buf_node->next = NULL;

    //linkedlist為空的情形
    if((*head) == NULL)
    {
        *head = buf_node;
    }
    //已經存在Node
    else {
        (*head)->prev = buf_node;
        buf_node->next = (*head);
        *head = buf_node;
    }
}
/*
    function addToHead will insert a node which hold data into linked list from tail of the linked list.
    parameter head represent the head of a linked list.
    parameter data represent the data to insert.
*/
void addToTail(struct Node **head, int data)
{
    //創建一個新的Node
    struct Node *buf_node = (struct Node*)malloc(sizeof(struct Node));
    buf_node->data = data;
    buf_node->prev = NULL;
    buf_node->next = NULL;

    //linkedlist為空的情形
    if((*head) == NULL)
    {
        *head = buf_node;
    }
    //已經存在Node
    else {
        struct Node *iter = (*head);
        while(iter->next != NULL)
            iter = iter->next;

        iter->next = buf_node;
        buf_node->prev = iter;
    }
}
/*
    function deleteData will search from head to find the first node which hold the data and remove it.
    parameter head represent the head of a linked list.
    parameter data represent the data to be search.
*/
void deleteData(struct Node **head, int data)
{
    struct Node *iter = *head;
    while(iter != NULL)
    {
      if(iter->data == data)
      {
        //更新node
        if(iter->prev != NULL)
          iter->prev->next = iter->next;
        if(iter->next != NULL)
          iter->next->prev = iter->prev;

        //更新head
        if(iter == *head)
        {
          *head = iter->next;
        }

        //刪除此node
        free(iter);

        //完成後回傳
        return;
      }
      else
      {
        iter = iter->next;
      }
    }
}
/*
    function deleteData will search from head to find the first n node which hold the data and remove it.
    parameter head represent the head of a linked list.
    parameter data represent the data to be search.
    parameter n represent the max number of node to be removed.
*/
void deleteDatas(struct Node **head, int data, int n)
{
    for(int i = 0;i < n;i++)
    {
      deleteData(head, data);
    }
}
/*
    function display will print out all the data in the linked list from the head
    there is a \n in the end of each print
    output example:
    if your linked list data is 5, 4, 3, 2, 1
    then you should print out "(5, 4, 3, 2, 1)" with the content in quotes but without the quotes
    parameter head represent the head of a linked list.
*/
void display(struct Node *head)
{
    struct Node *iter = head;
    int counter = 0;
    printf("(");

    while(iter != NULL)
    {
      if(counter != 0)
        printf(", ");
      
      printf("%d", iter->data);
      iter = iter->next;

      counter++;
    }
    printf(")\n");
}

/*int main()
{
  struct Node *list;
  struct Node **list_add = &list;
  initLinkList(list_add);
  display(list);

  addToHead(list_add, 5);
  display(list);
  addToHead(list_add, 6);
  display(list);
  addToHead(list_add, 7);
  display(list);
  addToHead(list_add, 8);
  display(list);
  addToHead(list_add, 9);
  display(list);

  addToTail(list_add, 3);
  display(list);
  addToTail(list_add, 3);
  display(list);
  addToTail(list_add, 3);
  display(list);

  deleteData(list_add, 3);
  display(list);
  deleteData(list_add, 3);
  display(list);
  deleteData(list_add, 3);
  display(list);
  deleteData(list_add, 3);
  display(list);

  addToHead(list_add, 5);
  display(list);
  addToHead(list_add, 6);
  display(list);
  addToHead(list_add, 7);
  display(list);

  deleteData(list_add, 5);
  display(list);
  deleteData(list_add, 6);
  display(list);
  deleteData(list_add, 7);
  display(list);
  addToHead(list_add, 5);
  display(list);
  addToHead(list_add, 6);
  display(list);
  addToHead(list_add, 7);
  display(list);

  deleteData(list_add, 5);
  display(list);
  deleteData(list_add, 6);
  display(list);
  deleteData(list_add, 7);
  display(list);
  addToHead(list_add, 5);
  display(list);
  addToHead(list_add, 6);
  display(list);
  addToHead(list_add, 7);
  display(list);

  deleteData(list_add, 5);
  display(list);
  deleteData(list_add, 6);
  display(list);
  deleteData(list_add, 7);
  display(list);
}*/