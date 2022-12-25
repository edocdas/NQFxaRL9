#include <stdio.h>
#include <errno.h>
#include <sys/time.h>
#include <thread>
#include <iostream>

#define MAX 500

void multiplication(int raw, int col, double (&matrix1)[MAX][MAX], double (&matrix2)[MAX][MAX],
double (&matrix3)[MAX][MAX], int i, int j, int k, float val)
{
   //std::cout << "row:" << raw << " col:" << col << std::endl;
   //std::cout << "i:" << i << " j:" << j << std::endl;
   for(j=0;j<col;j++) //matrix2's col
   {      
      val = 0;
      for(k=0;k<raw;k++) //matrix2's raw
      {
         //std::cout << matrix1[i][k] << " " << matrix2[k][j] << std::endl;
         val+=matrix1[i][k]*matrix2[k][j];
      }
      matrix3[i][j] = val;
   }
}

int main()
   {
   int raw,col,i=0,j=0,k=0,x=0;
   float val;
   double matrix1[MAX][MAX],matrix2[MAX][MAX],matrix3[MAX][MAX];
   char infilename[20],outfilename[20];
   FILE *infile, *outfile;
   struct timeval tp_s, tp_e;
   struct timezone tzp_s, tzp_e;
   for(i=0;i<raw;i++)
      {
      for(j=0;j<col;j++)
         matrix1[1][1]=matrix2[1][1]=matrix3[1][1]=0;
      }
   gettimeofday(&tp_s,&tzp_s);

   for(x=0;x<300;x++)
      {
      sprintf(infilename,"in%d.txt",x+1);
      sprintf(outfilename,"out%d.txt",x+1);
      if ((infile=fopen(infilename,"r"))==NULL)
         perror("in open error~\n");
      fscanf(infile,"%d",&raw);
      fscanf(infile,"%d",&col);
      printf("%d\n",x);
      for(i=0;i<raw;i++) // set matrix value
         {
         for(j=0;j<col;j++)
            {
            fscanf(infile,"%f",&val);
            matrix1[i][j]=matrix2[i][j]=val;
            }
         }

      std::thread thread_arr[raw];

      for(i=0;i<raw;i++) //matrix1's raw
      {
         //std::cout << "i:" << i << std::endl;
         thread_arr[i] = std::thread(multiplication, raw, col, std::ref(matrix1), std::ref(matrix2), std::ref(matrix3), i, j, k, val);
         /*for(j=0;j<col;j++) //matrix2's col
         {
            val=0;
            for(k=0;k<raw;k++) //matrix2's raw
            {
            val+=matrix1[i][k]*matrix2[k][j];
            }
            matrix3[i][j]=val;
         }*/
      }

      for(i=0;i<raw;i++) //matrix1's raw
      {
         thread_arr[i].join();
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
      }
   gettimeofday(&tp_e,&tzp_e);
   if ((outfile=fopen("time.txt","w"))==NULL)
      perror("out open error~\n");
   fprintf(outfile,"Total execution time =%ld\n",tp_e.tv_sec-tp_s.tv_sec);
   fclose(outfile);
   }
