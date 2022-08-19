#include<iostream>
#include<cstdio>

struct segment{
  int split = 1;
  double a_x = 0, a_y = 0;
  double b_x = 0, b_y = 0;
};

int main(){
  //freopen("input.txt","r", stdin);
  //freopen("output.txt","w", stdout);

  int test_case = 0, input_line = 0;
  std::cin >> test_case;
  for(int i = 0;i < test_case;i++)
  {
    std::cin >> input_line;
    struct segment data[input_line];
    for(int j = 0;j < input_line;j++)
    {
      double a_x = 0, a_y = 0, b_x = 0, b_y = 0;
      std::cin >> a_x >> a_y >> b_x >> b_y;
      data[j].a_x = a_x;
      data[j].a_y = a_y;
      data[j].b_x = b_x;
      data[j].b_y = b_y;
    }
    for(int a = 0;a < input_line;a++)
    {
      for(int b = a+1;b < input_line;b++)
      {
        double x1 = data[a].a_x, y1 = data[a].a_y, x2 = data[a].b_x, y2 = data[a].b_y;
        double x3 = data[b].a_x, y3 = data[b].a_y, x4 = data[b].b_x, y4 = data[b].b_y;
        double t = ((x1-x3)*(y3-y4)-(y1-y3)*(x3-x4))/((x1-x2)*(y3-y4)-(y1-y2)*(x3-x4));
      	double u = ((x1-x3)*(y1-y2)-(y1-y3)*(x1-x2))/((x1-x2)*(y3-y4)-(y1-y2)*(x3-x4));
      	if(t >= 0 && t <= 1 && u >= 0 && u <= 1)
      	{
          data[a].split += 1;
          data[b].split += 1;
      	}
      }
    }
    int sum = 0;
    for(int k = 0;k < input_line;k++)
    {
      sum += data[k].split;
    }

    //if(i+1 != test_case)
      std::cout << sum << "\n\n";
    //else
      //std::cout << sum << '\n';
  }
}
