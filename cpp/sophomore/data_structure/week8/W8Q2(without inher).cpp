#include <exception>
#include<iostream>


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

  void setData(T data)
  {
    this->data = data;
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

  template<typename D>
  friend void print_list_node(LinkedList<D> *list);
  template<typename D>
  friend bool empty_list_node(LinkedList<D> *list);
  template<typename D>
  friend D find_char(LinkedList<D> *list, const char ch);
  template<typename D>
  friend void list_sort(LinkedList<D> *list);
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

  Node<T>* getHead()
  {
    return head;
  }

  Node<T>* getTail()
  {
    return tail;
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

//測試用，把這個list印出來
template<class T>
void print_list_node(LinkedList<T> *list)
{
  Node<T> *iter = list->head;
  std::cout << "Print list:";
  while(true)
  {
    std::cout << iter->getData()->getData() << " ";
    if(iter != list->tail)
      iter = iter->getNext();
    else
      break;
  }
  std::cout << "\n";
}

//檢查list是否為空
template<class T>
bool empty_list_node(LinkedList<T> *list)
{
  return list->head == nullptr;
}

//看這個list有沒有特定的字元（假設list的資料皆為一字元的string）
template<class T>
T find_char(LinkedList<T> *list, const char ch)
{
  if(empty_list_node(list))
    return nullptr;

  Node<T> *iter = list->head;
  
  while(true)
  {
    //std::cout << "find_char:" << iter->getData()->getData() << "\n";

    if(iter->getData()->getData() == std::string(1, ch))
      return iter->getData();
    else if(iter != list->tail)
      iter = iter->getNext();
    else
      return nullptr;
  }
}

//排序這個list
template<class T>
void list_sort(LinkedList<T> *list)
{
  for(Node<T>*iter_a = list->head;iter_a;iter_a = iter_a->getNext())
  {
    for(Node<T>*iter_b = iter_a;iter_b;iter_b = iter_b->getNext())
    {
      if(iter_a->getData()->getData()[0] > iter_b->getData()->getData()[0])
      {
        T buf = iter_a->getData();
        iter_a->setData(iter_b->getData());
        iter_b->setData(buf);
      }
    }
  }
}

template<class T>
class Queue
{
  public:

  /**
   * Construct a new Queue object with no parameter
   */
  Queue()
  {
    list = new LinkedList<T>;
  }

  /**
   * Add a data to queue
   * @param data: data to be added to queue
   */
  void enqueue(T data)
  {
    list->addToTail(data);
  }

  /**
   * Remove a data from queue and return it
   * @return the data removed from queue
   */
  T dequeue()
  {
    T buf = list->getfront();
    list->deleteData(buf);
    return buf;
  }

  /**
   * @return the first element in the queue
   */
  T front()
  {
    return list->getfront();
  }

  /**
   * @return true if queue is empty, false otherwise
   */
  bool isEmpty()
  {
    return list->isEmpty();
  }

  friend std::ostream &operator<<(std::ostream &out, Queue * n)
  {
    out << n->list;

    return out;
  }

  private: 
    LinkedList<T> *list = nullptr;
};

template<class T>
class GeneralTreeNode{
public:
  GeneralTreeNode()
  {
    children = new LinkedList<GeneralTreeNode<T>*>;
  }
  GeneralTreeNode(std::string data)
  {
    this->data = data;
    children = new LinkedList<GeneralTreeNode<T>*>;
  }

  GeneralTreeNode<T>* getParent()
  {
    return parent;
  }
  void setParent(GeneralTreeNode<T>* parent)
  {
    this->parent = parent;
  }
  LinkedList<GeneralTreeNode<T>*>* getChildren()
  {
    return this->children;
  }
  void setChildren(LinkedList<GeneralTreeNode<T>*>* children)
  {
    this->children = children;
  }
  T getData()
  {
    return data;
  }

  void setWordEnd(bool state)
  {
    word_end = state;
  }

  bool getWordEnd()
  {
    return word_end;
  }
  

private:
  T data;
  GeneralTreeNode<T> *parent = nullptr; 
  LinkedList<GeneralTreeNode<T>*>* children = nullptr;
  bool word_end = false;
};

template<class T>
class GeneralTree{
  public:
    GeneralTree() {
       this -> root = new GeneralTreeNode<T>();
    }
    
    /*
    想法：與binary tree的方法相似
    先把root的Linkedlist放入，再以for迴圈把list的資料拿出
    並同時把這些資料依序放到queue中
    一直照著此方式做，直到queue空了
    */
    void levelorder()
    {
      std::string order_str;
      Queue<LinkedList<GeneralTreeNode<T>*> *> node;
      node.enqueue(this->root->getChildren());

      while(!node.isEmpty())
      {
          LinkedList<GeneralTreeNode<T>*> *buf = node.front();
          node.dequeue();

          for(Node<GeneralTreeNode<T>*> *iter = buf->getHead();iter;iter = iter->getNext())
          {
            if(order_str.length() == 0)
              order_str += iter->getData()->getData();
            else
              order_str += "," + iter->getData()->getData();

            if(!empty_list_node(iter->getData()->getChildren()))
              node.enqueue(iter->getData()->getChildren());
          }
      }

      std::cout << "Levelorder\n";
      std::cout << order_str << std::endl;
    }

    //更改樹的root?
    void setRoot(GeneralTreeNode<T>* root)
    {
      this->root = root;
    }

    //插入一個資料到樹中
    /*
    想法：
    1.樹為空的情況
    （只要放入就可以）
    1-1:第一個放在root的list
    1-2:剩下的放在隨後list的node

    2.樹不為空的情況
    （需要考量已經存在的可能）
    2-1:先搜尋，看有沒有重複的字串
    2-2:若沒有，則放入剩餘的字串
    */
    bool insert(T data)
    {
      //這個樹是空的
      if(empty_list_node(this->root->getChildren()))
      {
        //std::cout << "This is a empty tree.\n";
        //創建一個新的linkedlist，放入資料後，再給root node
        GeneralTreeNode<T>* iter;
        for(int i = 0;i < data.length();i++)
        {
          GeneralTreeNode<T> *buf_node = new GeneralTreeNode<T>(std::string(data, i, 1));
          //std::cout << "buf_node:" << buf_node->getData() << std::endl;

          //放root的child
          if(i == 0)
          {
            this->root->getChildren()->addToTail(buf_node);
            //print_list_node(this->root->getChildren());
          }
          //放其他node的child
          else
          {
            iter->getChildren()->addToTail(buf_node);
            //print_list_node(iter->getChildren());
          }
            
          iter = buf_node;

          //最後一個node，設定word_end
          if(i+1 == data.length())
            iter->setWordEnd(true);
        }
        return true;
      }
      //已經放東西了
      else
      {
        LinkedList<GeneralTreeNode<T>*> *iter = this->root->getChildren();

        int index = 0;
        bool first_put = true;
        GeneralTreeNode<T>* target_node;
        while(true)
        {
          //在linkedlist中，找不到該字元
          if((target_node = find_char(iter, data[index])) == 0)
          {
            //std::cout << "can't find that character\n";
            for(int i = index;i < data.length();i++)
            {
              GeneralTreeNode<T> *buf_node = new GeneralTreeNode<T>(std::string(data, i, 1));
              //std::cout << "buf_node:" << buf_node->getData() << std::endl;

              //放root的child
              if(first_put)
              {
                iter->addToTail(buf_node);
                list_sort(iter);
                //print_list_node(iter);
                
                first_put = false;
              }
              //放其他node的child
              else
              {
                target_node->getChildren()->addToTail(buf_node);
                //print_list_node(target_node->getChildren());
              }
                
              target_node = buf_node;

              //最後一個node，設定word_end
              if(i+1 == data.length())
                target_node->setWordEnd(true);
            }
            return true;
          }
          //在linkedlist中，找到該字元，且輸入資料尚未到底
          if((target_node = find_char(iter, data[index])) && index + 1 != data.length())
          {
            iter = target_node->getChildren();
            index++;
          }
          else if((target_node = find_char(iter, data[index])) && index + 1 == data.length())
          {
            if(target_node->getWordEnd())
              return false;
            else
             {
              target_node->setWordEnd(true);
              return true;
             };
          }
          else
          {
            return false;
          }
        }
      }
    }

    bool search(T data)
    {
      //這個樹是空的
      if(this->root->getChildren() == nullptr)
      {
        return false;
      }
      //已經放東西了
      else
      {
        LinkedList<GeneralTreeNode<T>*> *iter = this->root->getChildren();
        int index = 0;
        GeneralTreeNode<T>* target_node;

        while(true)
        {
          target_node = find_char(iter, data[index]);

          //在linkedlist中，找不到該字元
          if(target_node == 0)
          {
            return 0;
          }
          //在linkedlist中，找到該字元，且輸入資料尚未到底
          else if(target_node && index + 1 != data.length())
          {
            iter = target_node->getChildren();
            index++;
          }
          else
          {
            if(target_node->getWordEnd())
              return 1;
            else
              return 0;
          }
        }
      }
    }

    std::string serialize()
    {
      first_serial();

      LinkedList<GeneralTreeNode<T>*> *list = root->getChildren();
      //print_list_node(list);
      
      
      for(Node<GeneralTreeNode<T>*> *iter = list->getHead();iter;iter = iter->getNext())
      {
        serial_str += "{\"children\":[";
        serialize_list(iter->getData()->getChildren());
        serial_str += "],\"data\":\"" + iter->getData()->getData() + "\"";
        if(iter->getData()->getWordEnd())
          serial_str += ",\"end\":\"true\"";

        serial_str += "}";
        if(iter->getNext() != nullptr)
          serial_str += ",";
      }

      serial_str += "],\"data\":\"\"}}";
      
      //std::cout << "result:" << serial_str << std::endl;
      return serial_str;
    }

    void serialize_list(LinkedList<GeneralTreeNode<T>*> *list)
    {
      if(empty_list_node(list))
      {
        //std::cout << "list empty\n";
        return;
      }
      else
        //print_list_node(list);

      
      for(Node<GeneralTreeNode<T>*> *iter = list->getHead();iter;iter = iter->getNext())
      {
        serial_str += "{\"children\":[";
        serialize_list(iter->getData()->getChildren());
        serial_str += "],\"data\":\"" + iter->getData()->getData() + "\"";
        if(iter->getData()->getWordEnd())
          serial_str += ",\"end\":\"true\"";

        serial_str += "}";
        if(iter->getNext() != nullptr)
          serial_str += ",";
      }
    }
    

    void first_serial()
    {
      serial_str.clear(); 
      serial_str = "{\"root\":{\"children\":[";
    }


  private:
    GeneralTreeNode<T>* root;
    std::string serial_str;
};


/*
疑問
1.我們把TreeNode繼承給GeneralTreeNode，但是TreeNode的函式的參數是TreeNode
  是否都要改成GeneralTreeNode?
2.T&D如果都用string，那會有差別嗎?
*/
#include<cstdio>

int main() {
  //freopen("input.txt", "r", stdin);
  //freopen("output.txt", "w", stdout);

  GeneralTree<std::string> a;
  int insert_num = 0, search_num = 0;
  std::cin >> insert_num >> search_num;
  for(int i = 0;i < insert_num;i++)
  {
    std::string input;
    std::cin >> input;
    a.insert(input);
  }
  for(int i = 0;i < search_num;i++)
  {
    std::string input;
    std::cin >> input;
    std::cout << a.search(input) << std::endl;
  }

  std::cout << a.serialize() << std::endl;

  //測試用
  //a.levelorder();
  return 0;
}

