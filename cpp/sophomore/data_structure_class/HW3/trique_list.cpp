#include <iostream>
#include <cmath>

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

  //回傳上一個node
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
    //linkedlist為空的情形
    if(tail == nullptr)
    {
    tail = new Node<T>(data);
    head = tail;
    }
    //已經存在Node
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
    //linkedlist為空的情形
    if(head == nullptr)
    {
    head = new Node<T>(data);
    tail = head;
    }
    //已經存在Node
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

        //刪除此node
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

  void deleteData_reverse(T data)
  {
    Node<T> *iter = tail;
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

        //刪除此node
        delete iter;

        //任務完成
        return;
      }
      else
      {
        iter = iter -> getPrev();
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

  Node<T>* getHead()
  {
    return head;
  }

  Node<T>* getTail()
  {
    return tail;
  }

  private: 
    Node<T> *head = nullptr;
    Node<T> *tail = nullptr;
};


template <class T>
class trique
{
public:
    int Addrear(T data)
    {
        if(IsFull())
        {
            return -1;
        }
        else
        {
            std::cout << "Add rear"<< std::endl;
            half_end.addToTail(data);
            return 1;
        }
    }

    int Addfront(T data)
    {
        if(IsFull())
        {
            return -1;
        }
        else
        {
            std::cout << "Add front"<< std::endl;
            half_front.addToHead(data);
            return 1;
        }
    }

    int AddMiddle(int data)
    {    
        std::cout << "Add middle" << std::endl;
        if(IsFull())
        {
            return -1;
        }
        else
        {
            int list_sum = f_list_size() + e_list_size();
            std::cout << "list_size:" << list_sum << std::endl;

            stable_list(list_sum);
            half_end.addToHead(data);
            return 1;
        }
    }

    T *DeleteFront()
    {
        if(IsEmpty())
          return NULL;
        //前半list為空，後半不為空
        else if(f_list_empty() && !e_list_empty())
        {
          T *num = new T(half_end.getHead()->getData());
          half_end.deleteData(*num);
          return num;
        }
        else
        {
          T *num = new T(half_front.getHead()->getData());
          half_front.deleteData(*num);
          return num;
        }
    }

    T *DeleteRear()
    {
        if(IsEmpty())
          return NULL;
        //前半list不為空，後半為空
        else if(!f_list_empty() && e_list_empty())
        {
          T *num = new T(half_front.getTail()->getData());
          half_front.deleteData_reverse(*num);
          return num;
        }
        else
        {
          T *num = new T(half_end.getTail()->getData());
          half_end.deleteData_reverse(*num);
          return num;
        }
    }

    T *DeleteMiddle()
    {
        std::cout << "Delete middle" << std::endl;
        if(IsEmpty())
        {
            return NULL;
        }
        else
        {
            int list_sum = f_list_size() + e_list_size();
            std::cout << "list_size:" << list_sum << std::endl;

            stable_list(list_sum);
            if(f_list_size() > e_list_size())
            {
              T *num = new T(half_front.getTail()->getData());
              half_front.deleteData_reverse(*num);
              return num;
            }
            else
            {
              T *num = new T(half_end.getHead()->getData());
              half_end.deleteData(*num);
              return num;
            }
        }
    }

    T CheckFront()
    {
        if(IsEmpty())
            return -1;

        if(f_list_empty() && !e_list_empty())
          return half_end.getHead()->getData();
        else
          return half_front.getHead()->getData();
    }

    T CheckRear()
    {
        if(IsEmpty())
            return -1;

        if(!f_list_empty() && e_list_empty())
          return half_front.getTail()->getData();
        else
          return half_end.getTail()->getData();
    }

    T CheckMiddle()
    {
      if(IsEmpty())
            return -1;
      
      stable_list(f_list_size() + e_list_size());
      if(f_list_size() > e_list_size())
      {
        return half_front.getTail()->getData();
      }
      else
      {
        return half_end.getHead()->getData();
      }

    }

    bool f_list_empty()
    {
      return half_front.getHead() == nullptr ? true : false;
    }

    bool e_list_empty()
    {
      return half_end.getHead() == nullptr ? true : false;
    }

    
    bool IsEmpty()
    {
        return f_list_empty() && e_list_empty();
    }

    //以動態配置記憶體的方式新增list，不會有滿的問題
    bool IsFull()
    {
        return 0;
    }

    int f_list_size()
    {
      int size = 0;
      for(Node<T>* iter = half_front.getHead();iter;iter = iter->getNext())
      {
        size++;
      }
      return size;
    }

    int e_list_size()
    {
      int size = 0;
      for(Node<T>* iter = half_end.getHead();iter;iter = iter->getNext())
      {
        size++;
      }
      return size;
    }

    void print()
    {
      std::cout << "trique:";
      for(Node<T>* iter = half_front.getHead();iter;iter = iter->getNext())
      {
        std::cout << iter->getData() << " ";
      }

      for(Node<T>* iter = half_end.getHead();iter;iter = iter->getNext())
      {
        std::cout << iter->getData() << " ";
      }
      std::cout << "\n";
    }

    //先創建一個新的list，把舊的資料全搬過去，之後再依據平衡數目放回
    void stable_list(int count)
    {
        LinkedList<T> buf;
        while(half_front.getHead() != nullptr)
        {
          buf.addToTail(half_front.getHead()->getData());
          half_front.deleteData(half_front.getHead()->getData());
        }
        while(half_end.getHead() != nullptr)
        {
          buf.addToTail(half_end.getHead()->getData());
          half_end.deleteData(half_end.getHead()->getData());
        }

        std::cout << &buf;

        int front_count = 0, end_count = 0;
        if(count % 2 == 0)
        {
          front_count = end_count = count / 2;
        }
        else
        {
          front_count = (count / 2) + 1;
          end_count = count / 2;
        }
        
        std::cout << "front:" << front_count << " end:" << end_count << std::endl;

        for(int i = 0; i < front_count;i++)
        {
          half_front.addToTail(buf.getHead()->getData());
          buf.deleteData(buf.getHead()->getData());
        }

        for(int i = 0; i < end_count;i++)
        {
          half_end.addToTail(buf.getHead()->getData());
          buf.deleteData(buf.getHead()->getData());
        }

        std::cout << &half_front;
        std::cout << &half_end;
    }


private:
    LinkedList<T> half_front, half_end;
};


int main()
{
    trique <int> a;
    a.Addrear(1);
    a.print();
    a.Addfront(2);
    a.print();
    a.Addrear(3);
    a.print();
    a.Addfront(4);
    a.print();
    a.Addrear(6);
    a.print();

    /*a.AddMiddle(7);
    a.print();

    a.AddMiddle(8);
    a.print();

    a.AddMiddle(7);
    a.print();

    a.AddMiddle(8);
    a.print();

    a.AddMiddle(9);
    a.print();*/

    /*a.DeleteFront();
    a.print();
    a.DeleteFront();
    a.print();
    a.DeleteRear();
    a.print();
    a.DeleteRear();
    a.print();
    a.DeleteRear();
    a.print();
    a.DeleteRear();
    a.print();*/


    a.AddMiddle(7);
    a.print();
    std::cout << a.CheckMiddle() << std::endl;
    a.AddMiddle(8);
    a.print();
    std::cout << a.CheckMiddle() << std::endl;
    a.AddMiddle(9);
    a.print();
    std::cout << a.CheckMiddle() << std::endl;
    a.AddMiddle(10);
    a.print();
    std::cout << a.CheckMiddle() << std::endl;

    while(!a.IsEmpty())
    {
      a.DeleteRear();
      a.print();
    }


} 