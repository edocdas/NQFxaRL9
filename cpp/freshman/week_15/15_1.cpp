#include<cmath>
#include<iostream>

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

private:
  double x, y;
};
class Segment : public Point
{
public:
  Segment(): a(), b(){}
  Segment(Point c, Point d): a(c), b(d){}
  double getLength()
  {
    return a.getDistance(b);
  }
private:
  Point a, b;
};

int main()
{}
