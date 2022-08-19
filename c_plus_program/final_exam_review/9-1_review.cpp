#include<iostream>

struct line
{
  int a_x, a_y;
  int b_x, b_y;
  int split = 1;
};

int main()
{
  int test_case = 0, test_line = 0;
  std::cin >> test_case;
  for(int a = 1;a <= test_case;a++)
  {
    std::cin >> test_line;
    struct line data[test_line];
    for(int j = 0;j < test_line;j++)
    {
      std::cin >> data[j].a_x >> data[j].a_y >> data[j].b_x >> data[j].b_y;
    }

    for(int i = 0;i < test_line;i++)
    {
      for(int j = i+1;j < test_line;j++)
      {
        int x1 = data[i].a_x, y1 = data[i].a_y, x2 = data[i].b_x, y2 = data[i].b_y;
        int x3 = data[j].a_x, y3 = data[j].a_y, x4 = data[j].b_x, y4 = data[j].b_y;

        double t = (double)((x1-x3)*(y3-y4)-(y1-y3)*(x3-x4)) / ((x1-x2)*(y3-y4)-(y1-y2)*(x3-x4));
        double u = (double)((x1-x3)*(y1-y2)-(y1-y3)*(x1-x2)) / ((x1-x2)*(y3-y4)-(y1-y2)*(x3-x4));
        if(0 <= t && t <= 1 && 0 <= u && u <= 1)
        {
          data[i].split++;
          data[j].split++;
        }
      }
    }

    int sum = 0;
    for(int j = 0;j < test_line;j++)
      sum += data[j].split;

    std::cout << sum << "\n\n";
  }
}
