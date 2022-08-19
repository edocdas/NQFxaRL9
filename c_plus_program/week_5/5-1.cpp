#include<iostream>

class container
{
public:
  container(): box(0), len(0), index(-1){increase();}
  container(int input_len): len(input_len), index(-1)
  {
    reallocate(input_len);
    increase();
   }
  ~container()
  {
    delete[] box; //刪除box
    decrease();
  }

  int getLen(){return len;}
  int getIndex(){return index;}

  void traversal();
  bool push(int data);
  int pop();
  static int getCount(){return count;}

private:

  int *box; //本體
  int len; //container的大小
  int index; //目前指到哪一個
  static int count; //總共有幾個container
  bool reallocate(int size);
  static void increase(){count+=1;} //初始器用
  static void decrease(){count-=1;} //解構器用
};
int container::count = 0;

bool container::reallocate(int size){
  //std::cout << "\nreallocate size:" << size << '\n';
  int* new_box = new int[size];

  if(new_box == nullptr) // new object fail
    return false;
  else
  {
    for(int i = 0;i <= index;i++) //if index == -1(box empty), this will do nothing
    {
      new_box[i] = box[i];
    }

    if(box) //box exist
      delete[] box;
    box = new_box;
    len = size;

    return true;
  }
}

void container::traversal(){
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

bool container::push(int data){
  //std::cout << "index:" << index << " len:" << len << '\n';
  if(index+1 == len)
  {
    int reallo_size = 0;
    if(len == 0)
      reallo_size = 1;
    else
      reallo_size = len * 2;

    if(!reallocate(reallo_size))
    {
      return false;
    }
  }

  index++;
  box[index] = data;
  return true;
}

int container::pop(){
  if(index == -1)
    return 0;
  else
  {
    int output = box[0];
    for(int i = 0;i < index;i++)
    {
      box[i] = box[i+1];
    }
    //box[index] = 0; //delete?
    index--;
    return output;
  }
}

int main(){

  container *ptr = new container, *ptr2 = new container;
  ptr->push(1);
  ptr->push(2);
  ptr->push(3);
  ptr->push(4);
  ptr->push(4);
  ptr->push(4);
  ptr->push(4);
  ptr->push(4);
  ptr->traversal();
  ptr->pop();
  ptr->traversal();

  //b.traversal();

  //std::cout << a.getCount() << '\n';

  //std::cout << b.getCount() << '\n';
}
