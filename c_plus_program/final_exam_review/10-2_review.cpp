

class queue : public container
{
public:
  //queue():container(){}
  queue(int len):container(len){}
  bool put_in(int obj)
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

  int *take_out()
  {
    if(index == -1)
      return nullptr;

    int *ptr = new int;
    *ptr = box[0];

    for(int i = 0;i < index;i++)
    {
      box[i] = box[i+1];
    }
    index--;
    return ptr;
  }
protected:
  int index = -1;
};

class priority_queue : public queue
{
public:
  priority_queue(int len, bool f):queue(len), order(f){}
  bool put_in(int obj)
  {
    if(queue::put_in(obj))
    {
      for(int i = 0;i <= index;i++)
      {
        //注意！！！ 這邊是j = i
        for(int j = i;j <= index;j++)
        {
          if(((box[i] < box[j]) && order) || ((box[i] > box[j]) && !order))
          {
            int buf = box[i];
            box[i] = box[j];
            box[j] = buf;
          }
        }
      }
      return true;
    }
    return false;
  }

private:
  bool order;
};
int main(){}
