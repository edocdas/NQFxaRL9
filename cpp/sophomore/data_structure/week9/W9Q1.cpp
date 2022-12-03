#include <cstdlib>
#include <iostream>
#include <stdexcept>
#include <ctime>

template<class T>
class Node
{
public:
	Node()
	{
		data = new T;
	}
	Node(T d)
	{
		data = new T;
		(*data) = d;
	}
	Node &operator=(T d)
	{
		(*data) = d;
		return *this;
	}
	friend std::ostream &operator<<(std::ostream &out, Node n)
	{
		out<<*(n.data);
		return out;
	}
	friend std::ostream &operator<<(std::ostream &out, Node *n)
	{
		out<<*(n->data);
		return out;
	}
	void setData(T d)
	{
		*data = d;
	}
	T &getData() const
	{
		return *data;
	}
protected:
	T *data;
};

template<class T>
class ListNode : public Node<T>
{
public:
	ListNode() : Node<T>()
	{
		prev = NULL;
		next = NULL;
	}
	ListNode(T d) : Node<T>(d)
	{
		prev = NULL;
		next = NULL;
	}
	ListNode(ListNode *p, ListNode *n) : Node<T>()
	{
		prev = p;
		next = n;
	}
	ListNode(T d, ListNode *p, ListNode *n) : Node<T>(d)
	{
		prev = p;
		next = n;
	}
	ListNode *getNext() const
	{
		return next;
	}
	ListNode *getPrev() const
	{
		return prev;
	}
	void setNext(ListNode *n)
	{
		next = n;
	}
	void setPrev(ListNode *p)
	{
		prev = p;
	}
	ListNode &operator=(T d)
	{
		this->setData(d);
		return *this;
	}
private:
	ListNode *prev, *next;
};

template<class T>
class LinkList
{
public:
	LinkList()
	{
		head = NULL;
		tail = NULL;
	}
	void addFromHead(T d)
	{
		ListNode<T> *node = new ListNode<T>(d);
		if(head != NULL)
		{
			head->setPrev(node);
		}
		node->setNext(head);
		head = node;
		if(tail == NULL)
			tail = node;
	}
	void addFromTail(T d)
	{
		ListNode<T> *node = new ListNode<T>(d);
		if(tail != NULL)
		{
			tail->setNext(node);
		}
		node->setPrev(tail);
		tail = node;
		if(head == NULL)
			head = node;
	}
	void addAfter(ListNode<T> *at, T d)
	{
		if(!exist(at))
			return;
		ListNode<T> *node = new ListNode<T>(d);
		if(at->getNext() != NULL)
			at->getNext()->setPrev(node);
		node->setNext(at->getNext());
		at->setNext(node);
		node->setPrev(at);
		if(node->getNext() == NULL)
			tail = node;
	}
	ListNode<T> *removeFromHead()
	{
		ListNode<T> *n = head;
		if(head != NULL)
		{
			head = head->getNext();
			if(head != NULL)
				head->setPrev(NULL);
			else
				tail = NULL;
			n->setNext(NULL);
		}
		return n;
	}
	ListNode<T> *removeFromTail()
	{
		ListNode<T> *n = tail;
		if(tail != NULL)
		{
			tail = tail->getPrev();
			if(tail != NULL)
				tail->setNext(NULL);
			else
				head = NULL;
			n->setPrev(NULL);
		}
		return n;
	}
	ListNode<T> *remove(ListNode<T> *n)
	{
		if(!exist(n))
			return NULL;
		if(n == head)
			return removeFromHead();
		if(n == tail)
			return removeFromTail();
		n->getPrev()->setNext(n->getNext());
		n->getNext()->setPrev(n->getPrev());
		n->setNext(NULL);
		n->setPrev(NULL);
		return n;
	}
	ListNode<T> *exist(T d)
	{
		ListNode<T> *j = head;
		while(j != NULL)
		{
			if(j->getData() == d)
				return j;
			j = j->getNext();
		}
		return NULL;
	}
	bool exist(ListNode<T> *n)
	{
		ListNode<T> *j = head;
		while(j != NULL)
		{
			if(j == n)
				return true;
			j = j->getNext();
		}
		return false;
	}
	ListNode<T> &operator[](int i)
	{
		ListNode<T> *j = head;
		int k;
		for(k = 0;k < i && j != NULL;k ++)
			j = j->getNext();
		if(j == NULL)
			throw std::invalid_argument("index does not exist.");
		return *j;
	}
	void print() const
	{
		ListNode<T> *j;
		j = head;
		while(j != NULL)
		{
			std::cout<<(*j)<<" ";
			j = j->getNext();
		}
		std::cout<<std::endl;
	}

  ListNode<T> * getHead()
  {
    return head;
  }

  T getfront()
  {
    return head->getData();
  }

  bool isEmpty()
  {
    return head == nullptr;
  }

  int size()
  {
    int count = 0;
    for(ListNode<T>*iter = head;iter;iter = iter->getNext())
    {
      count++;
    }
    return count;
  }
protected:
	ListNode<T> *head, *tail;
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
    list = new LinkList<T>;
  }

  /**
   * Add a data to queue
   * @param data: data to be added to queue
   */
  void enqueue(T data)
  {
    list->addFromTail(data);
  }

  /**
   * Remove a data from queue and return it
   * @return the data removed from queue
   */
  T dequeue()
  {
    T buf = list->getfront();
    list->remove(list->exist(buf));
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

  private: 
    LinkList<T> *list = nullptr;
};

/*
	Please finish the TreeNode class, TreeNode class respresent a node in a general tree.
	A general tree is different from binary tree, every node in binary tree have at most two child node, but a node in general tree may have more than two child node.
*/
template<class T>
class TreeNode : public Node<T>
{
public:
	TreeNode() : Node<T>()
	{ 
    child = new LinkList<TreeNode<T> *>();
	}
	TreeNode(T d) : Node<T>(d)
	{
    child = new LinkList<TreeNode<T> *>();
	}
	/*
		Add a child to this node.
	*/
	void addChild(TreeNode *n)
	{
    child->addFromTail(n);
	}
	/*
		Add a child to this node.
	*/
	void addChild(T d)
	{
    TreeNode<T> *buf = new TreeNode<T>(d);
    child->addFromTail(buf);
	}
	/*
		Return the nth child of the node.
	*/
	TreeNode<T> *operator[](int n)
	{
    TreeNode<T>*iter = child->head;
    for(int i = 0;i < n && iter;i++,iter = iter->getNext())
    {
      if(i+1 == n)
        return iter;
    }
    return 0;
	}

  LinkList<TreeNode<T> *> * getChildren()
  {
    return child;
  }
	
	
private:
	LinkList<TreeNode<T> *> *child;
};

/*
	Please finish the Tree class. Tree class respresent a general tree, that means node on this tree may have more than two child node.
	
*/
template<class T>
class Tree
{
public:
	Tree()
	{
	}
	/*
		return the nth node on this tree with level order.
	*/
	TreeNode<T> *operator[](int n)
	{
		int count = 0;
		Queue<LinkList<TreeNode<T>*> *> node;
		node.enqueue(this->root->getChildren());

		if(n == 0)
			return root;

		while(!node.isEmpty())
		{
			LinkList<TreeNode<T>*> *buf = node.front();
			node.dequeue();
			

			for(ListNode<TreeNode<T>*> *iter = buf->getHead();iter;iter = iter->getNext())
			{
			count++;

			//找到需要的數目了
			if(count == n)
				return iter->getData();
			if(iter->getData()->getChildren()->getHead() != nullptr)
				node.enqueue(iter->getData()->getChildren());
			}
		}
	}
	/*
		return the number of nodes on this tree.
	*/
	int count()
	{
    if(this->root == nullptr)
      return 0;

    int count = 1;
    Queue<LinkList<TreeNode<T>*> *> node;
    node.enqueue(this->root->getChildren());

    while(!node.isEmpty())
    {
        LinkList<TreeNode<T>*> *buf = node.front();
        node.dequeue();
        

        for(ListNode<TreeNode<T>*> *iter = buf->getHead();iter;iter = iter->getNext())
        {
          count++;
          if(iter->getData()->getChildren()->getHead() != nullptr)
            node.enqueue(iter->getData()->getChildren());
        }
    }

    return count;
	}
	/*
		print all the node on this tree with level order.
	*/
	void levelOrder()
	{
    std::string order_str = std::to_string(root->getData());
    Queue<LinkList<TreeNode<T>*> *> node;
    node.enqueue(this->root->getChildren());

    while(!node.isEmpty())
    {
        LinkList<TreeNode<T>*> *buf = node.front();
        node.dequeue();

        for(ListNode<TreeNode<T>*> *iter = buf->getHead();iter;iter = iter->getNext())
        {
          order_str += "," + std::to_string(iter->getData()->getData());

          if(iter->getData()->getChildren()->getHead() != nullptr)
            node.enqueue(iter->getData()->getChildren());
        }
    }

    std::cout << "Levelorder\n";
    std::cout << order_str << std::endl;
	}
	/*
		print all the node on this tree with preorder.
	*/
	void preorder()
	{
    std::string order_str;
    preorder(root, order_str);
    std::cout << order_str << std::endl;
	}

  void preorder(TreeNode<T> *cur_node, std::string &order_str)
  {
    if(order_str.length() == 0)
      order_str += std::to_string(cur_node->getData());
    else
      order_str += "," + std::to_string(cur_node->getData());

    int size = cur_node->getChildren()->size(), front_half = 0, end_half = 0;
    if(size % 2 == 0)
    {
      front_half = end_half = (size / 2);
    }
    else
    {
		//如果數目為奇數，那左半邊會多一個
      front_half = size / 2 + 1;
      end_half = size / 2;
    }
    ListNode<TreeNode<T>*> *iter = cur_node->getChildren()->getHead();
    for(int i = 0;i < front_half && iter;i++, iter = iter->getNext())
    {
      preorder(iter->getData(), order_str);
    }

    for(int i = 0;i < end_half && iter;i++, iter = iter->getNext())
    {
      preorder(iter->getData(), order_str);
    }
  }
	/*
		print all the node on this tree with postorder.
	*/
	void postorder()
	{
    std::string order_str;
    postorder(root, order_str);
    std::cout << order_str << std::endl;
	}

  void postorder(TreeNode<T> *cur_node, std::string &order_str)
  {
    int size = cur_node->getChildren()->size(), front_half = 0, end_half = 0;
    if(size % 2 == 0)
    {
      front_half = end_half = (size / 2);
    }
    else
    {
      front_half = size / 2 + 1;
      end_half = size / 2;
    }
    //std::cout << front_half << " " << end_half << std::endl;
    ListNode<TreeNode<T>*> *iter = cur_node->getChildren()->getHead();
    for(int i = 0;i < front_half && iter;i++, iter = iter->getNext())
    {
      postorder(iter->getData(), order_str);
    }

    for(int i = 0;i < end_half && iter;i++, iter = iter->getNext())
    {
      postorder(iter->getData(), order_str);
    }

    if(order_str.length() == 0)
      order_str += std::to_string(cur_node->getData());
    else
      order_str += "," + std::to_string(cur_node->getData());
  }
	/*
		set the root of this tree.
	*/
	void setRoot(T d)
	{
    root = new TreeNode<T>(d);
    std::cout << "setRoot" << root->getData() << std::endl;
	}
private:
	TreeNode<T> *root = 0;
};

int main()
{
	Tree<int> *tree = new Tree<int>();
	srand(time(NULL));
	int j, k, i;
	for(j = 0;j < 10;j ++)
	{
    std::cout << tree->count() << std::endl;
		if(tree->count() == 0)
			tree->setRoot(rand() % 100);
		else
		{
			k = rand() % tree->count();
      int rand_num = rand() % 100;
      std::cout << "index:" << k << " rand_num:" << rand_num << std::endl;
			(*tree)[k]->addChild(rand_num);
		}
	}
	tree->levelOrder();
	tree->preorder();
	tree->postorder();
}
