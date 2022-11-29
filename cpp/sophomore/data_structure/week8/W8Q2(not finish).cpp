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

  T find_char(const char ch)
  {
    Node<T> *iter = head;
    while(iter != tail)
    {
      if(iter->getData()->getData() == std::string(1, ch))
        return iter->getData();
      else
        iter = iter->getNext();
    }
    return nullptr;
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

//先宣告GeneralTreeNode
template<class T> class GeneralTreeNode;

/**
 * A abstract class for treenode
 * @tparam T Stored data of the node
 */
template<class T>
class TreeNode {
  public:
    /**
     * Get the Parent
     * @return TreeNode<T>* parent
     */
    virtual GeneralTreeNode<T>* getParent() = 0;

    /**
     * Set the Parent
     * @param parent to set
     */
    virtual void setParent(GeneralTreeNode<T>* parent) = 0;

    /**
     * Get the Children
     * @return LinkedList<TreeNode<T>*>* children
     */
    virtual LinkedList<GeneralTreeNode<T>*>* getChildren() = 0;

    /**
     * Set the Children
     * @param children to set
     */
    virtual void setChildren(LinkedList<GeneralTreeNode<T>*>* children) = 0;

  protected:
    /**
     * Data stored in the node
     */
    T data;

    /**
     * A linked list for children nodes
     */
    LinkedList<GeneralTreeNode<T>*>* children;
};


template<class T>
class GeneralTreeNode : public TreeNode<T> {
public:
  GeneralTreeNode()
  {
    children = new LinkedList<GeneralTreeNode<T>*>;
  }
  GeneralTreeNode(T data)
  {
    this->data = data;
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
  

private:
  GeneralTreeNode<T> *parent = nullptr;
  T data;
  LinkedList<GeneralTreeNode<T>*>* children = nullptr;
};


/**
 * A abstract class for tree
 * 
 * @tparam T Stored data in each node of the tree
 * @tparam D Data type that is used to insert, remove and search.
 */
 
template<class T, class D>
class Tree {
  public:
    /**
     * Levelorder traversal of the tree
     */
    //virtual void levelorder() = 0;

    /**
     * Inorder traversal of the tree
     */
    //virtual void inorder() = 0;

    /**
     * Preorder traversal of the tree
     */
    //virtual void preorder() = 0;

    /**
     * Postorder traversal of the tree
     */
    //virtual void postorder() = 0;

    /**
     * Insert a node to the tree with the given data if it not exists.
     * @param data data to insert
     * @return true if the node is inserted, false if the node already exists
     */
    virtual bool insert(D data) = 0;

    /**
     * Remove a node from the tree with the given data if it exists.
     * @param data data to insert
     * @return true if the node is removed successfully, false if the node is not found 
     */
    //virtual bool remove(D data) = 0;

    /**
     * Find a node with the given data if it exists.
     * @param data data to search
     * @return the node if found, NULL if not found
     */
    virtual TreeNode<T>* search(D data) = 0;

    /**
     * Set the Root object
     * @param root to set to root
     */
    virtual void setRoot(GeneralTreeNode<T>* root) = 0;

    /**
     * Deserialize the string to a tree with levelorder traversal
     * @param tree to be deserialized
     */
    //virtual void deSerialize(std::string tree) = 0;

    /**
     * Serialize the tree to a string with levelorder traversal
     * @return the serialized string
     */
    //virtual std::string serialize() = 0;
  protected:
  /**
   * First layer of the tree will be the children of root
   */
    TreeNode<T>* root;
};

template<class T, class D>
class GeneralTree : public Tree<T, D> {
  public:
    GeneralTree() {
       this -> root = new GeneralTreeNode<T>();
    }
    
    //更改樹的root?
    void setRoot(GeneralTreeNode<T>* root)
    {
      this->root = root;
    }

    //插入一個資料到樹中
    bool insert(D data)
    {
      //這個樹是空的
      if(this->root->getChildren() == nullptr)
      {
        //創建一個新的linkedlist，放入資料後，再給root node
        GeneralTreeNode<T>* iter;
        for(int i = 0;i < data.length();i++)
        {
          LinkedList<GeneralTreeNode<T>*> *children_list = new LinkedList<GeneralTreeNode<T>*>;
          GeneralTreeNode<T> *buf_node = new GeneralTreeNode<T>(std::string(data[i],1));
          children_list->addToTail(buf_node);

          if(i == 0)
            this->root->setChildren(children_list);
          else
            iter->setChildren(children_list);
            
          iter = buf_node;
        }
        return true;
      }
      //已經放東西了
      else
      {
        LinkedList<GeneralTreeNode<T>*> *iter = this->root->getChildren();

        int index = 0;
        GeneralTreeNode<T>* target_node;
        while(true)
        {
          //在linkedlist中，找不到該字元
          if((target_node = iter->find_char(data[index])) == 0)
          {
            GeneralTreeNode<T> *buf_node = new GeneralTreeNode<T>(std::string(1, data[index]));
            iter->addToTail(buf_node);
            return true;
          }
          //在linkedlist中，找到該字元，且輸入資料尚未到底
          if((target_node = iter->find_char(data[index])) && index + 1 != data.length())
          {
            iter = target_node->getChildren();
            index++;
          }
          else
          {
            return false;
          }
        }
      }
    }

    GeneralTreeNode<T>* search(D data)
    {
      //這個樹是空的
      if(this->root->getChildren() == nullptr)
      {
        return nullptr;
      }
      //已經放東西了
      else
      {
        LinkedList<GeneralTreeNode<T>*> *iter = this->root->getChildren();
        std::cout << iter << std::endl;

        int index = 0;
        GeneralTreeNode<T>* target_node;
        while(true)
        {
          //在linkedlist中，找不到該字元
          if((target_node = iter->find_char(data[index])) == 0)
          {
            return nullptr;
          }
          //在linkedlist中，找到該字元，且輸入資料尚未到底
          if((target_node = iter->find_char(data[index])) && index + 1 != data.length())
          {
            iter = target_node->getChildren();
            index++;
          }
          else
          {
            return target_node;
          }
        }
      }
    }


  private:
    GeneralTreeNode<T>* root;
};


/*
疑問
1.我們把TreeNode繼承給GeneralTreeNode，但是TreeNode的函式的參數是TreeNode
  是否都要改成GeneralTreeNode?
2.T&D如果都用string，那會有差別嗎?
*/

int main() {
  GeneralTree<std::string, std::string> a;
  a.insert("hello");
  a.search("hello");
  std::cout << a.search("hello");
  return 0;
}

