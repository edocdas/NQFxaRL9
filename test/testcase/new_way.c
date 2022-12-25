/*
如果執行發生錯誤
請更改第87行的Thread_size為10
*/

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/time.h>
#define MAX 500

double matrix1[MAX][MAX],matrix2[MAX][MAX];

struct x_num
{
  int x;
};

void* operation(void* not_convert_x)
{
  struct x_num *convert_x = (struct x_num*) not_convert_x;

  float val;
  int raw,col,i=0,j=0,k=0;
  char infilename[20],outfilename[20];
  FILE *infile, *outfile;
  double matrix3[MAX][MAX];
  
  sprintf(infilename,"in%d.txt",convert_x->x+1);
  sprintf(outfilename,"out%d.txt",convert_x->x+1);
  if ((infile=fopen(infilename,"r"))==NULL)
      perror("in open error~\n");
  fscanf(infile,"%d",&raw);
  fscanf(infile,"%d",&col);
  printf("%d\n",convert_x->x);
  for(i=0;i<raw;i++) // set matrix value
      {
      for(j=0;j<col;j++)
        {
        fscanf(infile,"%f",&val);
        matrix1[i][j]=matrix2[i][j]=val;
        }
      }

  for(i=0;i<raw;i++) //matrix1's raw
      {
      for(j=0;j<col;j++) //matrix2's col
        {
        val=0;
        for (k=0;k<raw;k++) //matrix2's raw
            {
            val+=matrix1[i][k]*matrix2[k][j];
            }
        matrix3[i][j]=val;
        }
      }
  if ((outfile=fopen(outfilename,"w"))==NULL)
      perror("out open error~\n");
  fprintf(outfile,"%d\n%d\n",raw,col);
  for(i=0;i<raw;i++)
      {
      for(j=0;j<col;j++,val++)
        fprintf(outfile,"%f\n",matrix3[i][j]);
      }
  fclose(infile);
  fclose(outfile);

  free(convert_x);
}



int main()
   {
   int raw,col,i=0,j=0,k=0,x=0,z=0;
   FILE *infile, *outfile;
   struct timeval tp_s, tp_e;
   struct timezone tzp_s, tzp_e;
   for(i=0;i<raw;i++)
      {
      for(j=0;j<col;j++)
         matrix1[1][1]=matrix2[1][1]=0;
      }
   gettimeofday(&tp_s,&tzp_s);

    int THREAD_SIZE = 20;

   pthread_t thread[THREAD_SIZE];
   for(x=0;x<1000;x++)
    {
      printf("%d\n", x);
      if(x % THREAD_SIZE == 0 && x != 0)
      {
        for(z=0;z<THREAD_SIZE;z++)
        {
          pthread_join(thread[z], NULL); // 建立子執行緒
        }
      }

      struct x_num *x_num = malloc(sizeof(struct x_num));
      x_num->x = x;
      pthread_create(&thread[x%THREAD_SIZE], NULL, operation, x_num); // 建立子執行緒
    }

    for(z=0;z<THREAD_SIZE;z++)
    {
      pthread_join(thread[z], NULL); // 建立子執行緒
    }

   gettimeofday(&tp_e,&tzp_e);
   if ((outfile=fopen("time.txt","w"))==NULL)
      perror("out open error~\n");
   fprintf(outfile,"Total execution time =%ld\n",tp_e.tv_sec-tp_s.tv_sec);
   fclose(outfile);
   }
