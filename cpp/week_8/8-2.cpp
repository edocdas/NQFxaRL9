#include <iostream>

class container
{
protected:
    int *box;
    int len;
    void copy(int *from, int *to, int l)
    {
        for(int i=0; i<l; i++)
            to[i] = from[i];
    }
public:
    container(): box(nullptr), len(1) {}
    //不能在一開始的時候就用reallocate，因為box不存在
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
        this->box = tmp; //寫錯？
    }
    bool reallocate(int l)
    {
        int *tmp = new int[l];
        if(!tmp)
            return false;
        copy(this->box, tmp, this->len);
        delete box;
        this->box = tmp;
        this->len = l;

        //std::cout << "len is:" << len << std::endl;
        return true;
    }

};

class stack : private container{
public:
  stack():index(-1){box = new int;}
  stack(int l):index(-1)
  {
    box = new int;
    reallocate(l);
  }
  stack(const stack &a)
  {
    int *tmp = new int[a.len];
    copy(a.box, tmp, a.len);
    this->len = a.len;
    this->box = tmp;
    this->index = a.index;
  }

  bool push(int data);
  int *pop();
  int getLen() {return len;}
  bool increase();
  void traversal();

private:
  int index;
};

bool stack::push(int data)
{
  if(index+1 == len)
    return false;
  else
  {
    box[index+1] = data;
    index++;
    return true;
  }
}

int* stack::pop()
{
  if(index == -1)
    return nullptr;
  else
  {
    int *ptr = new int;
    *ptr = box[index];
    index--;
    return ptr;
  }
}

bool stack::increase()
{
  if(reallocate(len*2))
    return true;
  else
    return false;
}

void stack::traversal(){
  if(index == -1)
    std::cout << "empty\n";
  else
  {
    for(int i = 0;i <= index;i++)
    {
        std::cout << box[i] << " ";
    }
    std::cout << '\n';
  }
}

int main(){
  stack A;
  A.increase();
  std::cout << A.getLen() << std::endl;
  A.increase(); //變成四個位子
  std::cout << A.getLen() << std::endl;
  /*
  A.push(1);
  A.push(2);
  A.push(3);
  A.push(4);

  stack B(A);

  int *put_out;
  while(put_out = B.pop(), put_out != nullptr)
  {
    std::cout << "Put out:" << *put_out << "\n";
    B.traversal();
  }*/

  for(int i = 1;i <= 5;i++)
  {
    std::cout << "enqueue:" << i << " " <<A.push(i) << std::endl;
    std::cout << "getlen:" << A.getLen() << std::endl;
  }

  int *put_out;
  while(put_out = A.pop(), put_out != nullptr)
  {
    std::cout << "Put out:" << *put_out << "\n";
    A.traversal();
  }
}
