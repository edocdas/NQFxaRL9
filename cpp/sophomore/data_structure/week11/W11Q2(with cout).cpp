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


template<class T> class BinarySearchTree;


/**
 * A TreeNode class of binarySearchTree class
 */
template<class T>
class TreeNode {
  public:
    friend class BinarySearchTree<T>;
    TreeNode(T input_data): data(input_data){}

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

    /**
     * Serialize the tree to a string with levelorder traversal
     * @return the serialized string
     */
    virtual std::string serialize() = 0;
  protected:
    TreeNode<T> *root = nullptr, *nil = nullptr;
};

template<class T>
class BinarySearchTree : public binarySearchTree<T> {
  public:
    BinarySearchTree()
    {
      this->nil = new TreeNode<T>("-1");
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
        if(isdigit(compare_1[0]))
          return stoi(compare_1) > stoi(compare_2);
        else
          return compare_1 > compare_2;
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
      else
        parent->left = new_node;
      
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
  

    TreeNode<T>* search(T target)
    {
      auto compare_larger = [](T compare_1, T compare_2) -> bool
      {
        if(isdigit(compare_1[0]))
          return stoi(compare_1) > stoi(compare_2);
        else
          return compare_1 > compare_2;
      };

      auto compare_smaller = [](T compare_1, T compare_2) -> bool
      {
        if(isdigit(compare_1[0]))
          return stoi(compare_1) < stoi(compare_2);
        else
          return compare_1 < compare_2;
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

    TreeNode<T>* Max(TreeNode<T> *iter)
    {
      auto compare_larger = [](T compare_1, T compare_2) -> bool
      {
        if(isdigit(compare_1[0]))
          return stoi(compare_1) > stoi(compare_2);
        else
          return compare_1 > compare_2;
      };

      while(iter->right != this->nil)
      {
        if(compare_larger(iter->right->data, iter->data))
        {
          iter = iter->right;
        }
      }

      return iter;
    }

    void Delete(T target)
    {
      auto transplant = [=](TreeNode<T>*old_node, TreeNode<T>*new_node)
      {
        if(old_node->parent == nullptr)
          this->root = new_node;
        else if(old_node == old_node->parent->left)
          old_node->parent->left = new_node;
        else
          old_node->parent->right = new_node;

        new_node->parent = old_node->parent;
      };


      TreeNode<T>* del_node;
      if((del_node = search(target)) != nullptr)
      {
        TreeNode<T>* replace_node = del_node, *fix_place;
        std::string replace_color = replace_node->color;

        //左方為空node
        if(del_node->left == this->nil)
        {
          fix_place = del_node->right;
          transplant(del_node, del_node->right);
        }
        //右方為空node
        else if(del_node->right == this->nil)
        {
          fix_place = del_node->left;
          transplant(del_node, del_node->left);
        }
        //都為非空node
        else
        {
          replace_node = Max(del_node->left);
          replace_color = replace_node->color;
          fix_place = replace_node->left;

          //處理左邊的內容
          if(replace_node->parent == del_node)
            fix_place->parent = replace_node;
          else
          {
            transplant(replace_node, replace_node->left);

            //std::cout << std::endl << "test" << std::endl << this->serialize() << std::endl;
            replace_node->left = del_node->left;
            replace_node->left->parent = replace_node;
          }

          //處理右邊的內容
          transplant(del_node, replace_node);
          replace_node->right = del_node->right;
          replace_node->right->parent = replace_node;
          replace_node->color = del_node->color;
        }

        if(replace_color == "B")
          delete_fix(fix_place);
      }
    }

    void delete_fix(TreeNode<T>* fix_node)
    {
      TreeNode<T>* sibling;
      while(fix_node != this->root && fix_node->color == "B")
      {
        if(fix_node == fix_node->parent->left)
        {
          sibling = fix_node->parent->right;

          if(sibling->color == "R")
          {
            std::cout << "Right sibling case 1" << std::endl;
            sibling->color = "B";
            fix_node->parent->color = "R";
            left_rotate(fix_node->parent);
            sibling = fix_node->parent->right;
          }
          if(sibling->left->color == "B" && sibling->right->color == "B")
          {
            std::cout << "Right sibling case 2" << std::endl;
            sibling->color = "R";
            fix_node = fix_node->parent;
          }
          else
          {
            if(sibling->right->color == "B")
            {
              std::cout << "Right sibling case 3" << std::endl;
              sibling->left->color = "B";
              sibling->color = "R";
              right_rotate(sibling);
              sibling = fix_node->parent->right;
            }

            std::cout << "Right sibling case 4" << std::endl;
            sibling->color = fix_node->parent->color;
            fix_node->parent->color = "B";
            sibling->right->color = "B";
            left_rotate(fix_node->parent);
            fix_node = this->root;
          }
        }
        else
        {
          sibling = fix_node->parent->left;

          if(sibling->color == "R")
          {
            std::cout << "Left sibling case 1" << std::endl;
            sibling->color = "B";
            fix_node->parent->color = "R";
            right_rotate(fix_node->parent);
            sibling = fix_node->parent->left;
          }
          if(sibling->right->color == "B" && sibling->left->color == "B")
          {
            std::cout << "Left sibling case 2" << std::endl;
            sibling->color = "R";
            fix_node = fix_node->parent;
          }
          else
          {
            if(sibling->left->color == "B")
            {
              std::cout << "Left sibling case 3" << std::endl;
              sibling->right->color = "B";
              sibling->color = "R";
              left_rotate(sibling);
              sibling = fix_node->parent->left;
            }

            std::cout << "Left sibling case 4" << std::endl;
            sibling->color = fix_node->parent->color;
            fix_node->parent->color = "B";
            sibling->left->color = "B";
            right_rotate(fix_node->parent);
            fix_node = this->root;
          }
        }
      }
      fix_node->color = "B";
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

    std::string serialize()
    {
      Queue<TreeNode<T>*> node;
      node.enqueue(this->root);

      while(!node.isEmpty())
      {
          TreeNode<T> *buf = node.dequeue();
          if(buf == this->nil)
          {
            order_str += ",NULL";
          }
          else
          {
            if(buf->parent != nullptr)
              std::cout << buf->data << " parent:" << buf->parent->data << std::endl;
            else
              std::cout << buf->data << " parent:empty" << std::endl;
            if(order_str.length() == 0)
              order_str += buf->data + "(" + buf->color + ")";
            else
              order_str += "," + buf->data + "(" + buf->color + ")";

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

private:
    std::string order_str;
};

int main()
{
  freopen("input3.txt","r",stdin);
  freopen("output.txt","w",stdout);

  std::string operation, buf;
  BinarySearchTree<std::string> tree;
  while(std::cin >> operation)
  {
    if(operation == "insert")
    {
      std::cin >> buf;
      std::cout << "insert:" << buf << std::endl << std::endl;
      tree.insert(buf);
      std::cout << tree.serialize() << std::endl;
    }
    else if(operation == "delete")
    {
      std::cin >> buf;
      std::cout << "delete:" << buf << std::endl;
      tree.Delete(buf);
      std::cout << tree.serialize() << std::endl << std::endl;
    }
  }

  //std::cout << tree.serialize() << std::endl;
}