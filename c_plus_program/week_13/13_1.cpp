#include<iostream>
#include<cctype>
#include<string>
#include<cstdio>

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

class Robot_enhancement : public Robot
{
public:
  void go_step(int step)//走step的步數
  {
    for(int i = 1;i <= step;i++)
    {
      go();
    }
  }

  //轉向使用已經寫好的

  void turn_to(char direction)
  {
    while(getDirection() != direction)
      turn("RIGHT");
  }

  void go_to(int x, int y)
  {
    if(x >= getPositionX() && y >= getPositionY()) //走右上
    {
      turn_to('E');
      while(x != getPositionX())
        go();
      turn_to('N');
      while(y != getPositionY())
        go();

      turn_to('N');
    }
    else if(x <= getPositionX() && y >= getPositionY()) //走左上
    {
      turn_to('W');
      while(x != getPositionX())
        go();
      turn_to('N');
      while(y != getPositionY())
        go();

      turn_to('N');
    }else if(x <= getPositionX() && y <= getPositionY()) //走左下
    {
      turn_to('W');
      while(x != getPositionX())
        go();
      turn_to('S');
      while(y != getPositionY())
        go();

      turn_to('N');
    }else if(x >= getPositionX() && y <= getPositionY()) //走右下
    {
      turn_to('E');
      while(x != getPositionX())
        go();
      turn_to('S');
      while(y != getPositionY())
        go();

      turn_to('N');
    }
  }

  //顯示資訊使用已經寫好的
};

int main()
{
  //freopen("input.txt", "r", stdin);
  //freopen("output.txt", "w", stdout);

  Robot_enhancement item;
  std::string command;
  while(std::getline(std::cin, command), command != "STOP")
  {
    if(command[0] == 'G' && command[1] == 'O' && command[2] != 'T')
    {
      auto num_begin = command.begin(), num_end = command.begin();
      while(!isdigit(*num_begin)) //找數字的前方
        num_begin++;
      num_end = num_begin;
      while(isdigit(*num_end)) //找數字的後方
        num_end++;

      std::string number = command.substr(num_begin-command.begin(), num_end-num_begin);
      int convert_number = stoi(number);
      //std::cout << convert_number << std::endl;
      item.go_step(convert_number);
    }
    else if(command[0] == 'T' && command[1] == 'U' && command[2] == 'R' && command[3] == 'N' && command[4] != 'T')
    {
      auto way_begin = command.begin(), way_end = command.end();
      while(*way_begin != ' ') //找方向的前方（空白符號）
        way_begin++;
      way_begin++; //讓他指到方向的第一個字元

      std::string way = command.substr(way_begin-command.begin(), way_end-way_begin);
      item.turn(way);
    }
    else if(command[0] == 'T' && command[1] == 'U' && command[2] == 'R' && command[3] == 'N' && command[4] == 'T' && command[5] == 'O')
    {
      auto dir_begin = command.begin(), dir_end = command.end();
      while(*dir_begin != ' ') //找方向的前方（左括號）
        dir_begin++;
      dir_begin++; //讓他指到方向的第一個字元

      std::string dir = command.substr(dir_begin-command.begin(), dir_end-dir_begin);
      item.turn_to(dir[0]);
    }
    else if(command[0] == 'G' && command[1] == 'O' && command[2] == 'T' && command[3] == 'O')
    {
      auto x_begin = command.begin(), x_end = command.begin();
      auto y_begin = command.end()-1, y_end = command.end();
      while(*x_begin != ' ') //找x的前方（空白符號）
        x_begin++;
      x_begin++; //讓他指到x的第一個字元

      x_end = x_begin;

      while(*x_end != ' ') //找x的後方（空白符號）
        *x_end++;

      while(*y_begin != ' ') //找y的前方（空白括號）
        y_begin--;
      y_begin++;

      std::string x = command.substr(x_begin-command.begin(), x_end - x_begin);
      std::string y = command.substr(y_begin-command.begin(), y_end - y_begin);
      int convert_x = stoi(x), convert_y = stoi(y);

      item.go_to(convert_x, convert_y);
    }
    else if(command == "SHOWINFO")
      item.display();
  }

  return 0;
}
