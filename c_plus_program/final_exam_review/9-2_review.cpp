#include<iostream>
#include<set>
#include<vector>
#include<climits>
#include<cmath>
#include<iomanip>

class Region
{
public:
  Region(int a, int b, int c, int d):x_a(a), y_a(b), x_b(c), y_b(d){}
  int x_a, y_a;
  int x_b, y_b;
};

class Icon
{
public:
  Icon(int a,int b):x(a), y(b){}
  int x, y;
};

bool Inregion(int x, int y, std::vector<Region> d_region)
{
  for(int i = 0;i < d_region.size();i++)
  {
    if(x >= d_region[i].x_a && x <= d_region[i].x_b && y >= d_region[i].y_a
       && y <= d_region[i].y_b)
      return true;
  }
  return false;
}

int main()
{
  std::vector<Region> d_region;
  std::vector<Icon> d_icon;
  int buf_1, buf_2, buf_3, buf_4;

  char ch;
  while(std::cin >> ch, ch != '#')
  {
    if(ch == 'I')
    {
      std::cin >> buf_1 >> buf_2;
      d_icon.push_back(Icon(buf_1, buf_2));
    }
    else if(ch == 'R')
    {
      std::cin >> buf_1 >> buf_2 >> buf_3 >> buf_4;
      d_region.push_back(Region(buf_1, buf_2, buf_3, buf_4));
    }
    else if(ch == 'M')
    {
      std::cin >> buf_1 >> buf_2;

      char target = '#';
      for(int i = 0;i < d_region.size();i++)
      {
        if(buf_1 >= d_region[i].x_a && buf_1 <= d_region[i].x_b && buf_2 >= d_region[i].y_a
           && buf_2 <= d_region[i].y_b)
          target = 'A' + i;
      }
      if(target != '#')
      {
        std::cout << target << std::endl;
        continue;
      }

      //記得用double
      double Max = INT_MAX;
      std::set<int> set_res;
      for(int i = 0;i < d_icon.size();i++)
      {
        if(Inregion(d_icon[i].x, d_icon[i].y, d_region))
          continue;

        if(sqrt(pow(d_icon[i].x-buf_1,2)+pow(d_icon[i].y-buf_2,2)) < Max)
        {
          Max = sqrt(pow(d_icon[i].x-buf_1,2)+pow(d_icon[i].y-buf_2,2));
          set_res.clear();
          set_res.insert(i+1);
        }
        else if(sqrt(pow(d_icon[i].x-buf_1,2)+pow(d_icon[i].y-buf_2,2)) == Max)
        {
          set_res.insert(i+1);
        }
      }

      for(auto it : set_res)
        std::cout << std::setw(3) << it;
      std::cout << "\n";
    }
  }
}
