#include <iostream>
#include <vector>

#define For(i, a, b) for(int i = a;i <=b ;i++)

void Process(int cur, bool (&two)[2][100][100])
{
  int input_case = 0;
  std::cin >> input_case;
  for(int i = 0;i < input_case;i++)
  {
    char buf1, buf2;
    std::cin >> buf1 >> buf2;
    //來回皆可
    two[cur][buf1][buf2] = two[cur][buf2][buf1] = true;
  }
  //找尋中間的可能性
  For(t, 'A', 'Z')
    For(u, 'A', 'Z')
      For(v, 'A', 'Z')
        two[cur][u][v] = two[cur][u][v] || two[cur][u][t] && two[cur][t][v];
}

bool Check(bool (&two)[2][100][100])
{
  For(i, 'A', 'Z')
    For(j, 'A', 'Z')
      if(two[0][i][j] != two[1][i][j])
        return false;

  return true;
}

int main()
{
  int test_case = 0;
  std::cin >> test_case;

  for(int i = 1;i <= test_case;i++)
  {
    bool two[2][100][100];

    For(j, 'A', 'Z')
      For(k, 'A', 'Z')
        two[0][j][k] = two[1][j][k] = false;

    Process(0, two);
    Process(1, two);
    Check(two) ? std::cout << "YES\n" : std::cout << "NO\n";

      std::cout << "\n";
  }
}
