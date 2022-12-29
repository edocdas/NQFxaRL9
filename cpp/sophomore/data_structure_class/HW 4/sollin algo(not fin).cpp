#include<iostream>
#include<climits>
#include<list>

#define SIZE 4

void print_arr(int* arr, int size)
{
	for(int i = 0; i < size;i++)
	{
		std::cout << arr[i] << " ";
	}
	std::cout << std::endl;
}

class Graph
{
public:
	void addedge(int start, int end, int weight)
	{
		if(start >= SIZE || end >= SIZE)
			std::cout << "Index out of range!" << std::endl;
		else
		{
			adjmatrix[start][end] = weight;
			adjmatrix[end][start] = weight;
		}
	}

  void print_list(std::list<int>*list, int count)
  {
    for(int i = 0;i < count;i++)
    {
      std::cout << "list " << i << std::endl;
      for(auto it :list[i])
        std::cout << it << " ";
      std::cout << "\n";
    }
  }

  void sollin_mst()
  {
    std::cout << "first one" << std::endl;
    std::list<int> sub_list[100];
    int list_count = 0;
    for(int i = 0;i < SIZE;i++)
    {
      int min = INT_MAX, index = -1;
      for(int j = 0;j < SIZE;j++)
      {
        if(adjmatrix[i][j] != 0 && adjmatrix[i][j] < min)
        {
          min = adjmatrix[i][j];
          index = j;
        }
      }

      list_weight[list_count] += adjmatrix[i][index];
      sub_list[list_count].push_back(i);
      sub_list[list_count].push_back(index);
      list_count++;
    }

    print_list(sub_list, list_count);
    //print_list(sub_list, list_count);
    list_union(sub_list, list_count);
    std::cout << list_count << "\n";
    print_list(sub_list, list_count);

    std::cout << "the others" << std::endl;

    while(sub_list[1].size() != 0)
    {
      for(int i = 0;i < list_count;i++)
      {
        int min = INT_MAX, index = 0;

        for(auto from : sub_list[i])
        {
          for(int j = i+1;j < SIZE;j++)
          {
            if(adjmatrix[from][j] != 0 &&adjmatrix[from][j] < min)
            {
              min = adjmatrix[from][j];
              index = j;
            }
          }
        }

        sub_list[i].push_back(index);
        list_weight[i] += adjmatrix[i][index];
      }

      list_union(sub_list, list_count);
    }
  }

  void list_union(std::list<int> *list_arr, int &list_count)
  {
    for(int j = 0;j < list_count;j++)
    {
      for(int i = 1;i < list_count;i++)
      {
        std::list<int> &first_list = list_arr[i-1], &second_list = list_arr[i];

        bool duplicate = false;
        for(auto it : first_list)
        {
          for(auto it2 : second_list)
          {
            if(it == it2)
              duplicate = true;
          }
        }

        if(duplicate)
        {
          for(auto it2 : second_list)
            first_list.push_back(it2);
          
          first_list.sort();
          remove_dupli(first_list);
          second_list.clear();
          list_weight[i-1] += list_weight[i];


          for(int k = i;k < list_count-1;k++)
          {
            list_arr[k] = list_arr[k+1];
            list_weight[k] = list_weight[k+1];
          }
          list_count--;

          i = 0;
        }
      }
    }
  }

  void remove_dupli(std::list<int> &first_list)
  {
    int before = *first_list.begin();
    for(auto it = ++first_list.begin();it != first_list.end();it++)
    {
      if(before == *it)
      {
        first_list.erase(it);
        before = *first_list.begin();
        it = first_list.begin();
      }
      else
        before = *it;
    }
  }


	void print_adj()
	{
		for(int i = 0;i < SIZE;i++)
		{
			for(int j = 0;j < SIZE;j++)
			{
				std::cout << adjmatrix[i][j] << " ";
			}
			std::cout << std::endl;
		}
	}

private:
	int adjmatrix[SIZE][SIZE] = {0};
	int node_count = 0;
  int list_weight[SIZE] = {0};
};

int main()
{
	Graph g;
	/* test 1
	g.addedge(0, 1, 28);
	g.addedge(1, 2, 16);
	g.addedge(2, 3, 12);
	g.addedge(3, 4, 22);
	g.addedge(4, 5, 25);
	g.addedge(5, 0, 10);
	g.addedge(6, 1, 14);
	g.addedge(6, 3, 18);
	g.addedge(6, 4, 24);*/
	
	/* test 2
	g.addedge(0, 1, 5);
	g.addedge(1, 2, 10);
	g.addedge(2, 3, 5);
	g.addedge(3, 4, 7);
	g.addedge(4, 5, 6);
	g.addedge(5, 0, 3);
	g.addedge(1, 4, 1);
	g.addedge(6, 1, 4);
	g.addedge(6, 2, 8);
	g.addedge(6, 3, 9);
	g.addedge(6, 4, 2);
	*/
	
  g.addedge(0, 1, 4);
  g.addedge(0, 2, 5);
  g.addedge(0, 3, 1);
  g.addedge(1, 2, 3);
  g.addedge(3, 1, 2);


  g.sollin_mst();
	//g.print_adj();

}