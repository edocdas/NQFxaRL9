#include<iostream>
#include<sstream>

//https://www.cise.ufl.edu/~nemo/cop3530/AVL-Tree-Rotations.pdf
/*
test case

20,10,45,5,NULL,40,52
*/


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

  Node<T> *gethead()
  {
    return head;
  }

  Node<T> *gettail()
  {
    return tail;
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

template<class K,class V>
struct Pair {
    /**
     * @brief Construct a new Pair object
     */
    Pair() {}

    /**
     * @brief Construct a new Pair object
     * 
     * @param key 
     * @param value 
     */
    Pair(K key, V value)
    {
    	this->first = key;
      	this->second = value;
    }

    /**
     * @brief Copy construct a new Pair object
     * 
     * @param other 
     */
    Pair(const Pair& other)
    {
    	this->first = other.first;
      	this->second = other.second;
    }

    friend std::ostream& operator<<(std::ostream& os, const Pair& p) {
      os << p.first << " " << p.second;
      return os;
    }
    K first;
    V second;
};


template<class T> class BinarySearchTree;

/**
 * A TreeNode class of binarySearchTree class
 */
template<class T>
class TreeNode {
  public:
    friend class BinarySearchTree<T>;
    TreeNode(T input_data): data(input_data){}
    
    T* getData()
    {
        return &data;
    }

    TreeNode<T> * getParent()
    {
        return parent;
    }

    TreeNode<T> *getRight()
    {
        return right;
    }

    TreeNode<T> *getLeft()
    {
        return left;
    }

  private:
    T data;
    TreeNode<T> *left = nullptr;
    TreeNode<T> *right = nullptr;
    TreeNode<T> *parent = nullptr;
    std::string color = "R";
};

/**
 * A binarySearchTree abstract class for BinarySearchTree class
 */
template<class T>
class binarySearchTree {
  public:
    /**
     * Insert data into the tree if the value is not present
     * @param data data to insert
     * @return true if insert successfully, false if the value is already present
     */
    virtual bool insert(T data) = 0;

  protected:
    TreeNode<T> *root = nullptr, *nil = nullptr;
};

template<class T>
class BinarySearchTree : public binarySearchTree<T> {
  public:
    BinarySearchTree()
    {
      this->nil = new TreeNode<T>(Pair<std::string, int>("NIL", -1));
      this->nil->color = "B";
      this->root = this->nil;
    }

    int height(TreeNode<T>*node)
    {
      auto max = [](int a, int b)
      {
        return a > b ? a : b;
      };

      if(node == nullptr)
        return -1;
      else
        return max(height(node->left),height(node->right)) + 1;
    }

    bool insert(T data)
    {
      auto compare_larger = [](T compare_1, T compare_2) -> bool
      {
          return compare_1.first > compare_2.first;
      };

      auto compare_smaller = [](T compare_1, T compare_2) -> bool
      {
          return compare_1.first < compare_2.first;
      };
      
      TreeNode<T> *iter = this->root, *parent = nullptr;
      TreeNode<T> *new_node = new TreeNode<T>(data);
      new_node->left = this->nil;
      new_node->right = this->nil;

      //找parent
      while(iter != this->nil)
      {
        parent = iter;
        if(compare_larger(data, iter->data))
          iter = iter->right;
        else
          iter = iter->left;
      }

      //把node放在對的位置
      new_node->parent = parent;
      if(parent == nullptr)
        this->root = new_node;
      else if(compare_larger(data,parent->data))
        parent->right = new_node;
      else if(compare_smaller(data,parent->data))
        parent->left = new_node;
      else
      {
        delete new_node;
        return false;
      }
      
      //處理avl tree
      insert_fix(new_node);
      return true;
    }

    void insert_fix(TreeNode<T>* node)
    {
      while(node->parent != nullptr && node->parent->color == "R")
      {
        //uncle在右邊的情況
        if(node->parent == node->parent->parent->left)
        {
          TreeNode<T>* uncle = node->parent->parent->right;
          //如果uncle&parent都是red
          if(uncle->color == "R")
          {
            node->parent->color = "B";
            uncle->color = "B";
            node->parent->parent->color = "R";
            node = node->parent->parent;
          }
          else
          {
            if(node == node->parent->right)
            {
              node = node->parent;
              left_rotate(node);
            }
            node->parent->color = "B";
            node->parent->parent->color = "R";
            right_rotate(node->parent->parent);
          }
        }
        //uncle在左邊的情況
        else
        {
          TreeNode<T>* uncle = node->parent->parent->left;
          if(uncle->color == "R")
          {
            node->parent->color = "B";
            uncle->color = "B";
            node->parent->parent->color = "R";
            node = node->parent->parent;
          }
          else
          {
            if(node == node->parent->left)
            {
              node = node->parent;
              right_rotate(node);
            }
            node->parent->color = "B";
            node->parent->parent->color = "R";
            left_rotate(node->parent->parent);
          }
        }

        if(node == this->root)
          break;
      }
      this->root->color = "B";
    }

    TreeNode<T>* search(std::string target)
    {
      auto compare_larger = [](std::string compare_1, T compare_2) -> bool
      {
          return compare_1 > compare_2.first;
      };

      auto compare_smaller = [](std::string compare_1, T compare_2) -> bool
      {
          return compare_1 < compare_2.first;
      };

      TreeNode<T> *iter = this->root;
      while(iter != this->nil)
      {
        //比較字串比目前node大
        if(compare_larger(target, iter->data))
        {
          iter = iter->right;
        }
        //比較字串比目前node小
        else if(compare_smaller(target, iter->data))
        {
          iter = iter->left;
        }
        //比較字串與目前node相等
        else
        {
            return iter;
        }
      }

      return nullptr;
    }

    void replace_parent(TreeNode<T>*old_node, TreeNode<T>*replace_node)
    {
      if(old_node->parent == nullptr)
      {
        replace_node->parent = nullptr;
        return;
      }

      if(old_node->parent->left == old_node)
      {
        old_node->parent->left = replace_node;
        replace_node->parent = old_node->parent;
      }
      else
      {
        old_node->parent->right = replace_node;
        replace_node->parent = old_node->parent;
      }
    }

    void left_rotate(TreeNode<T>*old_parent)
    {
      TreeNode<T> *new_parent = old_parent->right;
      replace_parent(old_parent, new_parent);
      old_parent->right = new_parent->left;
      new_parent->left = old_parent;
      old_parent->parent = new_parent;
      if(old_parent->right != this->nil)
        old_parent->right->parent = old_parent;

      if(old_parent == this->root)
        this->root = new_parent;
    }

    void right_rotate(TreeNode<T>*old_parent)
    {
      TreeNode<T> *new_parent = old_parent->left;
      replace_parent(old_parent, new_parent);
      old_parent->left = new_parent->right;
      new_parent->right = old_parent;
      old_parent->parent = new_parent;
      if(old_parent->left != this->nil) 
        old_parent->left->parent = old_parent;

      if(old_parent == this->root)
        this->root = new_parent;
    }

    void inorder(TreeNode<T> *iter, LinkedList<std::string> *list)
    {
        if(iter->left != this->nil)
            inorder(iter->left, list);
        list->addToTail(iter->data.first);
        if(iter->right != this->nil)
            inorder(iter->right, list);
    }

private:
    std::string order_str;
};

/**
 * @brief Class for Map
 * 
 * @tparam K data type for key of the map
 * @tparam V data type for value of the map
 */
template <class K, class V>
class Map : public BinarySearchTree<Pair<K, V>> {
  public: 
    // alias the type
    typedef Pair<K, V> MapType;

    /**
     * @brief Traverse the tree with inorder traversal
     */
    class Iterator{
      public:
        friend Map<K,V>;
        // Implement the function you need.
        Iterator() {}

        Iterator(TreeNode<MapType> *pair)
        {
            current = pair;
        }

        // Overload the operators
        MapType* operator->() const
        {
            return current->getData();
        }
        MapType& operator*() const
        {
            return *(current->getData());
        }

        Iterator& operator++()
        {
            //第一種情況，有right child
            if(current->getRight()->getData()->first != "NIL")
            {
              //std::cout << "first case" << std::endl;
              current = current->getRight();
            }
            //第二種情況，沒有parent(root node)
            else if(current->getParent() == nullptr)
            {
              //std::cout << "second case" << std::endl;
                TreeNode<MapType>*buf = current->getRight();
                while(buf->getLeft()->getData()->first != "NIL")
                    buf = buf->getLeft();
                current = buf;
            }
            //第三種可能，為parent的左node
            else if(current->getParent()->getLeft() == current)
            {
              //std::cout << "third case" << std::endl;
                current = current->getParent();
            }
            //第四種可能，為parent的右node
            else if(current->getParent()->getRight() == current)
            {  
                //尚未為最大值
                if(current->getParent()->getParent() != nullptr && current->getParent()->getParent()->getData()->first < current->getData()->first)
                {
                  //std::cout << "four case" << std::endl;

                    current = current->getParent()->getParent();
                }
                //已經為最大值
                else
                {
                  //std::cout << "five case" << std::endl;

                  current = 0;
                }
            }
            return *this;
        }
        Iterator operator++(int)
        {
            Iterator tmp(*this);
            operator++();
            return tmp;
        }

        TreeNode<MapType> *get_node() const
        {
            return current;
        }
					
      private:
        TreeNode<MapType> *current;
    };  

  /**
   * @brief Overload the operator []
   */
  V& operator[](const K& k)
  {
    //沒找到此node
    if(this->search(k) == nullptr)
        this->insert(Pair<K,V>(k,1));
        
    return this->search(k)->getData()->second;
  }

  /** 
   * @return Iterator pointing to the first element in the map
   */
  Iterator begin()
  {
    LinkedList<std::string> list;
    this->inorder(this->root, &list);

    /*for(auto it = list.gethead();it;it = it->getNext())
        std::cout << it->getData() << " ";
    std::cout << std::endl;*/

    return Iterator(this->search(list.getfront()));
  }

  /**
   * @return Iterator pointing to one past the last element in the map
   */
  Iterator end()
  {
    return Iterator(0);
  }

  // comparison operators on iterator
  friend bool operator==(const Iterator& _iter1, const Iterator& _iter2)
  {
    return _iter1.get_node() == _iter2.get_node();
  }
  friend bool operator!=(const Iterator& _iter1, const Iterator& _iter2)
  {
    return _iter1.get_node() != _iter2.get_node();
  }
};

int main() {
  Map<std::string, int> map;
  // Inserting data to Map
  Pair<std::string, int> p1("earth", 1);
  Pair<std::string, int> p2("moon", 2);
  Pair<std::string, int> p3(p2);

  // insert the pair into the map only if key not exist.
  map.insert(p1);
  map.insert(p2);
  map.insert(p3);

  // Will replace the value of already added key.
  map["sun"] = 3;
  map["earth"] = 4;

  // Iterate through all elements in Map
  Map<std::string, int>::Iterator it = map.begin();
  while(it != map.end()) {
    std::cout<<it->first<<" :: "<<(*it).second<<std::endl;
    it++;
  }

  // Check if insertion is successful or not
  if(map.insert(p1) == false) {
    std::cout<<"Element with key 'earth' not inserted because already existed"<<std::endl;
  }

  return 0;
}
