#include<iostream>
#include<cstdlib>
#include<ctime>

using namespace std;

class Tree
{
public:
	Tree()
	{
		int j;
		for(j = 0;j < 2000;j ++)
			root[j] = -1;
	}
	int insert(int node)
	{
		int index = 0;
		while(index < 2000 && root[index] != -1)
		{
			if(root[index] < node)
				index = index * 2 + 2;
			else
				index = index * 2 + 1;
		}
		root[index] = node;
		std::cout << index << std::endl;
	}
	void inorder()
	{
		int index = 0;
		inorder(index * 2 + 1);
		output.length() ? output += " " + std::to_string(root[index]) : output += std::to_string(root[index]);
		inorder(index * 2 + 2);

		std::cout << "Inorder\n" << output;
		output.clear();
	}

	void inorder(int index)
	{
		if(root[index] == -1)
			return;

		inorder(index * 2 + 1);
		output.length() ? output += " " + std::to_string(root[index]) : output += std::to_string(root[index]);
		inorder(index * 2 + 2);
	}

	void preorder()
	{
		int index = 0;
		output.length() ? output += " " + std::to_string(root[index]) : output += std::to_string(root[index]);
		preorder(index * 2 + 1);
		preorder(index * 2 + 2);

		std::cout << "Preorder\n" << output;
		output.clear();
	}

	void preorder(int index)
	{
		if(root[index] == -1)
			return;

		output.length() ? output += " " + std::to_string(root[index]) : output += std::to_string(root[index]);
		preorder(index * 2 + 1);
		preorder(index * 2 + 2);
	}

	void postorder()
	{
		int index = 0;
		postorder(index * 2 + 1);
		postorder(index * 2 + 2);
		output.length() ? output += " " + std::to_string(root[index]) : output += std::to_string(root[index]);


		std::cout << "Postorder\n" << output;
		output.clear();
	}

	void postorder(int index)
	{
		if(root[index] == -1)
			return;

		postorder(index * 2 + 1);
		postorder(index * 2 + 2);
		output.length() ? output += " " + std::to_string(root[index]) : output += std::to_string(root[index]);
	}

	void levelorder()
	{
		for(int i = 0;i < 2000;i++)
		{
			if(root[i] != -1)
			{
				if(output.length() == 0)
					output += std::to_string(root[i]);
				else
				 	output += " " + std::to_string(root[i]);

			}
		}

		std::cout << "Level order\n" << output;
		output.clear();
	}

    void print()
    {
        for(int i = 0;i < 100;i++)
        {	
            std::cout << root[i] << " ";
        }
    }
private:
	int root[2000];
	std::string output;
};

int main()
{
	Tree *tree = new Tree();
	int j, node;
	srand(time(NULL));
	for(j = 0;j < 10;j ++)
	{
		node = rand() % 10;
		std::cout << "insert:" << node << std::endl;
		tree->insert(node);
	}
	tree->inorder();
	printf("\n");
	tree->preorder();
	printf("\n");
	tree->postorder();
	printf("\n");
	tree->levelorder();
	printf("\n");

    //tree->print();
}
