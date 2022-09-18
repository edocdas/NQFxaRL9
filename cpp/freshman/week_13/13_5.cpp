#include<iostream>

int main()
{
  int king = 0, queen = 0, move = 0;
  while(std::cin >> king >> queen >> move)
  {
    //king 等於 queen
    if(king == queen)
    {
      std::cout << "Illegal state\n";
      continue;
    }

    const int queen_i = queen / 8, queen_j = queen % 8;
    const int king_i = king / 8, king_j = king % 8;
    bool legal = false;

    //以下有幾種情況使移動不成立
    //移動到king，移動到queen(沒移動)
    //非直線移動，或移動過程中穿透了king

    //橫著移動
    for(int j_iter = 0;j_iter < 8;j_iter++)
      if(queen_i * 8 + j_iter == move && move != king && move != queen)
        if(!(king_i == queen_i && ((move < king && king < queen) || (move > king && king > queen))))
          legal = true;

    //直著移動
    for(int i_iter = 0;i_iter < 8;i_iter++)
      if(i_iter * 8 + queen_j == move && move != king && move != queen)
        if(!(king_j == queen_j && ((move < king && king < queen) || (move > king && king > queen))))
          legal = true;

    if(!legal)
    {
      std::cout << "Illegal move\n";
      continue;
    }


    //只要走到king的任意旁邊四格，就會not allowed(代表自己送死)
    bool move_allowed = true;
    if(king_i + 1 < 8 && (king_i+1)*8 + king_j == move)
      move_allowed = false;
    if(king_i - 1 >= 0 && (king_i-1)*8 + king_j == move)
      move_allowed = false;
    if(king_j + 1 < 8 && (king_i)*8 + king_j+1 == move)
      move_allowed = false;
    if(king_j - 1 >= 0 && (king_i)*8 + king_j-1 == move)
      move_allowed = false;

    if(!move_allowed)
    {
      std::cout << "Move not allowed\n";
      continue;
    }

    //列出有可能死棋的四種可能
    if(king == 56 && move == 49 || king == 0 && move == 9
      || king == 7 && move == 14 || king == 63 && move == 54)
    {
      std::cout << "Stop\n";
      continue;
    }

    std::cout << "Continue\n";
  }
}
