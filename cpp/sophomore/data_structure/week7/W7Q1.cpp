#include<iostream>
#include<cstdlib>
#include<ctime>

using namespace std;

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

class Tree
{
public:
	Tree()
	{
    	root = 0;
		int j, k;
		for(j = 0;j < 20;j ++)
			for(k = 0;k < 4;k ++)
				node[j][k] = -1;
	}
	int insert(int n)
	{
		int f = root, index = 0;
		while(node[index][0] != -1)
			index ++;
		if(index >= 20)
			return -1;
		if(node[root][0] == -1)
		{
			node[root][0] = 1;
			node[root][1] = n;
			return 1;
		}
		else
		{
			node[index][0] = 1;
			node[index][1] = n;
			while(1)
			{
				if(node[f][1] < n)
				{
					if(node[f][3] == -1)
					{
						node[f][3] = index;
						return 1;
					}
					else
					{
						f = node[f][3];
					}
				}
				else
				{
					if(node[f][2] == -1)
					{
						node[f][2] = index;
						return 1;
					}
					else
					{
						f = node[f][2];
					}
				}
			}
		}
	}
	void inorder()
	{
		int index = 0;
		if(node[index][2] != -1)
			inorder(node[index][2]);
		output.length() ? output += " " + std::to_string(node[index][1]) : output += std::to_string(node[index][1]);
		if(node[index][3] != -1)
			inorder(node[index][3]);


		std::cout << "Inorder\n" << output;
		output.clear();
	}

	void inorder(int index)
	{
		if(node[index][2] != -1)
			inorder(node[index][2]);
		output.length() ? output += " " + std::to_string(node[index][1]) : output += std::to_string(node[index][1]);
		if(node[index][3] != -1)
			inorder(node[index][3]);
	}
	void preorder()
	{
		int index = 0;
		output.length() ? output += " " + std::to_string(node[index][1]) : output += std::to_string(node[index][1]);
		if(node[index][2] != -1)
			preorder(node[index][2]);
		if(node[index][3] != -1)
			preorder(node[index][3]);


		std::cout << "Preorder\n" << output;
		output.clear();
	}

	void preorder(int index)
	{

		output.length() ? output += " " + std::to_string(node[index][1]) : output += std::to_string(node[index][1]);
		if(node[index][2] != -1)
			preorder(node[index][2]);
		if(node[index][3] != -1)
			preorder(node[index][3]);
	}

	void postorder()
	{
		int index = 0;
		if(node[index][2] != -1)
			postorder(node[index][2]);
		if(node[index][3] != -1)
			postorder(node[index][3]);
		output.length() ? output += " " + std::to_string(node[index][1]) : output += std::to_string(node[index][1]);

		std::cout << "Postorder\n" << output;
		output.clear();
	}

	void postorder(int index)
	{
		if(node[index][2] != -1)
			postorder(node[index][2]);
		if(node[index][3] != -1)
			postorder(node[index][3]);
		output.length() ? output += " " + std::to_string(node[index][1]) : output += std::to_string(node[index][1]);
	}
	void levelorder()
	{
		Queue<int> a;
		a.enqueue(0);
		while(!a.isEmpty())
		{
			int index = a.dequeue();
			output.length() ? output += " " + std::to_string(node[index][1]) : output += std::to_string(node[index][1]);

			if(node[index][2] != -1)
				a.enqueue(node[index][2]);
			if(node[index][3] != -1)
				a.enqueue(node[index][3]);
		}

		
        std::cout << "Levelorder\n";
        std::cout << output << std::endl;
        output.clear();
	}
	void print()
	{
		for(int i = 0;i < 20;i++)
		{	
			std::cout << "row:" << i << " ";
			for(int j = 0;j < 4;j++)
			{
				std::cout << node[i][j] << " ";
			}
			std::cout << "\n";
		}
	}

private:
	int node[20][4];
	int root;
	std::string output;
};

int main()
{
	Tree *tree = new Tree();
	int j, node;
	srand(time(NULL));
	for(j = 0;j < 10;j ++)
	{
		node = rand() % 10;
		tree->insert(node);
	}

	//tree->print();

	tree->inorder();
	printf("\n");
	tree->preorder();
	printf("\n");
	tree->postorder();
	printf("\n");
	tree->levelorder();
	printf("\n");

}
