#include<string>
#include<sstream>
#include<iostream>

class Point
{
public:
int x, y;
};

class Convert
{
public:
  static std::string toString(int n)
  {
    std::ostringstream output;
    output << n;
    return output.str();
  }
  static std::string toString(char c)
  {
    std::ostringstream output;
    output << c;
    return output.str();
  }
  static std::string toString(double d)
  {
    std::ostringstream output;
    output << d;
    return output.str();
  }
  static std::string toString(Point p)
  {
    std::ostringstream output;
    output << "(" << p.x << ", " << p.y << ")";
    return output.str();
  }
};

int main()
{
  Convert a;
  Point b;
  b.x = 1;
  b.y = 2;
  std::cout << a.toString(b);
}
