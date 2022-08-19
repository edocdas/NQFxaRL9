//https://en.cppreference.com/w/cpp/container/priority_queue
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
  template <typename T> friend void print(const T &a); //測試用途
  //queue():container(1){} //不會用到吧
  queue(int len):container(len){}

  bool put_in(int obj);
  int* take_out();

protected:
  int index=-1; //預設為-1
};

class priority_queue : public queue
{
public:
  template <typename T> friend void print(const T &a); //測試用途
  bool put_in(int obj);
  priority_queue(int len, bool f):queue(len), order(f){}
private:
  bool order;
};

bool queue::put_in(int obj)
{
  if(index+1 == len)
      return false;
  else
  {
    box[index+1] = obj;
    index++;
    return true;
  }
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

bool priority_queue::put_in(int obj)
{
  if(index+1 == len)
      return false;
  else
  {
    box[index+1] = obj;
    index++;

    for(int i = 0;i <= index;i++)
    {
      for(int j = i;j <= index;j++)
      {
        if(order)
        {
          if(box[i] < box[j])
          {
            int buf = box[i];
            box[i] = box[j];
            box[j] = buf;
          }
        }
        else
        {
          if(box[i] > box[j])
          {
            int buf = box[i];
            box[i] = box[j];
            box[j] = buf;
          }
        }
      }
    }
    return true;
  }
}



int main(){
  queue a(5);
  for(int i = 1;i <= 10;i++)
  {
    bool condition = a.put_in(i);
    std::cout << "Put:" << condition << std::endl;
  }
  print(a);
  for(int i = 0;i < 10;i++)
  {
    int* take = a.take_out();
    if(take)
      std::cout << "Take:" << *take << std::endl;
    print(a);
  }

  priority_queue b(5,false);
  queue *test = &b;

  test->put_in(5);
  test->put_in(5);
  test->put_in(1);
  test->put_in(5);
  test->put_in(5);
  //std::cout << "Put:" << condition << std::endl;

  print(*test);
  for(int i = 0;i < 10;i++)
  {
    int* take = test->take_out();
    if(take)
      std::cout << "Take:" << *take << std::endl;
    print(*test);
  }
}
