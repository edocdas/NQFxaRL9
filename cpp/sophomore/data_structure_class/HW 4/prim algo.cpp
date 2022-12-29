#include<iostream>
#include<climits>

#define SIZE 7

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

	void prim_mst()
	{
		int key[SIZE], visit[SIZE] = {0}, predecessor[SIZE];

		//初始化
		for(int i = 0;i < SIZE;i++)
		{
			key[i] = INT_MAX;
			predecessor[i] = -1;
		}

		//prim演算法
		for(int i = 0;i < SIZE;i++)
		{
			auto get_min_key_index = [](int* key, int *visit) ->int
			{
				int min = INT_MAX, min_index = 0;
				for(int i = 0;i < SIZE;i++)
				{
					if(key[i] < min && visit[i] != 1)
					{
						min = key[i];
						min_index = i;
					}
				}
				return min_index;
			};


			//找出目前最小的key，且還沒走過
			int min_key_index = get_min_key_index(key, visit);
			//標記此node已走過
			visit[min_key_index] = 1;
			for(int j = 0;j < SIZE;j++)
			{
				//如果此路徑存在，且尚未走過，且比目前記錄的key值小
				if(adjmatrix[min_key_index][j] != 0 && visit[j] != 1 && adjmatrix[min_key_index][j] < key[j])
				{
					key[j] = adjmatrix[min_key_index][j];
					predecessor[j] = min_key_index;
				}
			}

			std::cout << "key: ";
			print_arr(key, SIZE);
			std::cout << "visit: ";
			print_arr(visit, SIZE);
			std::cout << "predecessor: ";
			print_arr(predecessor, SIZE);
		}

    int sum = 0;
		for(int i = 0;i < SIZE;i++)
		{
			if(i == 0)
      {
				std::cout << i << " to " << i << " weight:" << adjmatrix[i][i] << std::endl;
        sum += adjmatrix[i][i];
      }
			else
      {
				std::cout << i << " to " << predecessor[i] << " weight:" << adjmatrix[i][predecessor[i]] << std::endl;
        sum += adjmatrix[i][predecessor[i]];
      }
		}

    std::cout << "total weight:" << sum << std::endl;
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
	
	*/
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

	//g.print_adj();
	g.prim_mst();
}