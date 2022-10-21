#include<math.h>
#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<stdbool.h>

//(-100)-((-10)*10)
//0.1+0.035+8*2(-
//((((-8)(/3)*0.5))^10
//-0.1+0.035+8*2

struct Node_c
{
    char data;
    struct Node_c *prev, *next;
};

struct Node_d
{
    double data;
    struct Node_d *prev, *next;
};

void initLinkList_c(struct Node_c **head)
{
    *head = NULL;
}

void initLinkList_d(struct Node_d **head)
{
    *head = NULL;
}

void addToHead_c(struct Node_c **head, char data)
{
    //創建一個新的Node
    struct Node_c *buf_node = (struct Node_c*)malloc(sizeof(struct Node_c));
    buf_node->data = data;
    buf_node->prev = NULL;
    buf_node->next = NULL;

    //linkedlist為空的情形
    if((*head) == NULL)
    {
        *head = buf_node;
    }
    //已經存在Node
    else {
        (*head)->prev = buf_node;
        buf_node->next = (*head);
        *head = buf_node;
    }
}

void addToHead_d(struct Node_d **head, double data)
{
    //創建一個新的Node
    struct Node_d *buf_node = (struct Node_d*)malloc(sizeof(struct Node_d));
    buf_node->data = data;
    buf_node->prev = NULL;
    buf_node->next = NULL;

    //linkedlist為空的情形
    if((*head) == NULL)
    {
        *head = buf_node;
    }
    //已經存在Node
    else {
        (*head)->prev = buf_node;
        buf_node->next = (*head);
        *head = buf_node;
    }
}

void deleteData_c(struct Node_c **head, char data)
{
    struct Node_c *iter = *head;
    while(iter != NULL)
    {
      if(iter->data == data)
      {
        //更新node
        if(iter->prev != NULL)
          iter->prev->next = iter->next;
        if(iter->next != NULL)
          iter->next->prev = iter->prev;

        //更新head & tail
        if(iter == *head)
        {
          *head = iter->next;
        }

        //刪除此node
        free(iter);

        //完成後回傳
        return;
      }
      else
      {
        iter = iter->next;
      }
    }
}

void deleteData_d(struct Node_d **head, double data)
{
    struct Node_d *iter = *head;
    while(iter != NULL)
    {
      if(iter->data == data)
      {
        //更新node
        if(iter->prev != NULL)
          iter->prev->next = iter->next;
        if(iter->next != NULL)
          iter->next->prev = iter->prev;

        //更新head & tail
        if(iter == *head)
        {
          *head = iter->next;
        }

        //刪除此node
        free(iter);

        //完成後回傳
        return;
      }
      else
      {
        iter = iter->next;
      }
    }
}


void push_c(struct Node_c **stack, char data)
{
    addToHead_c(stack, data);
}

void push_d(struct Node_d **stack, double data)
{
    addToHead_d(stack, data);
}

char pop_c(struct Node_c **stack)
{
    char num = (*stack)->data;
    deleteData_c(stack, num);
    return num;
}

double pop_d(struct Node_d **stack)
{
    double num = (*stack)->data;
    deleteData_d(stack, num);
    return num;
}

char top_c(struct Node_c *stack)
{
    return stack->data;
}

double top_d(struct Node_d *stack)
{
    return stack->data;
}

int empty_c(struct Node_c *stack)
{
    return stack == NULL ? 1 : 0;
}

int empty_d(struct Node_d *stack)
{
    return stack == NULL ? 1 : 0;
}


void display(struct Node_d *head)
{
    struct Node_d *iter = head;
    int counter = 0;
    printf("(");

    while(iter != NULL)
    {
      if(counter != 0)
        printf(", ");
      
      printf("%lf", iter->data);
      iter = iter->next;

      counter++;
    }
    printf(")\n");
}




void check_9(char *ch, int iter, int *bonus)
{
  if(ch[iter] == '9')
  {
    //std::cout << "equal nine:" << iter << std::endl; 
    ch[iter] = '0';
    check_9(ch, iter-1, bonus);
  }
  else if(ch[iter] < '9' && ch[iter] >= '0')
  {
    //std::cout << "smaller than nine:" << iter << std::endl; 
    ch[iter] += 1;
  }
  else if(ch[iter] == '.')
  {
    //std::cout << "find dot:" << iter << std::endl; 
    (*bonus) = (*bonus) + 1;
  }
}

//想法，把小數轉成整數後計算
double banker_rounding(const double input)
{
  //std::cout << "input:" << input << std::endl;

  bool isDecimal = false, isNegative = false;
  int bonus = 0;
  char ch[128], *dot_place = 0;
  sprintf(ch, "%lf", input);

  if(input - (long long int)input != 0 && (dot_place = strchr(ch, '.')) != NULL)
    isDecimal = true;

  if(input < 0)
    isNegative = true;
  
  if(isDecimal)
  {
    for(int i = strlen(ch)-1; ch[i-2] != '.';i--)
    {
      if(ch[i] - '0' > 5 || (ch[i] - '0' == 5 && (ch[i-1] - '0') % 2 == 1))
      {
        ch[i] = '0';
        check_9(ch, i-1, &bonus);
      }
    }


    *(dot_place + 3) = '\0';
    if(isNegative)
    {
      //std::cout << "negative:" << atof(ch) - bonus << std::endl;
      return atof(ch) - bonus;
    }
    else
    {
      //std::cout << "positive:" << atof(ch) + bonus << std::endl;
      return atof(ch) + bonus;
    }
  }

  //std::cout << "integer:" << input << std::endl;
  return input;
}

int percedence(char ch)
{
  if(ch == '^')
    return 0;
  else if(ch == '*' || ch == '/')
    return 1;
  else if(ch == '+' || ch == '-')
    return 2;
  else if(ch == '(')
    return 3;

  return -1;
}

bool check_symbol(char ch)
{
  char table[] = {'+','-','*','/','^','(',')'};
  for(int i = 0;i < 7;i++)
  {
    if(ch == table[i])
      return true;
  }
  
  return false;
}

double calculation(char ch, double a, double b)
{
  switch(ch)
  {
    case '+':
      return b+a;
    case '-':
      return b-a;
    case '*':
      return b*a;
    case '/':
      return b/a;
    case '^':
      return pow(b,a);
    default:
      return 0;
  }
}


int main()
{
  //輸入的字串
  char input[10000] = {0}, postfix[10000], buf[10000];

  //每一行運算式
  
  while(scanf("%s", input) != EOF)
  {
    //1.把全部的數字轉成變數
    //變數array，使用ASCII當作index
    double var_array[128] = {0};
    int base_index = 'A';
    char *start = input, *end = input;

    //使用strtod尋找字串中的小數，如果該字元非小數，則繼續迭代
    while(*start != '\0')
    {
       if(!isdigit(*start))
        start++;
       else
       {
        //找到數字
        double r = strtod(start, &end);
        //定義變數
        char index[2] = {(char)base_index ,'\0'};
        //以此變數作為index放入數字
        var_array[base_index] = r;

        //複製字串
        strcpy(buf, end);
        strcpy(start, index);
        strcpy(start+1, buf);
        base_index++;

        //std::cout << "Step 1:" << input << std::endl;
       };
    }


    //2.把infix轉成postfix
    bool error_found = false;

    struct Node_c *sym_stack;
    initLinkList_c(&sym_stack);

    for(int i = 0;i < strlen(input);i++)
    {

      //如果是變數，就放到post_fix array
      if(input[i] >= 'A' && input[i] != '^')
      {
        //std::cout << "var\n";
        char ch_buf[2] = {input[i], '\0'};
        strcpy(postfix + strlen(postfix), ch_buf);
      }
      //需要先處裡負號的情況(前方為符號，且後方為變數，或者這個負號在最前方)
      else if(input[i] == '-' && input[i+1] != '\0' &&(i == 0 || (check_symbol(input[i-1]) && !check_symbol(input[i+1]) )))
      {
        //std::cout << "minus\n";
        var_array[input[i+1]] = var_array[input[i+1]] * -1;
      }
      //正常狀況，把符號放入(符號為左括號，或者stack為空，或者此符號比stack頂部符號)
      else if(input[i] != ')' && (empty_c(sym_stack) || input[i] == '(' || percedence(input[i]) < percedence(top_c(sym_stack))
        || top_c(sym_stack) == '^' && input[i] == '^'))
      {
        //std::cout << "push\n";
        push_c(&sym_stack, input[i]);
      }
      //遇到右括號
      else if(input[i] == ')')
      {
        //std::cout << "right parenthesis\n";
        while(empty_c(sym_stack) || top_c(sym_stack) != '(')
        {
          if(empty_c(sym_stack))
          {
            error_found = true;
            goto error2;
          }
            
          char ch_buf[2] = {top_c(sym_stack), '\0'};
          strcpy(postfix + strlen(postfix), ch_buf);
          pop_c(&sym_stack);
        }

        //左括號拿掉
        pop_c(&sym_stack);
      }
      //遇到順序比較低的運算子
      else
      {
        //拿符號直到stack為空，或者順序比stack符號小
        while(!empty_c(sym_stack) && percedence(input[i]) >= percedence(top_c(sym_stack)))
        {
          char ch_buf[2] = {top_c(sym_stack), '\0'};
          strcpy(postfix + strlen(postfix), ch_buf);
          pop_c(&sym_stack);
        }
        push_c(&sym_stack, input[i]);
      }

      //print("for stack", sym_stack);
      //std::cout << postfix << std::endl;
    }

    //把剩下的符號拿出
    while(!empty_c(sym_stack))
    {
      char ch_buf[2] = {top_c(sym_stack), '\0'};
      strcpy(postfix + strlen(postfix), ch_buf);
      pop_c(&sym_stack);
    }

    //print("final stack", sym_stack);
    //std::cout << postfix << std::endl;

    if(error_found)
    {
      error2:
      {
        printf("ERROR\n");
        memset(postfix, 0, 10000);
        continue;
      }
    }
    

    //3.開始計算
    struct Node_d* calc;
    initLinkList_d(&calc);

    for(int i = 0;i < strlen(postfix);i++)
    {
      if(postfix[i] == '(')
        goto error;
      else if(!check_symbol(postfix[i]))
        push_d(&calc,var_array[postfix[i]]);
      else
      {
        double var_a = 0, var_b = 0;

        if(empty_d(calc))
          goto error;
        else
        {
          var_a = top_d(calc);
          pop_d(&calc);
        }
        
        if(empty_d(calc))
          goto error;
        else
        {
          var_b = top_d(calc);
          pop_d(&calc);
        }

        double result = calculation(postfix[i], var_a, var_b);
        result = banker_rounding(result);
        push_d(&calc, result);
      }

        //printf("%c\n", postfix[i]);
        //printf("calc stack\n");
        //display(calc);
    }
    printf("%.2lf\n", top_d(calc));

    memset(postfix, 0, 10000);
    continue;

    error:
    {
        printf("ERROR\n");
      memset(postfix, 0, 10000);
    }
  }
}