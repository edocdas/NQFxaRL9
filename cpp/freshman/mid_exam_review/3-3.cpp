//全對
#include<iostream>
#include<string>
#include<map>

struct child
{
  std::string fa;
  std::string ma;
  std::string name;
};

int main(){
  int test_case = 0, child_count = 0;
  std::map <std::string, std::string> data;
  struct child ch_data[3100];
  std::cin >> test_case;
  for(int i = 1;i <= test_case;i++)
  {

    std::string a, b;
    std::cin >> a >> b;
    if(b == "dominant" || b == "recessive" || b == "non-existent")
      data.insert(std::make_pair(a,b));
    else
    {
      for(int i = 0;i <= child_count;i++)
      {
        if(i == child_count)
        {
          ch_data[i].fa = a;
          ch_data[i].name = b;
          child_count++;
          break;
        }else if(ch_data[i].name == b)
        {
          ch_data[i].ma = a;
          break;
        }
      }
    }
  }
  for(int i = 0;i < child_count;i++)
  {
    std::string pa_gene = data.find(ch_data[i].fa)->second;
    std::string ma_gene = data.find(ch_data[i].ma)->second;
    if(pa_gene == "dominant" && ma_gene == "dominant" ||
     pa_gene == "dominant" && ma_gene == "recessive" ||
    pa_gene == "recessive" && ma_gene == "dominant")
      data.insert(std::make_pair(ch_data[i].name,"dominant"));
    else if(pa_gene == "non-existent" && ma_gene == "non-existent" ||
      pa_gene == "non-existent" && ma_gene == "recessive" ||
      pa_gene == "recessive" && ma_gene == "non-existent")
      data.insert(std::make_pair(ch_data[i].name,"non-existent"));
    else
      data.insert(std::make_pair(ch_data[i].name,"recessive"));
  }
  for(auto it:data)
    std::cout << it.first << " " << it.second << std::endl;
}
