//想法來源
//https://kt11273.pixnet.net/blog/post/217984822
//模擬
//https://www.mathsisfun.com/games/towerofhanoi.html

#include<iostream>
#include<cmath>

/**
 * A Node class of Doublely Linked List class
 */
template<class T>
class Node {
  public:

  /**
   * Construct a new Node object with no parameter
   */
  Node() {}

  /**
   * Construct a new Node object with parameter
   * @param data: data to put in
   */
  Node(T data)
  {
    this->data = data;
  }

  /**
   * Construct a new Node object with parameters
   * @param data: data to put in
   * @param prev: pointer to the previous node
   * @param next: pointer to the next node
   */
  Node(T data, Node<T> *prev, Node<T> *next)
  {
    this->prev = prev;
    this->next = next;
    this->data = data;
  }

  //更改成新的tail
  void setTail(Node<T> *new_tail)
  {
    next = new_tail;
  }

  //更改成新的head
  void setHead(Node<T> *new_head)
  {
    prev = new_head;
  }

  //回傳下一個node
  Node<T>* getNext()
  {
    return next;
  }

  //回傳下一個node
  Node<T>* getPrev()
  {
    return prev;
  }

  //回傳node裡的資料
  T getData()
  {
    return data;
  }

  private: 
    Node<T> *prev = nullptr;
    Node<T> *next = nullptr;
    T data;
};

/**
 * A Doublely Linked List class
 */
template<class T>
class LinkedList {
  public:

  /**
   * Construct a new LinkedList object with no parameter
   */
  LinkedList() {}

  /**
   * Add a node to the tail of the linked list
   * @param data: data to put in
   */
  void addToTail(T data)
  {
    if(tail == nullptr)
    {
    tail = new Node<T>(data);
    head = tail;
    }
    else {
      Node<T> *new_tail = new Node<T>(data);
      tail->setTail(new_tail);
      new_tail->setHead(tail);
      tail = new_tail;
    }
  }

  /**
   * Add a node to the head of the linked list
   * @param data: data to put in
   */
  void addToHead(T data)
  {
    if(head == nullptr)
    {
    head = new Node<T>(data);
    tail = head;
    }
    else {
      Node<T> *new_head = new Node<T>(data);
      head->setHead(new_head);
      new_head->setTail(head);
      head = new_head;
    }
  }

  /**
   * Delete a node from the linked list with the given data from the head
   * If there are no data to be deleted, then do nothing
   * @param data: data to delete
   */
  void deleteData(T data)
  {
    Node<T> *iter = head;
    while(iter != nullptr)
    {
      if(iter->getData() == data)
      {
        //更新node
        if(iter->getPrev() != nullptr)
          iter->getPrev()->setTail(iter->getNext());
        if(iter->getNext() != nullptr)
          iter->getNext()->setHead(iter->getPrev());

        //更新head & tail
        if(iter == head)
        {
          head = iter->getNext();
        }
        if(iter == tail)
        {
          tail = iter->getPrev();
        }
        
        delete iter;

        //任務完成
        return;
      }
      else
      {
        iter = iter -> getNext();
      }
    }
  }

  /**
   * Delete valid n nodes from the linked list with the given data from the head
   * If there are no more data to be deleted, then just skip
   * @param data: data to delete
   * @param n: max number of nodes to delete
   */
  void deleteData(T data, int n)
  {
    for(int i = 0;i < n;i++)
    {
      deleteData(data);
    }
  }

  T getfront()
  {
    return head->getData();
  }

  T getend()
  {
    return tail->getData();
  }

  bool isEmpty()
  {
    return head == nullptr ? true : false;
  }

  /**
   * Overload the operator << to print out all the data in the linked list from the head
   * There is a \n in the end of each print
   * 
   * Output example: 
   * If your linked list data is 5, 4, 3, 2, 1
   * then you should print out "(5, 4, 3, 2, 1)" with the content in quotes but without the quotes
   */
  friend std::ostream &operator<<(std::ostream &out, LinkedList * n)
  {
    Node<T> *iter = n->head;
    int counter = 0;
    out << "(";
    while(iter != nullptr)
    {
      if(counter != 0)
        out << ", ";
      
      out << iter->getData();
      iter = iter->getNext();

      counter++;
    }
    out << ")\n";

    return out;
  }

  private: 
    Node<T> *head = nullptr;
    Node<T> *tail = nullptr;
};

template<class T>
class Stack
{
  public:

  /**
   * Construct a new Stack object with no parameter
   */
  Stack()
  {
    list = new LinkedList<T>;
  }

  /**
   * Add a data to stack
   * @param data: data to be added to stack
   */
  void push(T data)
  {
    list->addToHead(data);
    list_size++;
  }

  /**
   * Remove a data from stack and return it
   * @return the data removed from stack
   */
  T pop()
  {
    T buf = list->getfront();
    list->deleteData(buf);
    list_size--;
    return buf;
  }

  /**
   * @return the last element in the stack
   */
  T top()
  {
    return list->getfront();
  }

  /**
   * @return true if stack is empty, false otherwise
   */
  bool isEmpty()
  {
    return list->isEmpty();
  }

  /**
   * @return the size of the stack
   */
  int size()
  {
    return list_size;
  }

  friend std::ostream &operator<<(std::ostream &out, Stack * n)
  {
    out << n->list;

    return out;
  }

  private: 
    LinkedList<T> *list;
    int list_size = 0;
};



void move(Stack<char> *stack_a, Stack<char> *stack_b)
{
  //從A移動到B
  if(!stack_a->isEmpty() && (stack_b->isEmpty() || stack_a->top() > stack_b->top()))
  {
    stack_b->push(stack_a->top());
    stack_a->pop();

    return;
  }
  //從B移動到A
  else if(!stack_b->isEmpty() && (stack_a->isEmpty() || stack_b->top() > stack_a->top()))
  {
    stack_a->push(stack_b->top());
    stack_b->pop();

    return;
  }
}

int main()
{
  int count = 0;
  while(std::cin >> count)
  {
    Stack<char> source, destination, auxiliary;

    for(int i = 0;i < count;i++)
    {
      source.push('A'+i);
    }

    int i = 0;
    while(true)
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

      if(source.isEmpty() && auxiliary.isEmpty())
        break;

      i++;
      //std::cout << &source;
      //std::cout << &auxiliary;
      //std::cout << &destination;
    }
    std::cout << i+1 << std::endl;
  }
}