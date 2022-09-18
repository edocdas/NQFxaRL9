/*
(6)
4
A.DD .A.. DD.A ..D. B... E...
B.A. BA.. .A.B ..AB A.DD ....
E... ...E ...E E... .... A.AD
.... .... .... .... E... B...

(11)
5
.A..E E.A.. E..E. ..E.E .EBB. ...D.
..B.. B.... ..B.. ....B ..... EA...
.B... ..B.. ...B. ..B.. .A..E .B..D
.A.B. B..A. .B.A. .A..B EA... .....
E.BDD B.DED DDB.E DED.B ...D. .EBB.

(20)
6
E..DAB B.DE.. BAD..E ..AD.B .AB..B ..E..B
...B.B .A.B.B A.B... B.B.A. .CE..A ..D.E.
..BCE. B.C.E. .ECB.. .E.C.B .D.D.. EC.BA.
..E... .E.... ...E.. ....E. EC.DA. .D.C..
.D.... .CD... ....C. ...DC. ..D.E. .AE..D
.CE..D AA.CDE D..DA. EDC.DA ..E..B .AB..B

1.先把不存在的方塊清掉
2.嘗試把每面塗色，如果搭配不對，就把該塊清除，繼續檢查，直到碰到結尾
*/

#include<iostream>
#include<cstring>
#include<cstdio>

int main()
{
  //freopen("input.txt","r", stdin);
  //freopen("output.txt","w", stdout);

  int cube_size = 0;
  while(std::cin >> cube_size, cube_size != 0)
  {
    int cube[cube_size][cube_size][cube_size]; //總和的方塊
    char test_char[cube_size][cube_size][cube_size]; //塗色的情形
    char input_cube[6][cube_size][cube_size]; //輸入的資料
    memset(cube, -1, sizeof(cube));
    memset(test_char, 0, sizeof(test_char));

    int row_index = 0, plane_index = 0;
    for(int i = 1;i <= cube_size*cube_size*6;i++) //輸入
    {
      char input;
      std::cin >> input;
      input_cube[plane_index%6][row_index][(i-1)%cube_size] = input;

      if(i % cube_size == 0) //換到下一個面
        plane_index++;
      if(i % (cube_size*6) == 0) //換到下一列
        row_index++;
    }


    //首先，執行穿透測試
    for(int plane = 0;plane < 6;plane++)
    {
      for(int row = 0;row < cube_size;row++)
      {
        for(int col = 0;col < cube_size;col++)
        {
          if(input_cube[plane][row][col] == '.')
          {
            switch(plane)
            {
              case 0: //前面
              {
                for(int iter = 0;iter < cube_size;iter++)
                {
                  cube[iter][row][col] = 0;
                }
                break;
              }
              case 1: //左面
              {
                for(int iter = 0;iter < cube_size;iter++)
                {
                  cube[(cube_size-1)-col][row][iter] = 0;
                }
                break;
              }
              case 2: //後面
              {
                for(int iter = 0;iter < cube_size;iter++)
                {
                  cube[iter][row][(cube_size-1)-col] = 0;
                }
                break;
              }
              case 3: //右面
              {
                for(int iter = 0;iter < cube_size;iter++)
                {
                  cube[col][row][iter] = 0;
                }
                break;
              }
              case 4: //上面
              {
                for(int iter = 0;iter < cube_size;iter++)
                {
                  cube[(cube_size-1)-row][iter][col] = 0;
                }
                break;
              }
              case 5: //下面
              {
                for(int iter = 0;iter < cube_size;iter++)
                {
                  cube[row][iter][col] = 0;
                }
                break;
              }
            }
          }
        }
      }
    }

    //接著是顏色測試
    bool not_done = true;
    while(not_done)
    {
      not_done = false;
      for(int plane = 0;plane < 6;plane++)
      {
        for(int row = 0;row < cube_size;row++)
        {
          for(int col = 0;col < cube_size;col++)
          {
            if(input_cube[plane][row][col] != '.')
            {
              switch(plane)
              {
                case 0: //前面
                {
                  for(int iter = 0;iter < cube_size;iter++)
                  {
                    if(cube[iter][row][col] == 0) //該格不存在
                      continue;

                    //沒塗色or已塗色且相同
                    if(test_char[iter][row][col] == 0 ||
                      test_char[iter][row][col] == input_cube[plane][row][col])
                    {
                      //沒塗色
                      if(test_char[iter][row][col] == 0)
                        not_done = true;

                      test_char[iter][row][col] = input_cube[plane][row][col];
                      break;
                    }
                    else
                    {
                      test_char[iter][row][col] = '!';
                      cube[iter][row][col] = 0;
                      not_done = true;
                    }
                  }


                  break;
                }
                case 1: //左面
                {
                  for(int iter = 0;iter < cube_size;iter++)
                  {
                    if(cube[(cube_size-1)-col][row][iter] == 0) //該格不存在
                      continue;


                    if(test_char[(cube_size-1)-col][row][iter] == 0 ||
                      test_char[(cube_size-1)-col][row][iter] == input_cube[plane][row][col])
                    {

                      if(test_char[(cube_size-1)-col][row][iter] == 0)
                        not_done = true;

                      test_char[(cube_size-1)-col][row][iter] = input_cube[plane][row][col];
                      break;
                    }
                    else
                    {
                      test_char[(cube_size-1)-col][row][iter] = '!';
                      cube[(cube_size-1)-col][row][iter] = 0;
                      not_done = true;
                    }
                  }


                  break;
                }
                case 2: //後面
                {
                  for(int iter = cube_size-1;iter >= 0;iter--)
                  {
                    if(cube[iter][row][(cube_size-1)-col] == 0) //該格不存在
                      continue;

                    if(test_char[iter][row][(cube_size-1)-col] == 0 ||
                      test_char[iter][row][(cube_size-1)-col] == input_cube[plane][row][col])
                    {
                      if(test_char[iter][row][(cube_size-1)-col] == 0)
                        not_done = true;

                      test_char[iter][row][(cube_size-1)-col] = input_cube[plane][row][col];
                      break;
                    }
                    else
                    {
                      test_char[iter][row][(cube_size-1)-col] = '!';
                      cube[iter][row][(cube_size-1)-col] = 0;
                      not_done = true;
                    }
                  }

                  break;
                }
                case 3: //右面
                {
                  for(int iter = cube_size-1;iter >= 0;iter--)
                  {
                    if(cube[col][row][iter] == 0) //該格不存在
                      continue;

                    if(test_char[col][row][iter] == 0 ||
                      test_char[col][row][iter] == input_cube[plane][row][col])
                    {
                      if(test_char[col][row][iter] == 0)
                        not_done = true;

                      test_char[col][row][iter] = input_cube[plane][row][col];
                      break;
                    }
                    else
                    {
                      test_char[col][row][iter] = '!';
                      cube[col][row][iter] = 0;
                      not_done = true;
                    }
                  }


                  break;
                }
                case 4: //上面
                {
                  for(int iter = 0;iter < cube_size;iter++)
                  {
                    if(cube[(cube_size-1)-row][iter][col] == 0) //該格不存在
                      continue;

                    if(test_char[(cube_size-1)-row][iter][col] == 0 ||
                      test_char[(cube_size-1)-row][iter][col] == input_cube[plane][row][col])
                    {
                      if(test_char[(cube_size-1)-row][iter][col] == 0)
                        not_done = true;

                      test_char[(cube_size-1)-row][iter][col] = input_cube[plane][row][col];
                      break;
                    }
                    else
                    {
                      test_char[(cube_size-1)-row][iter][col] = '!';
                      cube[(cube_size-1)-row][iter][col] = 0;
                      not_done = true;
                    }
                  }


                  break;
                }
                case 5: //下面
                {
                  for(int iter = cube_size-1;iter >= 0;iter--)
                  {
                    if(cube[row][iter][col] == 0) //該格不存在
                      continue;

                    if(test_char[row][iter][col] == 0 ||
                      test_char[row][iter][col] == input_cube[plane][row][col])
                    {
                      if(test_char[row][iter][col] == 0)
                        not_done = true;

                      test_char[row][iter][col] = input_cube[plane][row][col];
                      break;
                    }
                    else
                    {
                      test_char[row][iter][col] = '!';
                      cube[row][iter][col] = 0;
                      not_done = true;
                    }
                  }

                  /*for(int z = 0;z < cube_size;z++)
                  {
                    for(int y = 0;y < cube_size;y++)
                    {
                      for(int x = 0;x < cube_size;x++)
                      {
                        std::cout << z << y << x << ":"<<test_char[z][y][x] << "\n";
                      }
                    }
                  }
                  std::cout << "\n";*/
                  break;
                }
              }
            }
          }
        }
      }
    }

    int sum = 0;
    //結算
    for(int z = 0;z < cube_size;z++)
    {
      for(int y = 0;y < cube_size;y++)
      {
        for(int x = 0;x < cube_size;x++)
        {
          //std::cout << z << y << x << ":"<<test_char[z][y][x] << "\n";
          if(cube[z][y][x] == -1)
            sum++;
        }
      }
    }
    std::cout << "Maximum weight: "<< sum <<" gram(s)\n";
  }
}
