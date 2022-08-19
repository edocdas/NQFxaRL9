#include<iostream>

int n = 0;
//pos打錯了
int view[6][10][10], pos[10][10][10];

#define REP(i,n) for(int i = 0;i < n;i++)

char Getchar()
{
  while(true)
  {
    char ch;
    std::cin >> ch;
    if(ch >= 'A' && ch <= 'Z' || ch == '.')
      return ch;
  }
}

void search(int i, int j, int k, int p, int &x, int &y, int &z)
{
  switch(k)
  {
    case 0: x = i, y = j, z = p; return;
    case 1: x = i, y = p, z = n-j-1; return;
    case 2: x = i, y = n-j-1, z = n-p-1; return;
    case 3: x = i, y = n-p-1, z = j; return;
    case 4: x = p, y = j, z = n-i-1; return;
    //case 5 的x記錯了
    case 5: x = n-p-1, y = j, z = i; return;
  }
}

int solve()
{
  int x = 0, y = 0, z = 0;

  REP(k,6) REP(i,n) REP(j,n)
    if(view[k][i][j] == '.')
    {
      REP(p,n)
      {
        search(i,j,k,p,x,y,z);
        pos[x][y][z] = '.';
      }
    }

  while(true)
  {
    bool done = true;
    REP(k,6) REP(i,n) REP(j,n)
      if(view[k][i][j] != '.')
      {
        REP(p,n)
        {
          search(i,j,k,p,x,y,z);
          if(pos[x][y][z] == '.') continue;
          if(pos[x][y][z] == '#')
            pos[x][y][z] = view[k][i][j];

          if(pos[x][y][z] == view[k][i][j]) break;
          pos[x][y][z] = '.';
          done = false;
        }
      }

    if(done)
      break;
  }

  int result = 0;
  REP(x,n) REP(y,n) REP(z,n)
    if(pos[x][y][z] != '.')
      result++;
  return result;
}

int main()
{
  while(std::cin >> n, n != 0)
  {
    REP(i,n) REP(k,6) REP(j,n) view[k][i][j] = Getchar();
    REP(x,n) REP(y,n) REP(z,n) pos[x][y][z] = '#';

    std::cout << "Maximum weight: " << solve() << " gram(s)\n";
  }
}
