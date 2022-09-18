#include<iostream>
class Point
{
public:
    Point()
    {
        x = 0;
        y = 0;
    }
    Point(double _x, double _y)
    {
        x = _x;
        y = _y;
    }
    double x, y;
};

class Triangle
{
public:
    Triangle(Point a, Point b, Point c)
    {
        point[0] = a;
        point[1] = b;
        point[2] = c;
    }
    //override operator* with one parameter which is also a object of Triangle and return true if two triangle collision, return false if not.
    //Two triangle collision if they overlap or share the same point or segment.
    //多載 *號，如果兩個三角形有碰撞的話就回傳 true ，否則就回傳 dalse。
    //如果兩個三角形有重疊或是共用某個線段或是點的話就是兩個三角形有碰撞。
    bool operator *(Triangle b)
    {
      for(int i = 0;i <= 2;i++)
      {
        double v0x = b.point[0].x, v0y = b.point[0].y;
        double v1x = b.point[1].x, v1y = b.point[1].y;
        double v2x = b.point[2].x, v2y = b.point[2].y;

        double vx = point[i].x , vy = point[i].y;

        double r = ((vx*v2y-vy*v2x)-(v0x*v2y-v0y*v2x))/(v1x*v2y-v2x*v1y);
        double s = ((vx*v1y-vy*v1x)-(v0x*v1y-v0y*v1x))/-(v1x*v2y-v2x*v1y);

        if(r >= 0 && s >= 0 && r + s <= 1)
          return true;
      }

      for(int i = 0;i <= 2;i++)
      {
        double v0x = point[0].x, v0y = point[0].y;
        double v1x = point[1].x, v1y = point[1].y;
        double v2x = point[2].x, v2y = point[2].y;

        double vx = b.point[i].x , vy = b.point[i].y;

        double r = ((vx*v2y-vy*v2x)-(v0x*v2y-v0y*v2x))/(v1x*v2y-v2x*v1y);
        double s = ((vx*v1y-vy*v1x)-(v0x*v1y-v0y*v1x))/-(v1x*v2y-v2x*v1y);

        if(r >= 0 && s >= 0 && r + s <= 1)
          return true;
      }
      return false;
    }
private:
    Point point[3];
};

int main()
{
    double x1, y1, x2, y2, x3, y3;
    std::cin>>x1>>y1>>x2>>y2>>x3>>y3;
    Point a(x1, y1), b(x2, y2), c(x3, y3);
    std::cin>>x1>>y1>>x2>>y2>>x3>>y3;
    Point a2(x1, y1), b2(x2, y2), c2(x3, y3);
    Triangle t1(a, b, c), t2(a2, b2, c2);
    std::cout<<t1 * t2<<std::endl;
}
