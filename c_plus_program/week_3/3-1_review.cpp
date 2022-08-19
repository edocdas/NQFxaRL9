#include<map>
#include<string>
#include<iostream>

struct child{
  std::string father;
  std::string mother;
  std::string name;
};

int main()
{
  std::map <std::string, std::string>data;
  struct child ch_data[3100];
  int test_line = 0, child_count = 0;

  std::cin >> test_line;
  for(int i = 1;i <= test_line;i++)
  {
    std::string a, b;
    std::cin >> a >> b;
    if(b == "dominant" || b == "recessive" || b == "non-existent")
    {
      data.insert(std::make_pair(a,b));
    }
    else
    {
      for(int i = 0;i <= child_count;i++)
      {
        if(i == child_count)
        {
          ch_data[i].father = a;
          ch_data[i].name = b;
          child_count++;
          break;
        }
        else if(ch_data[i].name == b)
        {
          ch_data[i].mother = a;
          break;
        }
      }
    }
  }
  for(int i = 0;i < child_count;i++)
  {
    std::string pa = data.find(ch_data[i].father)->second;
    std::string ma = data.find(ch_data[i].mother)->second;
    //std::cout << pa << " " << ma << std::endl;
    if(pa == "dominant" && ma == "dominant" || pa == "dominant" && ma == "recessive"
        || pa == "recessive" && ma == "dominant")
        {
          data.insert(std::make_pair(ch_data[i].name,"dominant"));
          //std::cout << "1" << std::endl;
        }

    else if(pa == "non-existent" && ma == "non-existent" || pa == "non-existent" && ma == "recessive"
        || pa == "recessive" && ma == "non-existent")
        {
          data.insert(std::make_pair(ch_data[i].name,"non-existent"));
          //std::cout << "2" << std::endl;
        }
    else
      {
        data.insert(std::make_pair(ch_data[i].name,"recessive"));
        //std::cout << "3" << std::endl;
      }

  }

  for(auto it:data)
    std::cout << it.first << " " << it.second << std::endl;
}
