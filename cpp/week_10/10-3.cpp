#include<iostream>
#include<cstdio>
#include<vector>
#include<utility>
#include<set>

class airline{
public:
  void input();
  bool compare();
  void recur(std::vector<std::pair<char,char> >, char, std::set<char> *);
  void print(); //測試用途
private:
  std::vector<std::pair<char, char> > data_a;
  std::vector<std::pair<char, char> > data_b;
  std::set<char> cities; //全部的城市
};

void airline::input()
{
  int case_a = 0, case_b = 0;

  std::cin >> case_a;
  for(int j = 0;j < case_a;j++)
  {
    char input_a, input_b;
    std::cin >> input_a >> std::ws >>input_b;
    data_a.push_back(std::make_pair(input_a, input_b));
    data_a.push_back(std::make_pair(input_b, input_a));
    cities.insert(input_a);
    cities.insert(input_b);
  }

  std::cin >> case_b;
  for(int j = 0;j < case_b;j++)
  {
    char input_a, input_b;
    std::cin >> input_a >> std::ws >> input_b;
    data_b.push_back(std::make_pair(input_a, input_b));
    data_b.push_back(std::make_pair(input_b, input_a));
    cities.insert(input_a);
    cities.insert(input_b);
  }
}

bool airline::compare()
{
  std::set<char> a_cities, b_cities; //結果比較
  for(auto current_city: cities)
  {
    a_cities.clear(); //一開始先清空
    b_cities.clear();

    recur(this->data_a, current_city, &a_cities);
    recur(this->data_b, current_city, &b_cities);

    if(a_cities != b_cities)
      return false;
  }
  return true;
}

void airline::recur(std::vector<std::pair<char,char> > data,
  char cur_city, std::set<char>* cities)
{
  std::set<char> next_cities;
  for(auto element:data) //找到與cur_city對應的城市
  {
    if(element.first == cur_city && cities->find(element.second) == cities->end())
    {
      next_cities.insert(element.second);
    }
  }
  cities->insert(cur_city);
  for(auto element:next_cities)
  {
    recur(data, element, cities);
  }
}

void airline::print()
{
  for(auto it :data_a)
    std::cout << it.first << " " << it.second << std::endl;

  for(auto it :data_b)
    std::cout << it.first << " " << it.second << std::endl;

  for(auto it :cities)
    std::cout << it << std::endl;
}

int main(){
  //freopen("input.txt","r",stdin);
  //freopen("output.txt","w",stdout);

  int test_case = 0;
  std::cin >> test_case;
  for(int i = 1;i <= test_case;i++)
  {
    airline data;
    data.input();
    //data.print();
    data.compare() ? std::cout << "YES\n" : std::cout << "NO\n";
    if(i!=test_case)
      std::cout << "\n";
  }
}
