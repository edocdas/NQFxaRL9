/* This program was written by Kenrick Albert on Thursday December 22, 2022 */

/*
 * TASK:
 * Matrix multiplication is an important program for scientific computing. How to improve the
 * computation performance of matrix multiplication is the key issue of the program design.
 *
 * In the homework, you must to study some technologies by yourself in order to improve the computation
 * performance of matrix multiplication. The program attached in the document is used to do matrix
 * multiplication. There are 3 test data and results attached in the Homework 2's test data post.
 *
 * The testing OS is Ubuntu 5.4.0-84-generic. There are 1000 test files needed to compute. You can implement
 * your program improved from the program attached in the file, and execute it on your computer.  In the first,
 * you should compile the codes attached in the file (as the original program), execute it on your computer,
 * and get the computing time.
 *
 * Next, you can execute your program and get its computing time. The computing time of your program should
 * be less than that of the original program. Suppose the computing time of your program is larger than that
 * of the original program, the grade of your homework 2 is very low. The computing time of the original
 * program on the test computer is 844 seconds.
 *
 * The computing time of the multi-thread program on the test
 * computer is 270 seconds. You must upload your source codes (.c or .cpp) to elearn platform. Your source
 * codes will be compiled and executed on the test computer. The grade of your homework 2 is generated
 * according to the computing time of your program. 
 */

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/time.h>
#include <pthread.h>

#define MAX 500
#define NAME_LEN 20
#define POOL_SIZE 4
/* #define TEST_COUNT 1000 */
#define TEST_COUNT 1000

// Get the global errno variable
extern int errno;

// Struct declaration 2D array of doubles
typedef struct {
    double data[MAX][MAX];
} Matrix;

// Define struct to hold all necessary data
typedef struct {
    char *outFileName;
    int row, col;
    Matrix *mat1;
    Matrix *mat2;
    Matrix *mat3;
} Bundle;

void initBundle(Bundle *b, char *_outFileName, int _row, int _col, Matrix *_mat1, Matrix *_mat2, Matrix *_mat3){
    b->outFileName = _outFileName;
    b->row         = _row;
    b->col         = _col;
    b->mat1        = _mat1;
    b->mat2        = _mat2;
    b->mat3        = _mat3;
}

void *matMult(void *args){
    // Open the output file
    FILE *outfile;

    // Retreive the argument bundle
    Bundle *argData = (Bundle*) args;

    Matrix *mat1 = argData->mat1;
    Matrix *mat2 = argData->mat2;
    Matrix *mat3 = argData->mat3;

    // Attempt to open output file
    if((outfile = fopen(argData->outFileName,"w")) == NULL)
        perror("out open error~\n");

    // Write matrix dimensions to file
    fprintf(outfile,"%d\n%d\n",argData->row, argData->col);

    // Perform matrix calculation for the current file
    float val;
    for(int i = 0; i < argData->row; i++){ //matrix1's row
        for(int j = 0; j < argData->col; j++){ //matrix2's col
            val = 0;
            for (int k = 0; k < argData->row; k++){ //matrix2's row
                val += mat1->data[i][k] * mat2->data[k][j];
            }

            // Write the multiplication result into the file
            fprintf(outfile,"%f\n", val);
        }
    }

    // Close the output file
    fclose(outfile);

    // Release the memory allocated for the argData bundle
    free(argData);

    return NULL;
}

int main(void) {
    int row, col, i = 0, j = 0, k = 0, x = 0;
    float val;
    Matrix matrix1, matrix2, matrix3;
    char infilename[NAME_LEN], outfilename[NAME_LEN];
    FILE *infile, *outfile;
    struct timeval tp_s, tp_e;
    struct timezone tzp_s, tzp_e;

    /*
     * Create threadpool with size POOL_SIZE. This conserves computer resources
     * (these do not actually create threads, this is just a container to hold them)
     */
    pthread_t threadPool[POOL_SIZE];

    // I don't know what this is for but I left it alone
    for(i = 0; i < row; i++) {
        for(j = 0; j < col; j++)
            matrix1.data[1][1] = matrix2.data[1][1] = matrix3.data[1][1] = 0;
    }

    // Clock the start time
    gettimeofday(&tp_s,&tzp_s);

    int threadIndex = 0;
    for(x = 1; x <= TEST_COUNT; x++, threadIndex++) {
        // Generate names for input and output files
        sprintf(infilename ,"in%d.txt" , x);
        sprintf(outfilename,"out%d.txt", x);

        // File open error checking
        if((infile = fopen(infilename,"r")) == NULL){
            perror("in open error~\n");
        }

        // Read row and column dimensions of input file
        fscanf(infile, "%d", &row);
        fscanf(infile, "%d", &col);
        printf("%d\n", x);

        // Initialization of matrices
        for(i = 0;i < row; i++){
            for(j = 0;j < col; j++){
                fscanf(infile,"%f",&val);
                matrix1.data[i][j] = matrix2.data[i][j] = val;
            }
        }

        // Close the infile as we no longer have to read for it in this iteration
        fclose(infile);

        // Create bundle to be processed in thread
        Bundle *argBundle = (Bundle *) malloc(sizeof(Bundle));
        initBundle(argBundle, outfilename, row, col, &matrix1, &matrix2, &matrix3);

        // Open a thread for the current matrix
        if(pthread_create(&threadPool[threadIndex], NULL, matMult, (void *) argBundle) != 0){
            return 1;
        }

        // Once we have hit our pool size or we are at the last test file, join the threads
        /* printf("Thread Index %d\n", threadIndex); */
        if(threadIndex == POOL_SIZE - 1){
            /* printf("Joining %d Threads...\n", limit); */
            for(int i = 0; i < POOL_SIZE; i++ ){
                /* printf("i = %d\n", i); */
                if(pthread_join(threadPool[i], NULL) != 0){
                    perror("Error");
                    return 1;
                }
                /* printf("Thread %d: Done!\n", i + 1); */
            }
            threadIndex = -1; // Reset the thread index
        }
    }

    // Clock the end time
    gettimeofday(&tp_e,&tzp_e);

    // Write execution duration to time.txt
    if((outfile = fopen("time.txt","w")) == NULL)
        perror("out open error~\n");

    fprintf(outfile,"Total execution time = %ld\n",tp_e.tv_sec - tp_s.tv_sec);
    fclose(outfile);

    return 0;
}
