#include<iostream>
#include<cmath>

class Point
{
public:

  Point():x(0),y(0){}
  Point(double a, double b):x(a),y(b){}
  Point(Point &c):x(c.x), y(c.y){}
  void printPoint(){std::cout << "(" << x << ", " << y << ")";}
  double getX() {return x;}
  double getY() {return y;}
  void setX(double a) {x = a;}
  void setY(double a) {y = a;}
  double getDistance(Point input){return sqrt(pow(input.x-x,2)+pow(input.y-y,2));}
  bool operator==(Point b)
  {
    return this->x == b.x && this->y == b.y;
  }

private:
  double x, y;
};
class Segment : public Point
{
public:
  friend class Shape;
  Segment(): a(), b(){}
  Segment(Point c, Point d): a(c), b(d){}
  Point getPointA(){return a;}
  Point getPointB(){return b;}
  double getLength()
  {
    return a.getDistance(b);
  }
private:
  Point a, b;
};

class Shape : public Segment
{
public:
  Shape():Segment(){}
  Shape(Segment *input_seg, int input_count):edgeCount(input_count)
  {
    Point first_seg_a = input_seg[0].a, first_seg_b = input_seg[0].b;
    Point last_seg_a = input_seg[input_count-1].a, last_seg_b = input_seg[input_count-1].b;

    if(first_seg_a == last_seg_a || first_seg_a == last_seg_b
      || first_seg_b == last_seg_a || first_seg_b == last_seg_b)
    {
      for(int i = 0;i < input_count;i++)
      {
        seg[i] = input_seg[i];
      }
      edgeCount = input_count;
    }else
    {
        throw std::invalid_argument("Invalid syntax.");
    }
  } // to construct a shape with a serial of segment. Throw an invalid_argument if the segment can not construct a close path.
  virtual float getArea() = 0;
  float getPerimeter()
  {
    double sum = 0;
    for(int i = 0;i < edgeCount;i++)
    {
      sum += seg[i].getLength();
    }

    return sum;
  }

  Segment &getSeg(int index)
  {
  	return seg[index];
  }
private:
  Segment seg[10];
  int edgeCount;
};


class Circle : public Shape
{
public:
  Circle (float r):diameter(r){}
  float getArea(){return pi*diameter*diameter;}
  float getPerimeter(){return 2*pi*diameter;}
private:
  double diameter;
  double pi = 3.141592;
};

int main()
{
  Circle a(5);
  std::cout << a.getArea() << std::endl;
  std::cout << a.getPerimeter() << std::endl;

}
