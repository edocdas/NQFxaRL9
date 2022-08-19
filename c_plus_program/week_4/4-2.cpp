#include <iostream>
#include <string>
#include <set>
#include <cstdio>

int main(){

	//freopen("input.txt","r", stdin);
	//freopen("output.txt","w", stdout);
	int counter = 0, max = 0;
	std::string input;
	std::set<char> char_list;

	std::getline(std::cin, input); //read a line
	if(input.size() == 0) //if string is empty
	{
		std::cout << 0 << '\n';
		return 0;
	}

	for(int j = 0; j < input.size(); j++)
  {
		for(int i = j; i < input.size(); i++)
		{
			if(char_list.find(input[i]) == char_list.end()) //if set don't have that char
			{
				//std::cout << "Not found:" << input[i] << '\n';
				char_list.insert(input[i]); //put that char in set
				counter++;

				if(i+1 == input.size() && counter > max) //substring reach the end and counter bigger than max
					max = counter;
			}
			else //set have that char
			{
				//std::cout << "counter:" << counter << '\n';
				//std::cout << "max:" << max << '\n';
				if(counter > max)
					max = counter;
				char_list.clear(); //delete set
				counter = 0; //reset counter
				break; //to the outer for loop
			}
		}
	}
	std::cout << max << '\n';
	return 0;
}
