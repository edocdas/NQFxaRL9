#include<iostream>
#include<thread>
#include<mutex>

std::mutex g_mutex;

void time_killer(int &counter)
{
  std::lock_guard<std::mutex> lock(g_mutex);
  for(int i = 0;i < 4e8;i++)
    counter += 1;
  std::cout << "in time_killer counter:" << counter << std::endl;
}

int main()
{
  int a = 0;
  std::thread n1_thread(time_killer, std::ref(a)); 
  std::thread n2_thread(time_killer, std::ref(a));

  std::cout << "Thread start" << std::endl;
  n1_thread.join();
  std::cout << "Counter:" << a << std::endl;
  n2_thread.join();
  std::cout << "Counter:" << a << std::endl;
}