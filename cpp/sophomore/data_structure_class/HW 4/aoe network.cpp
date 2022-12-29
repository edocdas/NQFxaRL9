#include<iostream>
#include<list>
#include<stack>
#include<climits>

template<typename T>
void print_arr(T *arr, int size)
{
  for(int i = 0;i < size;i++)
    std::cout << arr[i] << " ";
  std::cout << "\n";
}

const int max = 7;

//目前上限設定為9個node
template<class T>
class Graph{
public:
  Graph()
  {
    for(int i = 0;i < max;i++)
      latest_arr[i] = INT_MAX;
  }

  friend void print_arr(T, int);
  void insert(int from, int to, int weight)
  {
    link_arr[from].insert(link_arr[from].end(), to);
    link_arr_reverse[to].insert(link_arr_reverse[to].end(), from);
    link_arr[from].sort();
    link_arr_reverse[to].sort();

    weight_arr[from][to] = weight;
  }

  int get_list_index(std::list<T> *check)
  {
    for(int i = 0;i < max;i++)
    {
      if(check == &link_arr[i])
        return i;
    }
    
    std::cerr << "list out of index\n";
    return -1;
  }

  int get_reverse_list_index(std::list<T> *check)
  {
    for(int i = 0;i < max;i++)
    {
      if(check == &link_arr_reverse[i])
        return i;
    }
    
    std::cerr << "reverse list out of index\n";
    return -1;
  }

  void aoe_network()
  {
    auto get_ee = [this]()
    {
      std::stack<std::list<T>*> left_node;
      left_node.push(&link_arr[0]);
      while(!left_node.empty())
      {
        std::list<T> *cur_list = left_node.top();
        left_node.pop();
        int from = get_list_index(cur_list);
        for(auto to : *cur_list)
        {
          if(earliest_arr[from] + weight_arr[from][to] > earliest_arr[to])
            earliest_arr[to] = earliest_arr[from] + weight_arr[from][to];
          
          left_node.push(&link_arr[to]);
        }
      }
    };
    
    auto get_le = [this]()
    {
      latest_arr[max-1] = earliest_arr[max-1];

      std::stack<std::list<T>*> left_node;
      left_node.push(&link_arr_reverse[max-1]);
      while(!left_node.empty())
      {
        std::list<T> *cur_list = left_node.top();
        left_node.pop();
        int from = get_reverse_list_index(cur_list);
        for(auto to : *cur_list)
        {
          if(latest_arr[from] - weight_arr[to][from] < latest_arr[to])
            latest_arr[to] = latest_arr[from] - weight_arr[to][from];
          
          left_node.push(&link_arr_reverse[to]);
        }
      }
    };

    auto get_crit_path = [this]()
    {
      std::cout << "Crit path node:0";
      for(int i = 1;i < max;i++)
      {
        if(latest_arr[i]-earliest_arr[i] == 0)
          std::cout << "," << i;
      }
      std::cout << "\n";
    };

    get_ee();
    get_le();
    print_arr(earliest_arr, max);
    print_arr(latest_arr, max);
    get_crit_path();

  }

  void print_list()
  {
    for(int i = 0;i < max;i++)
    {
      for(auto it : link_arr_reverse[i])
        std::cout << it << " ";
      std::cout << "\n";
    }
  }

private:
std::list<T> link_arr[max], link_arr_reverse[max];
T weight_arr[max][max] = {0}, earliest_arr[max] = {0}, latest_arr[max] = {0};
};

int main()
{
  Graph<int> g;

  //需要更改14行的max更改node數目，max就是目前圖的node總數目
  /*

  // max 為 9
  g.insert(0,1,6);
  g.insert(0,2,4);
  g.insert(0,3,5);
  g.insert(1,4,1);
  g.insert(2,4,1);
  g.insert(3,5,2);
  g.insert(4,6,9);
  g.insert(4,7,7);
  g.insert(5,7,4);
  g.insert(6,8,2);
  g.insert(7,8,4);
  */


  // max 為 7
  g.insert(0,1,3);
  g.insert(0,2,8);
  g.insert(1,3,5);
  g.insert(3,4,4);
  g.insert(2,4,2);
  g.insert(3,5,2);
  g.insert(4,5,5);
  g.insert(5,6,3);
  std::cout << "insert complete\n";
  g.print_list();

  g.aoe_network();
}