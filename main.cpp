#include <iostream>
#include <sstream>


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

  int size()
  {
    int count = 0;
    for(Node<T>*iter = head;iter;iter = iter->getNext())
    {
      count++;
    }
    return count;
  }

  void print()
  {
    auto while_print_node = [=](Node<T> *iter)
    {
      while(true)
      {
        auto print_type = [](Node<T> *iter)
        {
            std::cout << iter->getData() << " ";
        };


        print_type(iter);
        if(iter != this->getTail())
            iter = iter->getNext();
        else
            return;
      }
    };


    Node<T> *iter = this->getHead();
    std::cout << "Print list:";
    while_print_node(iter);
    std::cout << "\n";
  }

  private: 
    Node<T> *head = nullptr;
    Node<T> *tail = nullptr;
};

template<class T>
class TreeNodeLinkedList : public LinkedList<T>
{
  public:

  void print()
  {
    auto while_print_node = [=](Node<T> *iter)
    {
      while(true)
      {
        auto print_type = [](Node<T> *iter)
        {
            std::cout << iter->getData()->getData() << " ";
        };


        print_type(iter);
        if(iter != this->getTail())
            iter = iter->getNext();
        else
            return;
      }
    };


    Node<T> *iter = this->getHead();
    std::cout << "Print list:";
    while_print_node(iter);
    std::cout << "\n";
  }

  void print_path()
  {
    auto while_print_node = [=](Node<T> *iter)
    {
      while(true)
      {
        auto print_type = [](Node<T> *iter)
        {
            std::cout << iter->getData()->getPath() << " ";
        };


        print_type(iter);
        if(iter != this->getTail())
            iter = iter->getNext();
        else
            return;
      }
    };


    Node<T> *iter = this->getHead();
    std::cout << "Print list:";
    while_print_node(iter);
    std::cout << "\n";
  }


  void list_sort_data()
  {
    auto for_loop_selection_sort = [&]()
    {
      for(Node<T>*iter_a = this->getHead();iter_a;iter_a = iter_a->getNext())
      {
        for(Node<T>*iter_b = iter_a;iter_b;iter_b = iter_b->getNext())
        {
          auto sort_condiction = [&]() -> bool
          {
            return iter_a->getData()->getData() > iter_b->getData()->getData();
          };

          if(sort_condiction())
          {
            T buf = iter_a->getData();
            iter_a->setData(iter_b->getData());
            iter_b->setData(buf);
          }
        }
      }
    };


    for_loop_selection_sort();
  };

  void list_sort_path()
  {
    auto for_loop_selection_sort = [&]()
    {
      for(Node<T>*iter_a = this->getHead();iter_a;iter_a = iter_a->getNext())
      {
        for(Node<T>*iter_b = iter_a;iter_b;iter_b = iter_b->getNext())
        {
          auto sort_condiction = [&]() -> bool
          {
            return iter_a->getData()->getPath() > iter_b->getData()->getPath();
          };

          if(sort_condiction())
          {
            T buf = iter_a->getData();
            iter_a->setData(iter_b->getData());
            iter_b->setData(buf);
          }
        }
      }
    };


    for_loop_selection_sort();
  };

  T find_path_string(std::string target)
  {
    auto find_while_loop = [&](Node<T> *iter) -> T
    {
      while(true)
      {
        auto find_string_condiction = [&]() -> bool
        {
          return iter->getData()->getPath() == target;
        };

        if(find_string_condiction())
          return iter->getData();
        else if(iter != this->getTail())
          iter = iter->getNext();
        else
          return nullptr;
      }
    };


    if(this->isEmpty())
      return nullptr;
    Node<T> *iter = this->getHead();
    return find_while_loop(iter);
  }
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

template<class T>
class GeneralTreeNode{
  public:
    GeneralTreeNode()
    {
      children = new TreeNodeLinkedList<GeneralTreeNode<T>*>;
    }
    GeneralTreeNode(std::string data)
    {
      this->data = data;
      children = new TreeNodeLinkedList<GeneralTreeNode<T>*>;
    }

    GeneralTreeNode<T>* getParent()
    {
      return parent;
    }
    void setParent(GeneralTreeNode<T>* parent)
    {
      this->parent = parent;
    }
    TreeNodeLinkedList<GeneralTreeNode<T>*>* getChildren()
    {
      return this->children;
    }
    void setChildren(TreeNodeLinkedList<GeneralTreeNode<T>*>* children)
    {
      this->children = children;
    }

    T getData()
    {
      return data;
    }

    void setData(T data)
    {
      this->data = data;
    }

    void setPath(std::string path)
    {
      this->path = path;
    }

    void setType(std::string type)
    {
      this->type = type;
    }

    std::string getPath()
    {
      return path;
    }

    std::string getType()
    {
      return type;
    }
    

  private:
    T data;
    GeneralTreeNode<T> *parent = nullptr; 
    TreeNodeLinkedList<GeneralTreeNode<T>*>* children = nullptr;
    std::string path, type;
};

template<class T>
class GeneralTree{
  public:
    GeneralTree() {
       this -> root = new GeneralTreeNode<T>();
       this -> root->setType("dir");
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
    bool insert(T path, T data, T type)
    {
      auto path_split = [=](auto path_substr_list)
      {
        std::string buf;
        std::istringstream stream(path.substr(1));
        while(std::getline(stream, buf, '/'))
          path_substr_list.addToTail(buf);
      };


      TreeNodeLinkedList<std::string> path_substr_list;
      path_split(path_substr_list);
      int path_link_size = path_substr_list.size();

      GeneralTreeNode<T>* parent_node = this->root;
      //這個樹是空的
      if(this->root->getChildren()->isEmpty())
      {
        //std::cout << "This is a empty tree.\n";
        //創建一個新的linkedlist，放入資料後，再給root node
        for(int i = 0;i < path_link_size;i++)
        {
          auto get_node_in_pathlist = [&]() -> GeneralTreeNode<T> *
          {
            GeneralTreeNode<T> *buf_node = new GeneralTreeNode<T>();
            buf_node->setPath(path_substr_list.getHead()->getData());
            path_substr_list.deleteData(buf_node->getPath());
            
            return buf_node;
          };

          auto set_node_type = [&](GeneralTreeNode<T> *node)
          {
            if(i+1 == path_link_size)
              node->setType(type);
            else
              node->setType("dir");
          };

          auto set_node_data = [&](GeneralTreeNode<T> *node)
          {
            if(i+1 == path_link_size)
            {
              node->setData(data);
            }
          };

          auto set_node_parent = [&](GeneralTreeNode<T> *node)
          {
            node->setParent(parent_node);
          };


          GeneralTreeNode<T> *new_node = get_node_in_pathlist();
          parent_node->getChildren()->addToTail(new_node);
          
          set_node_parent(new_node);
          set_node_type(new_node);
          set_node_data(new_node);
          parent_node = new_node;
        }
        return true;
      }
      //已經放東西了
      else
      {
        TreeNodeLinkedList<GeneralTreeNode<T>*> *iter_list = this->root->getChildren();

        int index = 0;
        bool first_put = true;
        GeneralTreeNode<T>* target_node = this->root;
        while(true)
        {
          std::string cur_str = path_substr_list.getfront();
          path_substr_list.deleteData(cur_str);

          //在linkedlist中，找不到該字元
          if(iter_list->find_path_string(cur_str) == nullptr)
          {
            path_substr_list.addToHead(cur_str);
            //std::cout << "can't find that character\n";

            for(int i = index;i < path_link_size;i++)
            {
              GeneralTreeNode<T> *buf_node = new GeneralTreeNode<T>();
              buf_node->setPath(path_substr_list.getfront());
              path_substr_list.deleteData(path_substr_list.getfront());
              //std::cout << "buf_node:" << buf_node->getData() << std::endl;

              if(i+1 != path_link_size)
                buf_node->setType("dir");

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
              
              //設置parent
              buf_node->setParent(target_node);

              target_node = buf_node;

              //最後一個node，設定資料與屬性
              if(i+1 == path_link_size)
              {
                target_node->setType(type);
                target_node->setData(data);
              }
            }
            return true;
          }
          //在linkedlist中，找到該字元，且輸入資料尚未到底
          if(iter_list->find_path_string(cur_str) != nullptr && index + 1 != path_link_size)
          {
            target_node = iter_list->find_path_string(cur_str);
            iter_list = target_node->getChildren();
            index++;
          }
          else
          {
            return false;
          }
        }
      }
    }

    bool search(T path)
    {
      //這個樹是空的
      if(this->root->getChildren() == nullptr)
      {
        return false;
      }
      //已經放東西了
      else
      {
        LinkedList<std::string> path_substr;
        std::string buf;
        std::istringstream stream(path.substr(1));
        while(std::getline(stream, buf, '/'))
          path_substr.addToTail(buf);
      
        int path_link_size = path_substr.size();


        LinkedList<GeneralTreeNode<T>*> *iter = this->root->getChildren();
        int index = 0;
        GeneralTreeNode<T>* target_node;

        while(true)
        {
          std::string target_str = path_substr.getfront();
          path_substr.deleteData(target_str);

          target_node = find_str(iter, target_str);
          std::cout << "target_str:" << target_str << std::endl;
          std::cout << "target_node:" << target_node << std::endl;

          //在linkedlist中，找不到該字元
          if(target_node == 0)
          {
            return 0;
          }
          //在linkedlist中，找到該字元，且輸入資料尚未到底
          else if(target_node && index + 1 != path_link_size)
          {
            iter = target_node->getChildren();
            index++;
          }
          else
          {
            return 1;
          }
        }
      }
    }

    GeneralTreeNode<T>* search_get_path(T path)
    {
      //這個樹是空的
      if(this->root->getChildren() == nullptr)
      {
        return 0;
      }
      //已經放東西了
      else
      {
        LinkedList<std::string> path_substr;
        std::string buf;
        std::istringstream stream(path.substr(1));
        while(std::getline(stream, buf, '/'))
          path_substr.addToTail(buf);
      
        int path_link_size = path_substr.size();


        LinkedList<GeneralTreeNode<T>*> *iter = this->root->getChildren();
        int index = 0;
        GeneralTreeNode<T>* target_node;

        while(true)
        {
          std::string target_str = path_substr.getfront();
          path_substr.deleteData(target_str);

          target_node = find_str(iter, target_str);
          std::cout << "target_str:" << target_str << std::endl;
          std::cout << "target_node:" << target_node << std::endl;

          //在linkedlist中，找不到該字元
          if(target_node == 0)
          {
            return 0;
          }
          //在linkedlist中，找到該字元，且輸入資料尚未到底
          else if(target_node && index + 1 != path_link_size)
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

    std::string serialize()
    {
      first_serial();

      LinkedList<GeneralTreeNode<T>*> *list = root->getChildren();
      //print_list_node(list);
      
      
      for(Node<GeneralTreeNode<T>*> *iter = list->getHead();iter;iter = iter->getNext())
      {
        //他是一個檔案
        if(iter->getData()->getType() == "file")
        {
          serial_str += "{\"data\":\"" + iter->getData()->getData() + "\",";
        }
        //他是一個目錄
        else
        {
          serial_str += "{\"children\":[";
          serialize_list(iter->getData()->getChildren());
          serial_str += "],";
        }
        serial_str += "\"path\":\"" + iter->getData()->getPath() + "\",";
        serial_str += "\"type\":\"" + iter->getData()->getType() + "\"}";
        
        if(iter->getNext() != nullptr)
          serial_str += ",";
      }

      serial_str += "],\"path\":\"/\",\"type\":\"dir\"}}";
      
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
        if(iter->getData()->getType() == "file")
        {
          serial_str += "{\"data\":\"" + iter->getData()->getData() + "\",";
        }
        else
        {
          serial_str += "{\"children\":[";
          serialize_list(iter->getData()->getChildren());
          serial_str += "],";
        }
        serial_str += "\"path\":\"" + iter->getData()->getPath() + "\",";
        serial_str += "\"type\":\"" + iter->getData()->getType() + "\"}";
        
        if(iter->getNext() != nullptr)
          serial_str += ",";
      }
    }
    

    void first_serial()
    {
      serial_str.clear(); 
      serial_str = "{\"root\":{\"children\":[";
    }


    void deSerialize(std::string tree)
    {
      root->setPath("/");
      root->setType("dir");

      /*
      把前後不需要輸入的拿掉
      ex. {"root":{"children":[{"children":[{"data":"this is script","path":"script","type":"file"}],"path":"bin","type":"dir"}
          ,{"children":[],"path":"tmp","type":"dir"}
          ,{"children":[],"path":"usr","type":"dir"}],"path":"/","type":"dir"}}
          
          ->[{"children":[{"data":"this is script","path":"script","type":"file"}],"path":"bin","type":"dir"}
            ,{"children":[],"path":"tmp","type":"dir"}
            ,{"children":[],"path":"usr","type":"dir"}]
      */
      tree = tree.substr(20);
      tree = tree.substr(0, tree.length()-26);

      std::cout << "remove root:" << tree << std::endl;
      //因為解析出來的是一個array，開始進入array函式處理
      array_deser(tree, root);
    }


    /*
    分解一個node
    type & path 從後往前找，之後再直接用path_index得出children or data字串
    (以避免他們的字串包含在判斷標準內)

    ex1. {"children":[],"path":"tmp","type":"dir"}
    ex2. {"data":"this is script","path":"script","type":"file"}
    */
    void node_deser(std::string node_str, LinkedList<GeneralTreeNode<T>*>*list)
    {
      std::string children, data, path, type;

      int type_index = node_str.rfind("\"type\":"), path_index = node_str.rfind("\"path\"");
      type = node_str.substr(type_index+8);
      type = type.substr(0, type.length()-2);

      path = node_str.substr(path_index+8, type_index-3-(path_index+7));

      if(node_str.find("\"children\"") == 1)
      {
          children = node_str.substr(12,path_index-1-12);
      }
      else if(node_str.find("\"data\"") == 1)
      {
          data = node_str.substr(9,path_index-2-9);
      }


      //列印這個node(測試用途)
      std::cout << "Children:" << children << std::endl;
      std::cout << "Data:" << data << std::endl;
      std::cout << "Path:" << path << std::endl;
      std::cout << "Type:" << type << std::endl;

      //創建一個新的node
      GeneralTreeNode<T> *new_node = new GeneralTreeNode<T>;
      new_node->setPath(path);
      new_node->setType(type);
      if(data != "")
        new_node->setData(data);

      list->addToTail(new_node);

      //如果還有這個node的children
      if(children != "")
        array_deser(children, new_node);
    }

    /*
    分解一個array
    把這個array分解成各個node，並放在list中
    再使用node的函式處理

    symbol_end_place:找到第一個相符合符號的index

    ex. [{"children":[{"data":"this is script","path":"script","type":"file"}],"path":"bin","type":"dir"}
        ,{"children":[],"path":"tmp","type":"dir"}
        ,{"children":[],"path":"usr","type":"dir"}]

    ->  {"children":[{"data":"this is script","path":"script","type":"file"}],"path":"bin","type":"dir"}
        {"children":[],"path":"tmp","type":"dir"}
        {"children":[],"path":"usr","type":"dir"}
    */
    void array_deser(std::string children_str, GeneralTreeNode<T> *node)
    {
      children_str = children_str.substr(1, children_str.length()-1);
      LinkedList<std::string> array_nodes;
      //遇到array的結尾才會停止
      while(children_str[0] != ']')
      {
        int end_index = symbol_end_place(children_str, '{', '}');
        array_nodes.addToTail(children_str.substr(0, end_index+1));

        //尚未到最後一個node，順便把逗號拿掉
        if(children_str[end_index+1] == ',')
          children_str.erase(0, end_index+2);
        else
          children_str.erase(0, end_index+1);
      }

      for(Node<std::string>*iter = array_nodes.getHead();iter;iter = iter->getNext())
      {
        std::cout << "Current list\n" << iter->getData() << std::endl;
        node_deser(iter->getData(), node->getChildren());
      }
      
      /*std::cout << "List data\n";
      for(Node<std::string>*iter = array_nodes.getHead();iter;iter = iter->getNext())
      {
        std::cout << iter->getData() << std::endl;
      }*/
    }



    int symbol_end_place(std::string str, char left_sym, char right_sym)
    {
      int equal = 0;
      for(int i = 0;i < str.length();i++)
      {
        if(str[i] == left_sym)
          equal++;
        if(str[i] == right_sym)
          equal--;
        
        if(equal == 0)
          return i;
      }

      return -1;
    }

  private:
    GeneralTreeNode<T>* root;
    std::string serial_str;
};

class file_system
{
  public:
  static void mkdir(std::string path, GeneralTree<std::string> *tree)
  {
    if(!tree->search(path))
    {
      tree->insert(path, "", "dir");
    }
  }

  static void touch(std::string path, std::string data, GeneralTree<std::string> *tree)
  {
    if(!tree->search(path))
    {
      tree->insert(path, data, "file");
    }
  }

  static void mv(std::string old_path, std::string new_path, GeneralTree<std::string> *tree)
  {
    if(tree->search(old_path))
    {
      GeneralTreeNode<std::string>* old_children = tree->search_get_path(old_path);
      GeneralTreeNode<std::string>* new_children = tree->search_get_path(new_path);

      delete(new_children->getChildren());
      new_children->setChildren(old_children->getChildren());
      old_children->setChildren(0);
    }
  }

  static void rm(std::string path, GeneralTree<std::string> *tree)
  {
    if(tree->search(path))
    {
      GeneralTreeNode<std::string>* del_node = tree->search_get_path(path);
      GeneralTreeNode<std::string>* del_parent_node = del_node->getParent();

      del_parent_node->getChildren()->deleteData(del_node);
      delete del_node;
    }
  }

  static void cp(std::string old_path, std::string new_path, GeneralTree<std::string> *tree)
  {
    if(tree->search(old_path))
    {
      GeneralTreeNode<std::string>* old_children = tree->search_get_path(old_path);
      GeneralTreeNode<std::string>* new_children = tree->search_get_path(new_path);

      GeneralTreeNode<std::string>* buf_node = new GeneralTreeNode<std::string>();
      buf_node->setData(old_children->getData());
      buf_node->setPath(old_children->getPath());
      buf_node->setType(old_children->getType());
      buf_node->setParent(new_children);

      new_children->getChildren()->addToTail(buf_node);
      list_sort(new_children->getChildren());
      cp_node_iter(old_children->getChildren(), buf_node);

    }
  }

  void static cp_node_iter(LinkedList<GeneralTreeNode<std::string>*>*old_list, GeneralTreeNode<std::string>*node)
  {
    for(Node<GeneralTreeNode<std::string>*>*iter = old_list->getHead();iter;iter = iter->getNext())
    {
      GeneralTreeNode<std::string>* buf_node = new GeneralTreeNode<std::string>();
      buf_node->setData(iter->getData()->getData());
      buf_node->setPath(iter->getData()->getPath());
      buf_node->setType(iter->getData()->getType());
      buf_node->setParent(node);

      node->getChildren()->addToTail(buf_node);
      list_sort(node->getChildren());
      cp_node_iter(iter->getData()->getChildren(), buf_node);
    }
  }
};

#include<cstdio>

int main() {
  //freopen("input.txt", "r", stdin);
  //freopen("output.txt", "w", stdout);

  file_system item;
  GeneralTree<std::string> tree;
  std::string serial_tree, operation;
  std::getline(std::cin, serial_tree);
  tree.deSerialize(serial_tree);
  
  while(std::cin >> operation)
  {
    if(operation == "mv")
    {
      std::string old_path, new_path;
      std::cin >> old_path >> new_path;
      //item.mv(old_path, new_path, tree);
    }
  }



  //std::cout << a.serialize() << std::endl;
  return 0;
}

