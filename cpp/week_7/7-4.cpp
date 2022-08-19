/*
https://stackoverflow.com/questions/2049582/how-to-determine-if-a-point-is-in-a-2d-triangle
https://mathworld.wolfram.com/TriangleInterior.html
https://stackoverflow.com/questions/20946566/distinguish-zero-and-negative-zero
*/

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
    bool operator*(Triangle t2){
      Point a = point[0], b = point[1], c = point[2];
      Point d = t2.point[0], e = t2.point[1], f = t2.point[2];

      Point v2 = {b.x-a.x, b.y-a.y};
      Point v1 = {c.x-a.x, c.y-a.y};
      Point v0 = {a.x, a.y};
      for(int i = 1;i <= 3;i++)
      {
        Point v;
        if(i == 1)
          v = d;
        else if(i == 2)
          v = e;
        else if(i == 3)
          v = f;

        double var_a = ((double)(v.x*v2.y-v.y*v2.x)-(v0.x*v2.y-v0.y*v2.x))/(v1.x*v2.y-v1.y*v2.x);
        double var_b = -((double)(v.x*v1.y-v.y*v1.x)-(v0.x*v1.y-v0.y*v1.x))/(v1.x*v2.y-v1.y*v2.x);
        //std::cout << i << " var_a:" << var_a << '\n' << "var_b:" << var_b << '\n';

        if(var_a >= 0 && var_b >= 0 && var_a + var_b <= 1)
          return true;
      }

      v2 = {e.x-d.x, e.y-d.y};
      v1 = {f.x-d.x, f.y-d.y};
      v0 = {d.x, d.y};
      for(int i = 1;i <= 3;i++)
      {
        Point v;
        if(i == 1)
          v = a;
        else if(i == 2)
          v = b;
        else if(i == 3)
          v = c;

        double var_a = (double)((v.x*v2.y-v.y*v2.x)-(v0.x*v2.y-v0.y*v2.x))/(v1.x*v2.y-v1.y*v2.x);
        double var_b = -((double)(v.x*v1.y-v.y*v1.x)-(v0.x*v1.y-v0.y*v1.x))/(v1.x*v2.y-v1.y*v2.x);
        //std::cout << i << " var_a:" << var_a << '\n' << "var_b:" << var_b << '\n';

        if(var_a >= 0 && var_b >= 0 && var_a + var_b >= 1)
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
