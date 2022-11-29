#include <iostream>

using namespace std;

enum Boolean { FALSE, TRUE};
template <class Type> class List;
template <class Type> class ListIterator;

template <class Type>
class ListNode {
friend class List<Type>;
friend class ListIterator<Type>;
private:
    Type data;
    ListNode *link;
    ListNode(Type);
};

template <class Type>
ListNode<Type>::ListNode(Type element)
{
    data = element;
    link = 0;
}

template <class Type>
class List {
friend class ListIterator<Type>;
public:
    List() {first = 0;};
    void Insert(Type);
    void Delete(Type);
    void print();
    int size();

    int count(Type);
    bool exist(Type);
    int replaceALL(Type, Type);
    List<Type> subList(int, int);
    void shift(char, int);
    

    void Concatenate(List<Type>);
    void Invert();
private:
    ListNode<Type> *first;
};

//從前端加入
template <class Type>
void List<Type>::Insert(Type k)
{
ListNode<Type> *newnode = new ListNode<Type>(k);
newnode->link = first;
first = newnode;
}

template <class Type>
void List<Type>::Delete(Type k)
{
    ListNode<Type> *previous = 0;
    for (ListNode<Type> *current = first;current;previous = current, current = current->link)
    {
        if(current->data == k)
        {
            if (previous)
                previous->link = current->link;
            else
                first = first->link;

            delete current;
            return;
        }
    }
}

template <class Type>
void List<Type>::print()
{
    ListNode<Type> *iter = first;
    while(iter)
    {
        std::cout << iter->data << " ";
        iter = iter->link;
    }
    cout << endl;
}

template <class Type>
int List<Type>::size()
{
    int count = 0;
    ListNode<Type> *iter = first;
    while(iter)
    {
        iter = iter->link;
        count++;
    }
    return count;
}

template <class Type>
int List<Type>::count(Type compare)
{
    int count = 0;
    ListNode<Type> *iter = first;
    while(iter)
    {
        if(compare == iter->data)
            count++;
        iter = iter->link;
    }
    return count;
}

template <class Type>
bool List<Type>::exist(Type compare)
{
    ListNode<Type> *iter = first;
    while(iter)
    {
        if(compare == iter->data)
            return true;
        iter = iter->link;
    }
    return false;
}

template <class Type>
int List<Type>::replaceALL(Type target, Type replace)
{
    ListNode<Type> *iter = first;
    int count = 0;
    while(iter)
    {
        if(target == iter->data)
        {
            iter->data = replace;
            count++;
        }
        iter = iter->link;
    }
    return count;
}

//兩個index皆包含的方式
template <class Type>
List<Type> List<Type>::subList(int begin_i, int end_i)
{
    ListNode<Type> *iter = first;
    List<Type> sub_list;
    int index = 0;
    //找到對的起始點
    while(iter && index < begin_i)
    {
        iter = iter->link;
        index++;
    }

    //開始複製
    while(iter && index <= end_i)
    {
        sub_list.Insert(iter->data);
        iter = iter->link;
        index++;
    }

    sub_list.Invert();
    return sub_list;
}

template <class Type>
void List<Type>::shift(char dir, int times)
{
    int real_times = times % this->size();

    //不需要更動
    if(real_times == 0)
        return;

    //如果方向為向左
    if(dir == 'L' && real_times != 0)
        real_times = this->size() - real_times;

    ListNode<Type> *old_first = first, *iter = first;
    for(int i = 0;i < real_times;i++)
    {
        //特殊情況，需要把連結斬斷
        if(i + 1 == real_times)
        {
            ListNode<Type> *buf = iter->link;
            iter->link = nullptr;
            iter = buf;
        }
        //普通狀況
        else
        {
            iter = iter->link;
        }
    }

    this->first = iter;
    while(true)
    {
        if(iter->link != nullptr)
            iter = iter->link;
        else
        {
            iter->link = old_first;
            return;
        }
    }
}


template <class Type>
void List<Type>::Invert()
// A chain x is inverted so that if x = (a0, a1, ..., an),
// then, after execution, x = (an, ..., a1)
{
    ListNode<Type> *p = first, *q = 0; // q trails p
    while (p) {
       ListNode<Type> *r = q; q = p; // r trails q
       p = p->link; // p moves to next node
       q->link = r; // link q to preceding node
    }
    first = q;
}

template <class Type>
void List<Type>::Concatenate(List<Type> b)
// this = (a1, ..., am) and y = (b1, ..., bm), m, n >= 0
// produces the new chain z = (a1, ..., am, b1, ..., bn) in this.
{
    if (! first) {first = b.first; return;}
    if (b.first) {
	for (ListNode<Type> *p = first; p->link; p = p->link) // no body
	    p->link = b.first;
    }
}

template <class Type>
class ListIterator {
public:
    ListIterator(const List<Type>& l): list(l), current (l.first) {};
    Boolean NotNull();
    Boolean NextNotNull();
    Type* First();
    Type* Next();
private:
    const List<Type> &list;  // refers to an existing list
    ListNode<Type>* current; // points to a node in list
};

template <class Type> //check that current element in list is non-null
Boolean ListIterator<Type>::NotNull()
{
if (current) return TRUE;
else return FALSE;
}

template <class Type>  // check that the next element in list is non-null
Boolean ListIterator<Type>::NextNotNull()
{
if (current && current->link) return TRUE;
else return FALSE;
}

template <class Type> // return a pointer to the first element of list
Type* ListIterator<Type>::First() {
      if (list.first) return &list.first->data;
      else return 0;
}

template <class Type> // return a pointer to the next element of list
Type* ListIterator<Type>::Next() {
      if (current) {
	 current = current->link;
	 return &current->data;
      }
      else return 0;
}

int sum(const List<int>& l)
{
  ListIterator<int> li(l);  //li is associated with list l
  if (!li.NotNull()) return 0; // empty list, return 0
  int retvalue = *li.First(); // get first element
  while (li.NextNotNull())  // make sure that next element exists
     retvalue += *li.Next(); // get it, add it to current total
  return retvalue;
}



//template <class Type>
ostream& operator<<(ostream& os, List<char>& l)
{
    ListIterator<char> li(l);
    if (!li.NotNull()) return os;
    os << *li.First() << endl;
    while  (li.NextNotNull())
	 os << *li.Next() << endl;
    return os;
}

int main()
{
   List<int> intlist;
    intlist.Insert(5);
    intlist.Insert(5);
    intlist.Insert(5);
    intlist.Insert(5);
    intlist.Insert(5);
    intlist.Insert(15);
    intlist.Insert(4);
    intlist.Insert(4);
    intlist.Insert(4);
    intlist.Insert(4);
    intlist.Insert(25);
    intlist.Insert(35);

    intlist.print();
    cout << "Count test\n";
    cout << intlist.count(4) << endl;
    cout << intlist.count(5) << endl;
    cout << intlist.count(6) << endl;
    cout << "Exist test\n";
    cout << intlist.exist(6) << endl;
    cout << intlist.exist(15) << endl;
    cout << intlist.exist(16) << endl;

    cout << "Replace test\n";
    intlist.replaceALL(4, 10);
    intlist.print();

    cout << "Sublist test\n";
    List<int> copy_list = intlist.subList(3, 7);
    copy_list.print();
    List<int> copy_list2 = intlist.subList(8, 10000);
    copy_list2.print();
    List<int> copy_list3 = intlist.subList(0, 10);
    copy_list3.print();

    cout << "Shift test\n";
    intlist.shift('R', 5);
    intlist.print();
    intlist.shift('R', 30);
    intlist.print();
    intlist.shift('L', 11);
    intlist.print();
    intlist.shift('L', 12);
    intlist.print();
    intlist.shift('R', 12);
    intlist.print();

    intlist.Delete(20);
    intlist.Delete(15);
    intlist.Delete(35);
    cout << sum(intlist) << endl;
    intlist.print();

}