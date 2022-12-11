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
};

/**
 * A binarySearchTree abstract class for BinarySearchTree class
 */
template<class T>
class binarySearchTree {
  public:
    /**
     * Print preorder traversal of the tree
     * Format: "4,5,6,7". Data seperate by "," with no spaces between and without quotes
     */
    virtual void preorder() = 0;

    /**
     * Print inorder traversal of the tree
     * Format: "4,5,6,7". Data seperate by "," with no spaces between and without quotes
     */
    virtual void inorder() = 0;

    /**
     * Print postorder traversal of the tree
     * Format: "4,5,6,7". Data seperate by "," with no spaces between and without quotes
     */
    virtual void postorder() = 0;

    /**
     * Print levelorder traversal of the tree
     * Format: "4,5,6,7". Data seperate by "," with no spaces between and without quotes
     */
    //virtual void levelorder() = 0;

    /**
     * Insert data into the tree if the value is not present
     * @param data data to insert
     * @return true if insert successfully, false if the value is already present
     */
    virtual bool insert(T data) = 0;

    /**
     * Set the value of the root
     * @param data to set to root
     */
    virtual void setRoot(T data) = 0;

    /**
     * Search the tree for the given value
     * @param target target to find
     * @return true if found, false if not found
     */
    virtual bool serach(T target) = 0;

    /**
     * Deserialize the string to a tree with levelorder traversal
     * @param tree to be deserialized
     */
    virtual void deSerialize(std::string tree) = 0;

    /**
     * Serialize the tree to a string with levelorder traversal
     * @return the serialized string
     */
    virtual std::string serialize() = 0;
  protected:
    TreeNode<T> *root;
};

template<class T>
class BinarySearchTree : public binarySearchTree<T> {
  public:
    void setRoot(T data)
    {
        this->root = new TreeNode<T>(data);
        //std::cout << "root:" << this->root->data << std::endl;
    }

    bool insert(T data)
    {
        TreeNode<T> *iter = this->root, *new_node = new TreeNode<T>(data);
        while(iter != nullptr)
        {
            //數字比目前node大
            if(stoi(data) > stoi(iter->data))
            {
                //std::cout << "Bigger than node\n";

                if(iter -> right != nullptr)
                    iter = iter->right;
                else
                    {
                        //std::cout << "Put right node\n";
                        iter->right = new_node;
                        return true;
                    }
            }
            //數字比目前node小
            else if(stoi(data) < stoi(iter->data))
            {
                //std::cout << "Smaller than node\n";

                if(iter -> left != nullptr)
                    iter = iter->left;
                else
                    {
                        //std::cout << "Put left node\n";
                        iter->left = new_node;
                        return true;
                    }
            }
            //數字與目前node相等
            else
            {
                //std::cout << "Equal node\n";
                delete new_node;
                return false;
            }
        }
    }

    bool serach(T target)
    {
        TreeNode<T> *iter = this->root;
        while(iter != nullptr)
        {
            //數字比目前node大
            if(stoi(target) > stoi(iter->data))
            {
                if(iter -> right != nullptr)
                    iter = iter->right;
                else
                    return false;
            }
            //數字比目前node小
            else if(stoi(target) < stoi(iter->data))
            {
                if(iter -> left != nullptr)
                    iter = iter->left;
                else
                    return false;
            }
            //數字與目前node相等
            else
            {
                return true;
            }
        }

        return false;
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

    void inorder_str(TreeNode<T> *cur_node, std::string &order_str)
    {
      if(cur_node->left != nullptr)
        inorder_str(cur_node->left, order_str);

      if(order_str.length() == 0)
          order_str += cur_node->data;
      else
          order_str += "," + cur_node->data;

      if(cur_node->right != nullptr)
          inorder_str(cur_node->right, order_str);
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

      //把字串分開，並轉成數字(NULL表示成INT_MIN)
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
    }

    static bool isValidSerialization(std::string tree)
    {
      auto check_string_correct = [](std::string check)
      {
        if(check == "" || check == "NULLL" || check.find(" ") != std::string::npos)
        {
          //std::cout << "Check str:"<< check << "\nFalse\n";
          return false;
        }
        else
        {
          //std::cout << "Check str:" << check << "\nTrue\n";
          return true;
        }
      };

      BinarySearchTree<std::string> test;

      std::stringstream comma_split(tree);
      std::string sub_str;
      Queue<std::string> data_queue;
      Queue<TreeNode<T>*> next_queue;

      //字串最後方有逗號，則不是樹
      if(tree[tree.length()-1] == ',')
        return false;

      //把字串分開，並轉成數字
      while(std::getline(comma_split, sub_str, ','))
      {
        if(check_string_correct(sub_str))
          data_queue.enqueue(sub_str);
        else
          return false;
      }

      std::string buf;
      bool set_root = true;
      while(!data_queue.isEmpty())
      {
        TreeNode<T>* cur_node;

        //第一次放樹根
        if(set_root)
        {
          test.setRoot(data_queue.dequeue());
          set_root = false;

          cur_node = test.root;
          //std::cout << "root_node:" << cur_node->data << std::endl;
        }
        //之後的node
        else
        {
          if(next_queue.isEmpty())
            cur_node = 0;
          else
            cur_node = next_queue.dequeue();
          //std::cout << "cur_node:" << cur_node->data << std::endl;
        }

        
        //左node可放
        if(!data_queue.isEmpty())
        {
          //std::cout << "Left\n";
          if(!check_string_correct(buf = data_queue.dequeue()) || check_string_correct(buf) && cur_node == 0)
            return false;

          if(buf == "NULL")
            cur_node->left = 0;
          else
          {
            cur_node->left = new TreeNode<T>(buf);
            next_queue.enqueue(cur_node->left);
          }
          //std::cout << "left node place:" << cur_node->left->data << std::endl;
        }

        
        //右node可放
        if(!data_queue.isEmpty())
        {
          //std::cout << "Right\n";
          if(!check_string_correct(buf = data_queue.dequeue()) || check_string_correct(buf) && cur_node == 0)
            return false;

          if(buf == "NULL")
            cur_node->right = 0;
          else
          {
            cur_node->right = new TreeNode<T>(buf);
            next_queue.enqueue(cur_node->right);
          }
          //std::cout << "right node place:" << cur_node->right->data << std::endl;
        }
      }

      return true;
    }

    static bool isValidBinarySearchTree(std::string tree)
    {
      auto isnumber = [](std::string test)
      {
        for(auto it : test)
        {
          if(!('0' <= it && it <= '9'))
            return false;
        }
        return true;
      };
      auto compare = [=](std::string a, std::string b)
      {
        if(isnumber(a) && isnumber(b))
          return stoi(a) < stoi(b);
        else
          return a < b;
      };

      BinarySearchTree<std::string> check;
      check.deSerialize(tree);
      std::string order_str, buf, buf2;
      check.inorder_str(check.root, order_str);

      std::stringstream stream(order_str);
      
      std::getline(stream, buf, ',');
      while(std::getline(stream, buf2, ','))
      {
        if(!compare(buf, buf2))
          return false;
        
        buf = buf2;
      }
      
      return true;
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

private:
    std::string order_str;
};

int main()
{
  //freopen("input.txt","r",stdin);
  //freopen("output.txt","w",stdout);

  std::string line, buf;
  while(std::getline(std::cin, line))
  {
    BinarySearchTree<std::string> tree;
    
    if(!tree.isValidSerialization(line))
      std::cout << "Serialization invalid\n";
    else if(!tree.isValidBinarySearchTree(line))
      std::cout << "Binary Search Tree invalid\n";
    else
      std::cout << "OK\n";
  }
}