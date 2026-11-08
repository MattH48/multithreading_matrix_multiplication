/* CSci114_P3.cpp
 * How to run the program:
 * 1. g++ CSci114_P3.cpp
 * 2. ./a.out M N K
 * your choice of numbers in the command line argument.
 *
 * */
#include <fstream>
#include <cstdio>
#include <thread>
#include <cstdlib>
#define max_rows 100
#define max_cols 100

int C[max_rows][max_cols]; // Matrix C
void Matrix_C(int A[max_rows][max_cols], int B[max_rows][max_cols], int M,
              int N, int K, int start, int end) {
  for (int i = start; i < end; i++) {
    for (int j = 0; j < K; j++) {
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
  std::ifstream File_A; // Uses A.txt for the matrix input.
  File_A.open("A.txt");
  if (File_A.is_open()) {
    printf("File A has been successfully opened.\n");
  } else {
    printf("File A failed to open.\n");
    exit(1);
  }
  for (int i = 0; i < M; i++) {
    for (int j = 0; j < N; j++) {
      File_A >> A[i][j];
    }
  }
  File_A.close();
  printf("******Matrix A******\n");
  for (int i = 0; i < M; i++) {
    for (int j = 0; j < N; j++) {
      printf("%d ", A[i][j]);
      if (j == (N - 1)) {
        printf("\n");
      }
    }
  }
  std::ifstream File_B;
  File_B.open("B.txt");
  if (File_B.is_open()) {
     printf("File B has been opened successfully.\n");
  } else {
    printf("File B has failed to open.\n");
    exit(1);
  }
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < K; j++) {
      File_B >> B[i][j];
    }
  }
  File_B.close();
  printf("******Matrix B******\n");
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < K; j++) {
      printf("%d ", B[i][j]);
      if (j == (K - 1)) {
        printf("\n");
      }
    }
  }
  int mid = M/2;
  std::thread threadObj1(Matrix_C, A, B, M, N, K, 0, mid);
  std::thread threadObj2(Matrix_C, A, B, M, N, K, mid, M);
  threadObj1.join();
  threadObj2.join();
  printf("*******Matrix C******\n");
  for (int i = 0; i < M; i++) {
    for (int j = 0; j < K; j++) {
      printf("%d ", C[i][j]);
    }
    printf("\n");
  }
  printf("Multiplication finished.\n");
  return 0;
}
