#include<iostream>
#include<fstream>
#include<ctime>
#include<thread>

void random_operation(int times)
{
  std::string filename = "in" + std::to_string(times) + ".txt";
  std::fstream file(filename, std::ios::out);
  srand(time(NULL));
  int row = 500, col = 500;
  file << row << "\n" << col << "\n";
  for(int i = 0;i < row;i++)
  {
    for(int j = 0;j < col;j++)
    {
      file << rand() << "\n";
    }
  }
  file.close();
}

int main()
{
  int count = 1000;
  std::thread thread_arr[count];
  for(int times = 1;times <= count;times++)
  {
    std::cout << times << "\n";
    thread_arr[times-1] = std::thread(random_operation, times);
  }

  for(int i = 0;i < count;i++)
  {
    std::cout << i+1 << "join\n";
    thread_arr[i].join();
  }
  std::cout << "Random complete\n";
}