#include<stdio.h>
#include<stdlib.h>

struct Node
{
    char data;
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
void addToHead(struct Node **head, char data)
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
void addToTail(struct Node **head, char data)
{
    //創建一個新的Node
    struct Node *buf_node = (struct Node*)malloc(sizeof(struct Node));
    buf_node->data = data;

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
void deleteData(struct Node **head, char data)
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

        //更新head & tail
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
void deleteDatas(struct Node **head, char data, int n)
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
      
      printf("%c", iter->data);
      iter = iter->next;

      counter++;
    }
    printf(")\n");
}

void push(struct Node **stack, char data)
{
    addToHead(stack, data);
}
/*
    function dequeue will remove a data from stack
    parameter stack represent the stack
    this function should return the data that be removed
*/
char pop(struct Node **stack)
{
    char num = (*stack)->data;
    deleteData(stack, num);
    return num;
}
/*
    function top will give the next remove data in the given stack
    parameter stack represent the stack
    this function should return the next remove data
*/
char top(struct Node *stack)
{
    return stack->data;
}
/*
    function isEmpty will determine if the given stack is empty or not
    parameter stack represent the stack
    this function should return 1 if the given stack is empty, 0 if not
*/
int isEmpty(struct Node *stack)
{
    return stack == NULL ? 1 : 0;
}
/*
    function size will give the number of data in the given stack
    this function should return the number of data in the stack
*/
int size(struct Node *stack)
{
    int count = 0;
    while(stack != NULL)
    {
        stack = stack->next;
        count++;
    }
    return count;
}

void move(struct Node **stack_a, struct Node **stack_b)
{
  
  //從A移動到B
  if(!isEmpty(*stack_a) && (isEmpty(*stack_b) || top(*stack_a) > top(*stack_b)))
  {
    //puts("A to B\n");
    push(stack_b, top(*stack_a));
    pop(stack_a);

    return;
  }
  //從B移動到A
  else if(!isEmpty(*stack_b) && (isEmpty(*stack_a) || top(*stack_b) > top(*stack_a)))
  {
    //puts("B to A\n");
    push(stack_a, top(*stack_b));
    pop(stack_b);

    return;
  }
  
}

int main()
{
  int count = 0;
  while(scanf("%d", &count) != EOF)
  {
    struct Node *source, *destination, *auxiliary;
    initLinkList(&source);
    initLinkList(&destination);
    initLinkList(&auxiliary);
    //struct Node **source_h = &source, **destination_h = &destination, **auxiliary_h = &auxiliary;

    for(int i = 0;i < count;i++)
    {
      push(&source,'A'+i);
    }


    int i = 0;
    while(1)
    {
      //奇數個碟子
      if(count % 2 == 1)
      {
        if(i % 3 == 0)
          move(&source, &destination);
        else if(i % 3 == 1)
          move(&source, &auxiliary);
        else if(i % 3 == 2)
          move(&auxiliary, &destination);
      }
      //偶數個碟子
      else
      {
        if(i % 3 == 0)
          move(&source, &auxiliary);
        else if(i % 3 == 1)
          move(&source, &destination);
        else if(i % 3 == 2)
          move(&auxiliary, &destination);
      }

      //display(source);
      //display(auxiliary);
      //display(destination);

      if(isEmpty(source) && isEmpty(auxiliary))
        break;

      i++;
    }
    printf("%d\n", i+1);
  }
}