#include<iostream>
#include<string>
#include<sstream>
#include<vector>

class Robot
{
public:
  Robot()
  {
    position_x = 0;
    position_y = 0;
    direction = 'N';
  }
  void turn(std::string way)
  {
    char d[4] = {'N', 'E', 'S', 'W'};
    int j;
    for(j = 0;j < 4;j ++)
      if(d[j] == direction)
        break;
    if(way == "RIGHT")
      direction = d[(j + 1) % 4];
    else if(way == "LEFT")
      direction = d[(j - 1 + 4) % 4];
  }
  int getPositionX()
  {
    return position_x;
  }
  int getPositionY()
  {
    return position_y;
  }
  char getDirection()
  {
    return direction;
  }
  void go()
  {
    if(direction == 'N')
      position_y ++;
    else if(direction == 'E')
      position_x ++;
    else if(direction == 'S')
      position_y --;
    else
      position_x --;
  }
  void display()
  {
    std::cout<<"at("<<position_x<<", "<<position_y<<"), heading "<<direction<<std::endl;
  }
private:
  int position_x, position_y;
  char direction;
};


int main()
{
  Robot bot;
  std::string command;
  while(std::getline(std::cin, command), command != "STOP")
  {
    std::stringstream str_stream(command);
    std::vector<std::string> str_vec;
    std::string buf;
    while(str_stream >> buf)
      str_vec.push_back(buf);

    if(str_vec[0] == "GO")
    {
      for(int i = 1;i <= stoi(str_vec[1]);i++)
      {
        bot.go();
      }
    }
    else if(str_vec[0] == "TURN")
    {
      bot.turn(str_vec[1]);
    }
    else if(str_vec[0] == "TURNTO")
    {
      while(bot.getDirection() != str_vec[1][0]) //注意！！！
      {
        bot.turn("RIGHT");
      }

    }
    else if(str_vec[0] == "GOTO")
    {
      int x = stoi(str_vec[1]), y = stoi(str_vec[2]);
      char x_dir, y_dir;
      if(x >= bot.getPositionX() && y >= bot.getPositionY()) //走右上
      {
        x_dir = 'E';
        y_dir = 'N';
      }
      else if(x >= bot.getPositionX() && y <= bot.getPositionY()) //走右下
      {
        x_dir = 'E';
        y_dir = 'S';
      }
      else if(x <= bot.getPositionX() && y >= bot.getPositionY())
      {
        x_dir = 'W';
        y_dir = 'N';
      }
      else if(x <= bot.getPositionX() && y <= bot.getPositionY())
      {
        x_dir = 'W';
        y_dir = 'S';
      }
      while((bot.getDirection()) != x_dir)
        bot.turn("RIGHT");
      while(x != bot.getPositionX())
        bot.go();
      while((bot.getDirection()) != y_dir)
        bot.turn("RIGHT");
      while(y != bot.getPositionY())
        bot.go();

      while((bot.getDirection()) != 'N')
        bot.turn("RIGHT");
    }
    else if(str_vec[0] == "SHOWINFO")
      bot.display();
  }
  return 0;
}
