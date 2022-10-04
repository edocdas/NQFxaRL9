#include<stdio.h>

struct Node
{
    int data;
    struct Node *prev, *next;
};

void initLinkList(struct Node **head)
{
    head = NULL;
}

void addToHead(struct Node **head, int data)
{
    struct Node* Newnode = (struct Node *)malloc(sizeof(struct Node));
    if (head==NULL)
    {
        head = Newnode;
    }
    else if(//tail == head)
    {
        head = Newnode;
        head->next = tail;
        //tail->prev = head;
    }
    else
    {
        struct Node *temp = head;
        head = Newnode;
        temp->prev = Newnode;
        head->next = temp;
    }
}

void addToTail(struct Node **head, int data)
{
    struct Node *Newnode = (struct Node *)malloc(sizeof(struct Node));
    if (head==NULL)  //沒有任何節點在LinkedList中的情形
        {
            //tail = Newnode;
            head = Newnode;
        }
        else if(//tail == head)      //只有一個節點在LinkedList中的情形
        {
            //tail = Newnode;
            head->next = tail;
            //tail->prev = head;
        }
        else                     //其他情形
        {
            struct Node *temp = //tail;
            //tail = Newnode;
            temp->next = tail;
            //tail->prev = temp;
        }
}

void deleteData(struct Node **head, int data)
{
    struct Node *current = *head;
    while(current != NULL)
        {
            if(current->data == data)
            {
                if(current == *head)
                {
                    if(*head == //*tail)
                    {
                        *head = NULL;
                        //*tail = NULL;
                    }
                    else
                    {
                        *head = current->next;
                        *head->prev = NULL;
                    }
                }
                else if(current == //*tail)
                {
                    if(*head == //*tail)
                    {
                        *head = NULL;
                        //*tail = NULL;
                    }
                    else
                    {
                        //*tail = current->prev;
                        //*tail->next = NULL;
                    }
                }
                else
                {
                    current->prev->next = current->next;
                    current->next->prev = current->prev;
                }
                delete current;
                break;
            }
            current = current->next;
        }
}

void deleteDatas(struct Node **head, int data, int n)
{
    struct Node *current = *head
    while(current!=NULL && count<n)
        {
            if(current->data == data)
            {
                count++;
                if(current == *head)
                {
                    if(*head == //*tail)
                    {
                        *head = NULL;
                        //*tail = NULL;
                        delete current;
                        return;
                    }
                    else
                    {
                        *head = current->next;
                        *head->prev = NULL;
                        struct Node *temp = current;
                        current = *head;
                        delete temp;
                    }
                }
                else if(current == //tail)
                {

                    if(*head == //*tail)
                    {
                        *head = NULL;
                        //*tail = NULL;
                        delete current;
                        return;
                    }
                    else
                    {
                        //*tail = current->prev;
                        //*tail->next = NULL;
                        struct Node *temp = current;
                        current = NULL;
                        delete temp;
                    }
                }
                else
                {
                    struct Node *temp = current->next;
                    current->prev->next = current->next;
                    current->next->prev = current->prev;
                    struct Node *tmp = current;
                    current = temp;
                    delete tmp;
                }
                continue;
            }
            current = current->next;
        }
    }
}

void display(struct Node *head)
{
        if(n->head == NULL)
        {
            printf("\n");
        }
        else
        {
            struct Node *current = n->head;
            if(n->head != n->tail)
            {
                //out<<"("<<current->getdata()<<",";
                printf(current->data,);
                current = current->next;
                while(true)
                {
                    if(current->next != NULL)
                        //out<<" "<<current->getdata()<<",";
                        printf( current->data,);
                    else
                    {
                        printf( current->data);
                        break;
                    }
                    current=current->next;
                }
                  printf(")\n");

            }else{
                printf("("current->data")\n");
            }
        }
}