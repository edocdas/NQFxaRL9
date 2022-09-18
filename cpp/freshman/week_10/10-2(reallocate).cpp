#include <iostream>
template <typename T>
void print(const T &a)
{
  for(int i = 0;i <= a.index;i++)
    std::cout << a.box[i] << ' ';
  std::cout << std::endl;
}

class container
{
protected:
    int *box;
    int len;
    void copy(int *from, int *to, int l)
    {
        for (int i = 0; i < l; i++)
            to[i] = from[i];
    }

public:
    container() : box(NULL), len(1) {}
    container(int l)
    {
        int *tmp = new int[l];
        this->len = l;
        this->box = tmp;
    }
    container(const container &a)
    {
        int *tmp = new int[a.len];
        copy(a.box, tmp, a.len);
        this->len = a.len;
    }
    int getLen() const
    {
        return this->len;
    }
    virtual bool put_in(int obj) = 0;
    virtual int *take_out(void) = 0;
};

class queue : public container
{
public:
  template <typename T> friend void print(const T &a);
  queue():container(1){} //不會用到吧
  queue(int len):container(len){}
  bool put_in(int obj);
  int* take_out();
  bool reallocate(int len)
  {
      int *tmp = new int[len];
      if(!tmp)
          return false;
      copy(this->box, tmp, this->len);
      delete box;
      this->box = tmp;
      this->len = len;

      return true;
  }

protected:
  int index=-1; //預設為-1
};

class priority_queue : public queue
{
public:
  template <typename T> friend void print(const T &a);
  priority_queue(int len, bool f):queue(len), order(f){}
  int* take_out();
private:
  bool order;
};

bool queue::put_in(int obj)
{
  if(index+1 == len)
    if(!reallocate(len*2))
      return false;

  box[index+1] = obj;
  index++;
  return true;

}

int* queue::take_out()
{
  //std::cout << "Call queue take out\n";
  if(index == -1)
    return nullptr;
  else
  {
    int *ptr = new int;
    *ptr = box[0];
    for(int i = 0;i < index;i++)
      box[i] = box[i+1];
    index--;
    return ptr;
  }
}

int* priority_queue::take_out()
{
  //std::cout << "Call priority_queue take out\n";
  if(index == -1)
    return nullptr;
  else
  {
    int *ptr = new int, goal = -1, remove_index = -1;
    if(order)
    {
      for(int i = 0;i <= index;i++)
      {
        if(goal == -1 || box[i] > goal)
        {
          goal = box[i];
          remove_index = i;
        }
      }
      for(int i = remove_index;i < index;i++)
      {
        box[i] = box[i+1];
      }
      index--;
    }
    else
    {
      for(int i = 0;i <= index;i++)
      {
        if(goal == -1 || box[i] < goal)
        {
          goal = box[i];
          remove_index = i;
        }
      }
      for(int i = remove_index;i < index;i++)
      {
        box[i] = box[i+1];
      }
      index--;
    }
    *ptr = goal;
    return ptr;
  }
}



int main(){
  queue a(5);
  for(int i = 1;i <= 10;i++)
  {
    a.put_in(i);
  }
  print(a);
  for(int i = 0;i < 5;i++)
  {
    a.take_out();
    print(a);
  }

  priority_queue b(5,true);
  /*for(int i = 1;i <= 5;i++)
  {
    b.put_in(i);
  }*/
  b.put_in(2);
  b.put_in(4);
  b.put_in(5);
  b.put_in(4);
  b.put_in(5);

  //print(b);
  queue *test = &b;
  print(*test);
  for(int i = 0;i < 5;i++)
  {
    int *output = test->take_out();
    std::cout << "output" << *output << '\n';
    print(*test);
  }
}
