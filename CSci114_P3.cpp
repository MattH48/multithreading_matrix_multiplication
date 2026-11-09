/* CSci114_P3.cpp
 * How to run the program:
 * 1. g++ CSci114_P3.cpp
 * 2. ./a.out M N K for MacOS or linux
 * 3. ./a.exe M N K for windows Cygwin
 * your choice of numbers in the command line argument.
 * AI disclamer: I used feedback from AI to fine tune my code finding any
 * missing pieces. However, outside of the feedback I wrote the logic and the
 * code.
 * */
#include <cstdio>  // for printf
#include <cstdlib> // for atoi
#include <fstream> // to open the input files
#include <thread>  // for thread operations
// I decided to go with macros for the max rows and columns to make the code
// more readable Along with easing the change of the maximum values.
#define max_rows 100
#define max_cols 100

int C[max_rows][max_cols]; // Matrix C
void Matrix_C(int A[max_rows][max_cols], int B[max_rows][max_cols], int M,
              int N, int K, int start,
              int end) { // This function multiplies the matrix.
  for (int i = start; i < end;
       i++) { // Start and end are for the threads to work off of.
    for (int j = 0; j < K; j++) { //
      for (int k = 0; k < N; k++) {
        C[i][j] += A[i][k] * B[k][j]; // Multiplacation of matrix A and B.
      }
    }
  }
}
int main(int argc, char **argv) { // Takes cmd arguments for the matrix.
  if (argc < 4) {
    printf("Invalid amount of arguments for program.\n");
    exit(1);
  }
  int A[max_rows][max_cols], B[max_rows][max_cols]; // Matrices
  int M, N, K;
  M = atoi(argv[1]);
  N = atoi(argv[2]);
  K = atoi(argv[3]);
  // checks if any cmdline arg is over max limit.
  if (M > 100 || N > 100 || K > 100) {
    printf("One of the arguments is over 100 invalid.\n");
    exit(1);
  }
  std::ifstream File_A; // Uses A.txt for the matrix input.
  File_A.open("A.txt");
  if (File_A.is_open()) { // The opening of the file.
    printf("File A has been successfully opened.\n");
  } else {
    printf("File A failed to open.\n");
    exit(1);
  }
  // allocated the values from the file to the matrix
  for (int i = 0; i < M; i++) {
    for (int j = 0; j < N; j++) {
      File_A >> A[i][j];
    }
  }
  File_A.close();
  printf("******Matrix A******\n");
  for (int i = 0; i < M; i++) { // Tests matrx A
    for (int j = 0; j < N; j++) {
      printf("%d ", A[i][j]);
      if (j == (N - 1)) {
        printf("\n");
      }
    }
  }
  std::ifstream File_B;
  File_B.open("B.txt");
  if (File_B.is_open()) { // The opening of the file.
    printf("File B has been opened successfully.\n");
  } else {
    printf("File B has failed to open.\n");
    exit(1);
  }
  // allocated the values from the file to the matrix
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < K; j++) {
      File_B >> B[i][j];
    }
  }
  File_B.close();
  printf("******Matrix B******\n");
  for (int i = 0; i < N; i++) { // Tests matrix B
    for (int j = 0; j < K; j++) {
      printf("%d ", B[i][j]);
      if (j == (K - 1)) {
        printf("\n");
      }
    }
  }
  std::thread threads[max_rows]; // Used an array to create threads
  for (int i = 0; i < M; i++) { // Creates a thread per row
    threads[i] = std::thread(Matrix_C, A, B, M, N, K, i, i + 1);
  }
  for (int i = 0; i < M; i++) { // joins each thread created
    threads[i].join();
  }
  printf("*******Matrix C******\n"); // Prints the result of matrix C
  for (int i = 0; i < M; i++) {
    for (int j = 0; j < K; j++) {
      printf("%d ", C[i][j]);
    }
    printf("\n");
  }
  printf("Multiplication finished.\n");
  return 0;
}
