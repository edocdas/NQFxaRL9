#include <iostream>
#include <string>

class Person {
public:
Person() = default;    // == Person(){} 就是預設都不添加引數的情況
Person(Person &copy) //copy constructor
{
	(this->parent)[0] = copy.parent[0];
	(this->parent)[1] = copy.parent[1];
	this->parent_count = copy.parent_count;
	this->name = copy.name;
	this->gene_type = copy.gene_type;
}

friend add_data(std::string, std::string, Person *, int *); //新增資料
friend bool compare_name(Person, Person); //排序用途
bool check_parent(); //檢查是否都有雙親
void define_gene(); //決定基因
void print_data();
private:
class Person *parent[2]={0}; //父與母
int parent_count = 0; //父母計數
std::string name= "";
std::string gene_type= "";
};

//這邊會有兩種狀況，一種是人加人（小孩第一次會加，第二次不會加），另一種是人加基因（加一人）
void add_data(std::string input_name, std::string input_str, Person *data, int *data_count)
{
	if(input_str == "non-existent" || input_str == "recessive" || input_str == "dominant") //人加基因的狀況
	{
		(data+(*data_count))->name = input_name;
		(data+(*data_count))->gene_type = input_str;

    (*data_count) += 1; //人數加一
	}
	else //人加人的狀況
	{
		Person *buf; //找到親代的指標
		for(int i = 0; i <= *data_count; i++) //找到親代是誰（一定會找到）
		{
			if(data[i].name == input_name)
			{
				buf = data+i;
			}
		}

		for(int i = 0; i <= *data_count; i++)               //兩種狀況，第一種小孩第一次加入，第二種小孩已經在裡面了
		{
			if(data[i].name == input_str || i == *data_count) //左方為第二次加入，右方為第一次加入，兩者其一達成就可
			{
				data[i].name = input_str;
				data[i].parent[data[i].parent_count] = buf; //親代的指標傳遞給指標陣列
				data[i].parent_count += 1; // [0]為親代1 [1]為親代2

				if(i == *data_count) //新的小孩
					(*data_count) += 1;

        return; //完成條件就結束
			}
		}
	}
}

//如果數字為2，就代表親代都有了（2個）
bool Person::check_parent()
{
	return this->parent_count == 2 ? true : false;
}

//取得父與母的基因後，決定子代基因
void Person::define_gene()
{
	std::string pa_type=(this->parent)[0]->gene_type, ma_type=(this->parent)[1]->gene_type;

	if(pa_type == "dominant" && ma_type == "dominant" || pa_type == "dominant" && ma_type == "recessive" || pa_type == "recessive" && ma_type == "dominant")
		this->gene_type = "dominant";
	else if(pa_type == "non-existent" && ma_type == "non-existent" || pa_type == "non-existent" && ma_type == "recessive" || pa_type == "recessive" && ma_type == "non-existent")
		this->gene_type = "non-existent";
	else
		this->gene_type = "recessive";
}

void Person::print_data()
{
	std::cout << this->name << " " << this->gene_type << '\n';
}

/*void Person::print_data() //debug version
   {
        std::cout << "Name:" << this->name << '\n';
        std::cout << "Gene_type:" << this->gene_type << '\n';
        if((this->parent)[0] != nullptr && (this->parent)[1] != nullptr)
                std::cout << "Parent_name:" << (this->parent)[0]->name << ", " <<
                        (this->parent)[1]->name << "\n";
   }*/

bool compare_name(Person a, Person b)
{
	return a.name > b.name ? true : false;
}

int main(){

	class Person data[3100];
	int data_num = 0, data_counter = 0; //num為總數，counter為人的數目
	std::cin >> data_num;

	for(int i = 0; i < data_num; i++)
	{
		std::string name, input_str;
		std::cin >> name >> input_str;
		add_data(name, input_str, &data[0], &data_counter);

		if(data[data_counter-1].check_parent())
			data[data_counter-1].define_gene();
	}


	for(int i = 0; i < data_counter; i++)
	{
		for(int j = 0; j < data_counter-1; j++)
		{
			if(compare_name(data[j], data[j+1]))
			{
				Person buf = data[j];
				data[j] = data[j+1];
				data[j+1] = buf;
			}
		}
	}

	for(int i = 1; i <= data_counter; i++) //print all data
	{
		data[i-1].print_data();
	}

	return 0;
}
