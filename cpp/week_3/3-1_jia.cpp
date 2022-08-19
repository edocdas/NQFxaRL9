#include <iostream>
#include <string>
#include <map>

struct Child{
	std::string parent_a;
	std::string parent_b;
	std::string child_name;
};

int main(){
	std::map<std::string, std::string> Person;
	Child child_data[3100];
	int child_count = 0, data_line = 0;
	std::cin >> data_line >> std::ws;
	for(int i = 0;i < data_line;i++)
	{
		std::string left, right;
		std::cin >> left >> right;

		if(right == "dominant" || right == "recessive" || right == "non-existent")
		{
			Person.insert(std::make_pair(left, right));
		}
		else
		{
			for(int j = 0;j <= child_count;j++)
			{
				if(j == child_count)
				{
					child_data[j].parent_a = left;
					child_data[j].child_name = right;
					child_count += 1;
					break;
				}
				else if(right == child_data[j].child_name)
				{
					child_data[j].parent_b = left;
					break;
				}
			}
		}
	}

	for(int i = 0;i < child_count;i++)
	{
		std::string gene_a = Person[child_data[i].parent_a];
		std::string gene_b = Person[child_data[i].parent_b];
		std::string child_gene;

		if((gene_a == "dominant" && gene_b == "dominant") ||
		(gene_a == "dominant" && gene_b == "recessive") ||
		(gene_a == "recessive" && gene_b == "dominant"))
			child_gene = "dominant";
		else if((gene_a == "non-existent" && gene_b == "non-existent") ||
			(gene_a == "non-existent" && gene_b == "recessive") ||
			(gene_a == "recessive" && gene_b == "non-existent"))
				child_gene = "non-existent";
		else
			child_gene = "recessive";

		Person.insert(std::make_pair(child_data[i].child_name, child_gene));
	}

	for(auto it : Person)
		std::cout << it.first << " " << it.second << '\n';
	return 0;
}
