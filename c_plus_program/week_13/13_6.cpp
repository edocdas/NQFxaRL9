#include<iostream>

int main()
{
  int number_count = 0, game_counter = 0;
  while(std::cin >> number_count, number_count != 0)
  {
    std::cin >> std::ws; //把 '\n' 吸掉
    game_counter++;
    std::string input, result = "Game " + std::to_string(game_counter) + ":\n";
    char answer[number_count+1];
    std::getline(std::cin, input); //讀入 答案
    for(int i = 0;i < number_count;i++)
    {
      answer[i] = input[i*2];
    }

    while(std::getline(std::cin, input), input[0] != '0')
    {
      char ch_input[number_count+1], answer_buf[number_count+1];
      for(int i = 0;i < number_count;i++)
      {
        ch_input[i] = input[i*2];
        answer_buf[i] = answer[i];
      }


      int a = 0, b = 0;
      for(int i = 0;i < number_count;i++)
      {
        if(answer_buf[i] == ch_input[i])
        {
            a++;
            answer_buf[i] = 's';
            ch_input[i] = 's';
        }
      }

      for(int i = 0;i < number_count;i++)
      {
        for(int j = 0;j < number_count;j++)
        {
            if(answer_buf[i] != 's' && answer_buf[i] == ch_input[j])
            {
                b++;
                answer_buf[i] = 's';
                ch_input[j] = 's';
            }
        }
      }
      //std::cout << "a" << a << " b" << b << std::endl;
      result += "(" + std::to_string(a) + "," + std::to_string(b) + ")\n";
    }
    std::cout << result;
  }
}
