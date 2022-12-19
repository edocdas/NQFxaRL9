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
    TreeNode<T> *root = nullptr;
};

template<class T>
class BinarySearchTree : public binarySearchTree<T> {
  public:
    void setRoot(T data)
    {
        this->root = new TreeNode<T>(data);
        //std::cout << "root:" << this->root->data << std::endl;
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

      //找parent
      while(iter != nullptr)
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
      avl_rotate(new_node);
      return true;
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
      while(iter != nullptr)
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

      while(iter->right != nullptr)
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
      TreeNode<T>* del_node;
      if((del_node = search(target)) != nullptr)
      {
        auto remove_parent_bind = [=](TreeNode<T>*del_node)
        {
          if(del_node->parent->left == del_node)
          {
            del_node->parent->left = 0;
          }
          else
          {
            del_node->parent->right = 0;
          }
        };

        auto remove_and_replace = [](TreeNode<T>*del_node, TreeNode<T>*replace_node)
        {
          if(del_node->parent->left == del_node)
          {
            del_node->parent->left = replace_node;
            replace_node->parent = del_node->parent;
          }
          else
          {
            del_node->parent->right = replace_node;
            replace_node->parent = del_node->parent;
          }
        };

        //如果我們刪除的node左右皆沒有child
        if(del_node->left == nullptr && del_node->right == nullptr)
        {
          TreeNode<T>* buf = del_node->parent;
          remove_parent_bind(del_node);
          delete del_node;
          avl_rotate(buf);
        }
        //兩個都有資料
        else if(del_node->left != nullptr && del_node->right != nullptr)
        {
          TreeNode<T>* max_node = Max(del_node->left);
          T buf_data = max_node->data;
          //std::cout << "buf_data:" << buf_data << std::endl;
          Delete(buf_data);
          del_node->data = buf_data;
          //std::cout << "delete ser:" << this->serialize() << std::endl;
        }
        //其中一個有資料
        else
        {
          if(del_node->left != nullptr)
          {
            TreeNode<T>* buf = del_node->parent;
            remove_and_replace(del_node, del_node->left);
            delete(del_node);
            avl_rotate(buf);
          }
          else
          {
            TreeNode<T>* buf = del_node->parent;
            remove_and_replace(del_node, del_node->right);
            delete(del_node);
            avl_rotate(buf);
          }
        }
      }
    }
    
    void preorder()
    {
        //std::cout << "Preorder\n";
        preorder(this->root);
        std::cout << order_str << std::endl;
        order_str.clear();
    }

    void preorder(TreeNode<T> *cur_node)
    {
      if(cur_node == nullptr)
        return;

      if(order_str.length() == 0)
          order_str += cur_node->data;
      else
          order_str += "," + cur_node->data;

      preorder(cur_node->left);
      preorder(cur_node->right);
    }

    void inorder()
    {
        //std::cout << "Inorder\n";
        inorder(this->root);
        std::cout << order_str << std::endl;
        order_str.clear();
    }

    void inorder(TreeNode<T> *cur_node)
    {
      if(cur_node == nullptr)
        return;

      inorder(cur_node->left);

        if(order_str.length() == 0)
            order_str += cur_node->data;
        else
            order_str += "," + cur_node->data;

      inorder(cur_node->right);
    }

    void postorder()
    {
         //std::cout << "Postorder\n";
        postorder(this->root);
        std::cout << order_str << std::endl;
        order_str.clear();
    }

    void postorder(TreeNode<T> *cur_node)
    {
      if(cur_node == nullptr)
        return;
      
      postorder(cur_node->left);
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
            /*if(buf->parent != nullptr)
              std::cout << buf->data << " parent:" << buf->parent->data << std::endl;
            else
              std::cout << buf->data << " parent:empty" << std::endl;*/
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

    void avl_rotate(TreeNode<T>*iter)
    {
      auto balance_factor = [=](TreeNode<T>*node)
      {
        return this->height(node->left) - this->height(node->right);
      };

      auto replace_parent = [](TreeNode<T>*old_node, TreeNode<T>*replace_node)
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
      };

      auto left_rotate = [=](TreeNode<T>*old_parent)
      {
        TreeNode<T> *new_parent = old_parent->right;
        replace_parent(old_parent, new_parent);
        old_parent->right = new_parent->left;
        new_parent->left = old_parent;
        old_parent->parent = new_parent;
        if(old_parent->right != nullptr)
          old_parent->right->parent = old_parent;

        if(old_parent == this->root)
          this->root = new_parent;
      };

      auto right_rotate = [=](TreeNode<T>*old_parent)
      {
        TreeNode<T> *new_parent = old_parent->left;
        replace_parent(old_parent, new_parent);
        old_parent->left = new_parent->right;
        new_parent->right = old_parent;
        old_parent->parent = new_parent;
        if(old_parent->left != nullptr) 
          old_parent->left->parent = old_parent;

        if(old_parent == this->root)
          this->root = new_parent;
      };

      while(iter != nullptr)
      {
        if(balance_factor(iter) <= 1 && balance_factor(iter) >= -1)
        {
          iter = iter->parent;
          continue;
        }
        //左邊過重
        else if(balance_factor(iter) > 1)
        {
          //rl轉動
          if(balance_factor(iter->left) <= -1)
          {
            //std::cout << "rl rotate" << std::endl;
            left_rotate(iter->left);
            right_rotate(iter);
          }
          //r轉動
          else
          {
            //std::cout << "r rotate" << std::endl;
            right_rotate(iter);
          }
        }
        //右邊過重
        else if(balance_factor(iter) < -1)
        {
          //lr轉動
          if(balance_factor(iter->right) >= 1)
          {
            //std::cout << "lr rotate" << std::endl;
            right_rotate(iter->right);
            left_rotate(iter);
          }
          //l轉動
          else
          {
            //std::cout << "l rotate" << std::endl;
            left_rotate(iter);
          }
        }

        //std::cout << this->serialize() << std::endl;
      }
    }

private:
    std::string order_str;
};

int main()
{
  //freopen("input.txt","r",stdin);
  //freopen("output.txt","w",stdout);

  std::string operation, buf;
  BinarySearchTree<std::string> tree;
  while(std::cin >> operation)
  {
    if(operation == "insert")
    {
      std::cin >> buf;
      //std::cout << "insert:" << buf << std::endl;
      tree.insert(buf);
    }
    else if(operation == "delete")
    {
      std::cin >> buf;
      //std::cout << "delete:" << buf << std::endl;
      tree.Delete(buf);
    }
  }

  std::cout << tree.serialize() << std::endl;
}