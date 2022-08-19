//cin 不會讀 空白字元

#include<iostream>
#include<set>
#include<cmath>
#include<cstdio>
#include<string>

class window_system;

class window_area{
public:
  friend window_system;
  window_area() = default;

private:
  int fir_x = 0, fir_y = 0;
  int sec_x = 0, sec_y = 0;
};

class window_icon{
public:
  friend window_system;
  window_icon() = default;

private:
  int x = 0, y = 0;
};

class window_system{
public:
  window_system() = default;


  void new_area(int fir_x, int fir_y, int sec_x, int sec_y);
  void new_icon(int x, int y);
  char find_area(int search_x, int search_y);
  std::set<int>* find_icon(int search_x, int search_y);

private:
  window_area area_data[25];
  window_icon icon_data[50];
  int area_count = 0, icon_count = 0;
};

void window_system::new_area(int fir_x, int fir_y, int sec_x, int sec_y)
{
  area_data[area_count].fir_x = fir_x;
  area_data[area_count].fir_y = fir_y;
  area_data[area_count].sec_x = sec_x;
  area_data[area_count].sec_y = sec_y;
  area_count += 1;
}

void window_system::new_icon(int x, int y)
{
  icon_data[icon_count].x = x;
  icon_data[icon_count].y = y;
  icon_count += 1;
}

char window_system::find_area(int search_x, int search_y)
{
  for(int i = area_count-1;i >= 0;i--) //由後往前檢測
  {
    if(area_data[i].fir_x <= search_x && area_data[i].fir_y <= search_y &&
       area_data[i].sec_x >= search_x && area_data[i].sec_y >= search_y)
       return 'A' + i;
  }
  return ' '; //fail test
}

std::set<int>* window_system::find_icon(int input_x, int input_y)
{
  double max = -1;

  std::set<int> *result = new std::set<int>;
  for(int i = 0;i < icon_count;i++)
  {
    if(find_area(icon_data[i].x, icon_data[i].y) == ' ')
    {
      double distance = (double)sqrt(pow(icon_data[i].x-input_x,2)+pow(icon_data[i].y-input_y,2));
      if(distance == max)
      {
        result->insert(i+1);
      }
      else if(max == -1 || distance < max)
      {
        result->erase(result->begin(), result->end());
        result->insert(i+1);
        max = distance;
      }
    }
  }
  return result;
}

int main(){
  //freopen("input.txt", "r", stdin);
  //freopen("output.txt", "w", stdout);

  char function;
  window_system system;
  while(std::cin >> function, function != '#')
  {
    if(function == 'I')
    {
      int x = 0, y = 0;
      std::cin >> x >> y;
      system.new_icon(x, y);
      //puts("I operation complete");
    }else if(function == 'R')
    {
      int fir_x = 0, fir_y = 0, sec_x = 0, sec_y = 0;
      std::cin >> fir_x >> fir_y >> sec_x >> sec_y;
      system.new_area(fir_x, fir_y, sec_x, sec_y);
      //puts("R operation complete");
    }else if(function == 'M')
    {
      int x = 0, y = 0;
      std::cin >> x >> y;
      if(system.find_area(x,y) != ' ')
      {
        std::cout << system.find_area(x,y) << std::endl;
      }else
      {
        for(auto it : *system.find_icon(x,y))
        {
          std::string space;
          if(it>=100)
            space = "";
          else if(it >= 10)
            space = " ";
          else
            space = "  ";

          std::cout << space << it;
        }
        std::cout << '\n';
      }
      //puts("M operation complete");
    }
  }
  return 0;
}
