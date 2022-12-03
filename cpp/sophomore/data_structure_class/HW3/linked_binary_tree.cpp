#include<iostream>
#include<sstream>
#include<climits>

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

  T getfront()
  {
    return head->getData();
  }

  Node<T> * gethead()
  {
    return this->head;
  }

  T getend()
  {
    return tail->getData();
  }

  bool isEmpty()
  {
    return head == nullptr ? true : false;
  }

  protected: 
    Node<T> *head = nullptr;
    Node<T> *tail = nullptr;
};

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



template<class T, class D>
class LinkedList_pair : public LinkedList<T>
{
  public:
    LinkedList_pair() = default;
  void addToHead(T data)
  {
    LinkedList<T>::addToHead(data);
    this->data = data->getData();
  }
  void addToTail(T data)
  {
    LinkedList<T>::addToTail(data);
    this->data = data->getData();
  }

  D get_list_value()
  {
    return data;
  }

  void sort()
  {
    for(Node<T>*iter_a = this->head;iter_a;iter_a = iter_a->getNext())
    {
      for(Node<T>*iter_b = iter_a;iter_b;iter_b = iter_b->getNext())
      {
        if(iter_a->getData()->get_same_data() > iter_b->getData()->get_same_data())
        {
          T buf = iter_a->getData();
          iter_a->setData(iter_b->getData());
          iter_b->setData(buf);
        }
      }
    }
  }

  private:
    D data;
};

template<class T, class D>
T find_data(LinkedList<T>* link_list, D compare)
{
  std::cout << "In find_data\n";
  for(Node<T> *iter = link_list->gethead();iter;iter = iter->getNext())
  {
    std::cout << "Compare:" << stoi(iter->getData()->get_list_value()) << " & " << compare << "\n"; 
    if(stoi(iter->getData()->get_list_value()) == compare)
      return iter->getData();
  }
  return nullptr;
}

template<class T>
void sort(LinkedList<T>* link_list)
{
  for(Node<T>*iter_a = link_list->gethead();iter_a;iter_a = iter_a->getNext())
  {
    for(Node<T>*iter_b = iter_a;iter_b;iter_b = iter_b->getNext())
    {
      if(stoi(iter_a->getData()->get_list_value()) > stoi(iter_b->getData()->get_list_value()))
      {
        T buf = iter_a->getData();
        iter_a->setData(iter_b->getData());
        iter_b->setData(buf);
      }
    }
  }
}

template<class T, class D>
void list_print(LinkedList<T> *link_list, D test)
{
  std::cout << "Print list\n";
  for(Node<T>*iter = link_list->gethead();iter;iter = iter->getNext())
  {
    std::cout << "List value:" << iter->getData()->get_list_value()<< "\n";
    for(Node<D>*iter_in = iter->getData()->gethead();iter_in;iter_in = iter_in->getNext())
    {
      std::cout << "Data:" << iter_in->getData()->getData() << "\n";
    }
  }
}

template<class T, class D, class K>
void list_change_data(LinkedList<T> *link_list, D empty, K old_str, K new_str)
{ 
  for(Node<T>*iter = link_list->gethead();iter;iter = iter->getNext())
  {
    std::cout << "List value:" << iter->getData()->get_list_value()<< "\n";
    if(iter->getData()->get_list_value() == old_str)
    {
      for(Node<D>*iter_in = iter->getData()->gethead();iter_in;iter_in = iter_in->getNext())
      {
        iter_in->getData()->setData(new_str);
      }
    }
  }
}

template<class T> class LinkedBinaryTree;


/**
 * A TreeNode class of binarySearchTree class
 */
template<class T>
class TreeNode {
  public:
    friend class LinkedBinaryTree<T>;
    TreeNode(T input_data): data(input_data){}

    T getData()
    {
      return data;
    }

    void setData(T data)
    {
      this->data = data;
    }

  private:
    T data;
    TreeNode<T> *left = nullptr;
    TreeNode<T> *right = nullptr;
};


template<class T>
class LinkedBinaryTree{
  public:
    void setRoot(T data)
    {
        this->root = new TreeNode<T>(data);
        //std::cout << "root:" << this->root->data << std::endl;
    }

    void preorder()
    {
        //std::cout << "Preorder\n";

        if(order_str.length() == 0)
            order_str += this->root->data;
        else
            order_str += "," + this->root->data;

        if(this->root->left != nullptr)
            preorder(this->root->left);
        if(this->root->right != nullptr)
            preorder(this->root->right);

        std::cout << order_str << std::endl;
        order_str.clear();
    }

    void preorder(TreeNode<T> *cur_node)
    {
        if(order_str.length() == 0)
            order_str += cur_node->data;
        else
            order_str += "," + cur_node->data;

        if(cur_node->left != nullptr)
            preorder(cur_node->left);
        if(cur_node->right != nullptr)
            preorder(cur_node->right);
    }

    void inorder()
    {
        //std::cout << "Inorder\n";
        
        if(this->root->left != nullptr)
            inorder(this->root->left);

        if(order_str.length() == 0)
            order_str += this->root->data;
        else
            order_str += "," + this->root->data;

        if(this->root->right != nullptr)
            inorder(this->root->right);

        std::cout << order_str << std::endl;
        order_str.clear();
    }

    void inorder(TreeNode<T> *cur_node)
    {
        if(cur_node->left != nullptr)
            inorder(cur_node->left);

        if(order_str.length() == 0)
            order_str += cur_node->data;
        else
            order_str += "," + cur_node->data;

        if(cur_node->right != nullptr)
            inorder(cur_node->right);
    }

    void postorder()
    {
         //std::cout << "Postorder\n";
        
        if(this->root->left != nullptr)
            postorder(this->root->left);

        if(this->root->right != nullptr)
            postorder(this->root->right);

        if(order_str.length() == 0)
            order_str += this->root->data;
        else
            order_str += "," + this->root->data;

        std::cout << order_str << std::endl;
        order_str.clear();
    }

    void postorder(TreeNode<T> *cur_node)
    {
        if(cur_node->left != nullptr)
            postorder(cur_node->left);
        if(cur_node->right != nullptr)
            postorder(cur_node->right);

        if(order_str.length() == 0)
            order_str += cur_node->data;
        else
            order_str += "," + cur_node->data;
    }

    void levelorder()
    {
        Queue<TreeNode<T>*> node;
        node.enqueue(this->root);

        while(!node.isEmpty())
        {
            TreeNode<T> *buf = node.front();
            node.dequeue();

            if(order_str.length() == 0)
                order_str += buf->data;
            else
                order_str += "," + buf->data;

            if(buf->left != nullptr)
                node.enqueue(buf->left);
            if(buf->right != nullptr)
                node.enqueue(buf->right);
        }

        //std::cout << "Levelorder\n";
        std::cout << order_str << std::endl;
        order_str.clear();
    }
    
    void deSerialize(std::string tree)
    {
      std::stringstream comma_split(tree);
      std::string sub_str;
      Queue<std::string> data_queue;
      Queue<TreeNode<T>*> next_queue;

      //把字串分開，並轉成數字
      while(std::getline(comma_split, sub_str, ','))
      {
        if(sub_str == "NULL")
          data_queue.enqueue("NULL");
        else
          data_queue.enqueue(sub_str);
      }

      std::string buf;
      bool set_root = true;
      while(!data_queue.isEmpty())
      {
        TreeNode<T>* cur_node;

        //第一次放樹根
        if(set_root)
        {
          this->setRoot(data_queue.dequeue());
          set_root = false;

          cur_node = this->root;

          //std::cout << "root_node:" << cur_node->data << std::endl;
        }
        //之後的node
        else
        {
          cur_node = next_queue.dequeue();
          //std::cout << "cur_node:" << cur_node->data << std::endl;
        }

        //左node可放
        if(!data_queue.isEmpty() && (buf = data_queue.dequeue()) != "NULL")
        {
          cur_node->left = new TreeNode<T>(buf);
          next_queue.enqueue(cur_node->left);
          //std::cout << "left node place:" << cur_node->left->data << std::endl;
        }
        //右node可放
        if(!data_queue.isEmpty() && (buf = data_queue.dequeue()) != "NULL")
        {
          cur_node->right = new TreeNode<T>(buf);
          next_queue.enqueue(cur_node->right);
          //std::cout << "right node place:" << cur_node->right->data << std::endl;
        }
      }
      TreeNode<T>* test;
      inorder_create_link(root);
      list_print(&link_list, test);
    }


    std::string serialize()
    {
      Queue<TreeNode<T>*> node;
      node.enqueue(this->root);

      while(!node.isEmpty())
      {
          TreeNode<T> *buf = node.dequeue();
          if(buf == 0)
          {
            order_str += ",NULL";
          }
          else
          {
            if(order_str.length() == 0)
              order_str += buf->data;
            else
              order_str += "," + buf->data;

            node.enqueue(buf->left);

            node.enqueue(buf->right);
          }
      }

      std::string return_str = order_str;
      order_str.clear();

      //把多餘的,NULL刪掉
      while(return_str.find_last_not_of("NULL") == return_str.length()-5)
        return_str.resize(return_str.length()-5);
      return return_str;
    }

    void inorder_create_link(TreeNode<T> *cur_node)
    {

      if(cur_node->left != nullptr)
            inorder_create_link(cur_node->left);

      create_link(cur_node);

      if(cur_node->right != nullptr)
          inorder_create_link(cur_node->right);
    }
    
    void create_link(TreeNode<T> *cur_node)
    {
      LinkedList_pair<TreeNode<T>*, T> *buf = 0;
      if((buf = find_data(&link_list, stoi(cur_node->data))) != 0)
      {
        std::cout << "exist linklist\n";
        buf->addToTail(cur_node);
      }
      else
      {
        std::cout << "create new linklist\n";
        //添加到link_list裡（因為是第一次，創建一個新的list）
        LinkedList_pair<TreeNode<T>*, T> *new_list = new LinkedList_pair<TreeNode<T>*, T>;
        new_list->addToTail(cur_node);
        link_list.addToTail(new_list);
      }
      
      sort(&link_list);
    }

    void list_change(T old_str, T new_str)
    {
      TreeNode<T> *empty;
      list_change_data(&link_list, empty, old_str, new_str);
    }

private:
    std::string order_str;
    TreeNode<T> *root;
    LinkedList<LinkedList_pair<TreeNode<T>*, T>*> link_list;
};


/*
這棵樹的輸入使用deserialize，以levelorder的方式插入資料
ex. 15,6,23,4,7,NULL,71,NULL,5,NULL,NULL,50
1,4,6,7,8,11,11,NULL,NULL,13,2,4,6,7,8

有了linked binary tree，我們可以同時更改相同數值的資料，而不用一個一個改動
ex. 1,4,6,7,8,11,11,NULL,NULL,13,2,4,6,7,8    (把4改成123)
  ->1,123,6,7,8,11,11,NULL,NULL,13,2,123,6,7,8
    1,2,1,2,1,NULL,3,NULL,1,NULL,NULL,2       (把1改成123)
  ->123,2,123,2,123,NULL,3,NULL,123,NULL,NULL,2
*/

int main()
{
  std::string line, buf;
  while(std::getline(std::cin, line))
  {
    LinkedBinaryTree<std::string> tree;
    tree.deSerialize(line);
    std::string old_str = "1", new_str = "123";
    tree.list_change(old_str, new_str);


    std::cout << tree.serialize() << std::endl;
  }
}