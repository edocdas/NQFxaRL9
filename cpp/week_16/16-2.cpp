#include<iostream>

template <typename T>
class point
{
public:
  point():x(0), y(0){}
  //point(const point &input):x(input.x), y(input.y){}
  point(T input_x, T input_y):x(input_x), y(input_y){}

  friend std::ostream& operator <<(std::ostream &output, const point &data)
  {
    output << data.x << " " << data.y << std::endl;
    return output;
  }

  point operator +(const point& b)
  {
    return point(b.x+x, b.y+y);
  }
private:
  T x, y;
};

/*
template <typename T>
 std::ostream& operator <<(std::ostream &output, const point<T> &data)
{
  output << data.x << " " << data.y << std::endl;
  return output;
}*/

int main()
{
  double a = 1.11, b = 2;
  point<double> c(a,b), d(1,2.22);
  point<double> e = c+d;
  std::cout << c+d;
}
