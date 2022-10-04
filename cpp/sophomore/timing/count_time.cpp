//使用計時器計算完成時間
//https://tinyurl.com/2p8j62he
//https://levelup.gitconnected.com/8-ways-to-measure-execution-time-in-c-c-48634458d0f9

//傳遞函式到函式中
//https://stackoverflow.com/questions/9410/how-do-you-pass-a-function-as-a-parameter-in-c

//目前問題，為什麼每次執行時間不同


#include<cstdlib>
#include<iostream>

#define LENGTH 5

//創建隨機數
void create_random_number(int *array, int *backup, int length)
{
  srand(time(NULL));
  std::cout << "array:";
  for(int i = 0;i < length;i++)
  {
    array[i] = rand() % 10;
    backup[i] = array[i];
    std::cout << array[i] << " ";
  }
  std::cout << "\n";
}

//執行選擇排序法(較差版本)
void selection_sort_1(int *array, int length)
{
  for(int i = 0;i < length;i++)
  {
    for(int j = i+1; j < length;j++)
    {
      if(array[i] > array[j])
      {
        int buf = array[i];
        array[i] = array[j];
        array[j] = buf;
      }
    }
  }
}

//執行選擇排序法(較好版本)
void selection_sort_2(int *array, int length)
{
  for(int i = 0;i < length;i++)
    {
      int min = i;
      for(int j = i+1; j < length;j++)
      {
        if(array[min] > array[j])
        {
          min = j;
        }
      }

      if(i != min)
      {
        int buf = array[min];
        array[min] = array[i];
        array[i] = buf;
      }
    }
}


void bubble_sort (int *arr, int len)
{

	int i, j,temp;
	bool exchanged = true;
	
	for (i=0; exchanged && i<len-1; i++){ /* 外迴圈為排序趟數，len個數進行len-1趟,只有交換過,exchanged值為true才有必要執行迴圈,否則exchanged值為false不執行迴圈 */
        exchanged = false;
		for (j=0; j<len-1-i; j++) 
		{ /* 內迴圈為每趟比較的次數，第i趟比較len-i次  */
			if (arr[j] > arr[j+1])
			{ /* 相鄰元素比較，若逆序則互換（升序為左大於右，逆序反之） */
				temp = arr[j];
				arr[j] = arr[j+1];
				arr[j+1] = temp;
				exchanged = true; /*只有數值互換過, exchanged才會從false變成true,否則數列已經排序完成,exchanged值仍然為false,沒必要排序 */
			}
       }
    }
}



//重製陣列
void reset_array(int *current, int *replace, int length)
{
  for(int i = 0;i < length;i++)
  {
    *(current + i) = *(replace + i);
  }
}

void print_array(int *array, int length)
{
  for(int i = 0;i < length;i++)
  {
    std::cout << array[i] << " ";
  }
  std::cout << "\n";
}

//紀錄演算法所需時間
void algorithm_timing(void(*func)(int *, int), int *array, int *array_backup, int length, 
struct timespec *t_begin, struct timespec *t_end)
{
  clock_gettime(CLOCK_REALTIME, t_begin);

  //執行演算法
  func(array, length);
    
  clock_gettime(CLOCK_REALTIME, t_end);
  
  //印出排序好的陣列
  print_array(array, length);
  //重製陣列
  reset_array(array, array_backup, length);
}

int main()
{ 
    int arr[LENGTH] = {3,0,2,0,5}, arr_backup[LENGTH] = {3,0,2,0,5};
    
    //產生隨機數
    //create_random_number(arr, arr_backup, LENGTH);

    for(int i = 0;i < 30;i++)
    {
      //計算時間
    struct timespec t_start, t_end;
    struct timespec t2_start, t2_end;
    
    algorithm_timing(selection_sort_1, arr, arr_backup, LENGTH, &t_start, &t_end);
    algorithm_timing(selection_sort_2, arr, arr_backup, LENGTH, &t2_start, &t2_end);


    //印出執行時間
    std::cout << "Selection Sort1:" << t_end.tv_nsec - t_start.tv_nsec << " ns" << std::endl;
    std::cout << "Selection Sort2:" << t2_end.tv_nsec - t2_start.tv_nsec << " ns" << std::endl << std::endl;
    }
}