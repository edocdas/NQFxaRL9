//記住公式，應該會有上一題的說明，使用那些函式
Segment(Coordinate _a, Coordinate _b)
{
  a.setX(_a.getX());
  a.setY(_a.getY());
  b.setX(_b.getX());
  b.setY(_b.getY());
}
Coordinate *getIntersection(Segment s) // 計算與另一條線的交點，如果只有一個交點就回傳該交點，其他狀況則回傳NULL
{
  double x1 = a.getX(), y1 = a.getY(), x2 = b.getX(), y2 = b.getY();
  double x3 = s.a.getX(), y3 = s.a.getY(), x4 = s.b.getX(), y4 = s.b.getY();

  double t = ((x1-x3)*(y3-y4)-(y1-y3)*(x3-x4))/((x1-x2)*(y3-y4)-(y1-y2)*(x3-x4));
  double r = ((x1-x3)*(y1-y2)-(y1-y3)*(x1-x2))/((x1-x2)*(y3-y4)-(y1-y2)*(x3-x4));

  if(t>= 0 && t <= 1 && r >= 0 && r <= 1)
  {
    Coordinate*ptr = new Coordinate;
    ptr->setX(x1+t*(x2-x1));
    ptr->setY(y1+t*(y2-y1));
    return ptr;
  }
  else
    return nullptr;

}
float length()
{
  double f_x = a.getX(), f_y = a.getY(), s_x = b.getX(), s_y = b.getY();
  return sqrt(pow(f_x-s_x,2) + pow(f_y-s_y,2));
}
