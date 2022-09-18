#include<iostream>
#include<vector>
#include<climits>
#include<set>
#include<cmath>
#include<iomanip>

class icon
{
public:
  icon(int a, int b):x(a), y(b){}
  int x, y;

};

class region
{
public:
  region(int a, int b, int c, int d):l_x(a), l_y(b), r_x(c), r_y(d){}
  int l_x, l_y, r_x, r_y;
};

bool In_region(int x, int y, region reg)
{
  if(x >= reg.l_x && x <= reg.r_x && y >= reg.l_y && y <= reg.r_y)
    return true;
  else
    return false;
}

bool In_region(int x, int y, std::vector<region> reg)
{
  for(int i = 0;i < reg.size();i++)
  {
    if(x >= reg[i].l_x && x <= reg[i].r_x && y >= reg[i].l_y && y <= reg[i].r_y)
    {
      return true;
    }
  }
  return false;
}


double icon_dis(int x, int y,  icon ic)
{
  return sqrt(pow(x-ic.x,2) + pow(y-ic.y,2));
}

int main()
{
  std::vector<icon> data_icon;
  std::vector<region> data_region;

  char op;
  int buf_1, buf_2, buf_3, buf_4;
  while(std::cin >> op, op != '#')
  {
    if(op == 'I')
    {
      std::cin >> buf_1 >> buf_2;
      data_icon.push_back(icon(buf_1, buf_2));
    }
    else if(op == 'R')
    {
      std::cin >> buf_1 >> buf_2 >> buf_3 >> buf_4;
      data_region.push_back(region(buf_1, buf_2, buf_3, buf_4));
    }
    else if(op == 'M')
    {
      int click_x = 0, click_y = 0;
      char region_result = '#';
      std::cin >> click_x >> click_y;

      for(int i = 0;i < data_region.size();i++)
      {
        if(In_region(click_x, click_y, data_region[i]))
          region_result = 'A' + i;
      }

      if(region_result != '#')
      {
        std::cout << region_result << std::endl;
        continue;
      }


      double min = INT_MAX;
      std::set<int> icon_set;
      for(int i = 0;i < data_icon.size();i++)
      {
        if(In_region(data_icon[i].x, data_icon[i].y, data_region))
          continue;

        if(icon_dis(click_x, click_y, data_icon[i]) < min)
        {
          min = icon_dis(click_x, click_y, data_icon[i]);
          icon_set.clear();
          icon_set.insert(i+1);
        }
        else if(icon_dis(click_x, click_y, data_icon[i]) == min)
          icon_set.insert(i+1);
      }

      for(auto it : icon_set)
        std::cout << std::setw(3) << it;
      std::cout << "\n";
    }
  }
}
