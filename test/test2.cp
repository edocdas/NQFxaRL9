#include<vector>
#include<iostream>
#include<algorithm>
#include<ctime>
#include<cstdlib>
#include<map>

int main()
{
	/*std::vector<int> vec_int;
	srand(time(NULL));

	for(int i = 0;i < 10;i++)
	{
		vec_int.push_back(rand() % 5);
	}
	//vec_int.push_back(3);

	std::sort(vec_int.begin(), vec_int.end(), [](int a, int b){return a < b;});
	std::for_each(vec_int.begin(), vec_int.end(), [](int a){std::cout << a << std::endl;});
	//std::reverse(vec_int.begin(), vec_int.end());

	std::for_each(vec_int.begin(), vec_int.end(), [](int a){std::cout << a << std::endl;});

	std::cout << std::binary_search(vec_int.begin(), vec_int.end(), 3) << std::endl;
	*/

	std::map<int, int> map_a;
	map_a.insert(std::pair<int,int>(1,1));
	map_a.insert(std::pair<int,int>(2,2));
	map_a.insert(std::pair<int,int>(3,3));
	map_a.insert(std::pair<int,int>(4,4));
	map_a.erase(4);



	for(const auto it : map_a)
	{
		std::cout << it.first << " " << it.second << std::endl;
	}

}