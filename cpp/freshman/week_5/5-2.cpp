#include<iostream>

class go{
public:
  void input_data();
  void check();
  void recur_check(int, int);
  void print();
private:
  char board[9][9], surround_char=' ';
  bool surround = true;
  int white = 0, black = 0;
  int surround_count = 1;
};

void go::input_data(){
  for(int i = 0;i < 9;i++)
  {
    for(int j = 0;j < 9;j++)
    {
      std::cin >> board[i][j];
    }
  }
}

void go::print(){
  std::cout  << "Black " << black << " White " << white << '\n';
}

void go::check(){
  for(int i = 0;i < 9;i++)
  {
    for(int j = 0;j < 9;j++)
    {
      if(board[i][j] == 'O') //該格為白子
        white++;
      else if(board[i][j] == 'X') //該格為黑子
        black++;
      else if(board[i][j] == 'C') //該格檢查過了（C為檢查的符號）
        continue;
      else //該格為空
      {
        board[i][j] = 'C'; //把該格設為檢查過
        if(i-1 >= 0) //判定邊界（是否超過上棋盤）
          recur_check(i-1, j);
        if(i+1 < 9) //判定邊界（是否超過下棋盤）
          recur_check(i+1, j);
        if(j-1 >= 0) //判定邊界（是否超過左棋盤）
          recur_check(i, j-1);
        if(j+1 < 9) //判定邊界（是否超過右棋盤）
          recur_check(i, j+1);

        if(surround) //全部相連的空白格都偵測完，且遇到的棋子邊界都相同（包圍）
        {
          if(surround_char == 'X') //包圍的棋子為黑子
            black += surround_count;
          else if(surround_char == 'O') //包圍的棋子為白子
            white += surround_count;
        }

        surround = true; //重置包圍bool
        surround_char = ' '; //重置包圍棋子
        surround_count = 1; //重置空白數目

      }
    }
  }
}

void go::recur_check(int row, int col){

  if(board[row][col] == 'C') //檢查過就不用再檢查了
    return;
  else if(board[row][col] == 'O' || board[row][col] == 'X') //碰到棋子邊界
  {
    //以初始化過棋子邊界的棋，且目前與之前初始化的不相同（沒有包圍）
    if(surround_char != ' ' && surround_char != board[row][col])
      surround = false;
    else
      surround_char = board[row][col]; //第一次初始化棋子邊界的棋

    return;
  }
  board[row][col] = 'C'; //目前的空白設定為已檢查
  surround_count += 1; //空白數目加一

  if(row-1 >= 0)
    recur_check(row-1, col);
  if(row+1 < 9)
    recur_check(row+1, col);
  if(col-1 >= 0)
    recur_check(row, col-1);
  if(col+1 < 9)
    recur_check(row, col+1);
}

int main(){
  int input_go = 0; //多少個棋盤
  std::cin >> input_go;
  for(int i = 1;i <= input_go;i++)
  {
    go a; //創建棋盤
    a.input_data(); //輸入資料
    a.check(); //檢查棋盤
    a.print(); //印出結果
  }
}
