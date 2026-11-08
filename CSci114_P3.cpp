/* CSci114_P3.cpp
 * How to run the program:
 * 1. g++ CSci114_P3.cpp
 * 2. ./a.out M N K
 * your choice of numbers in the command line argument.
 *
 * */
#include <fstream>
#include <iostream>
#include <mutex>
#include <thread>
#define max_rows 100
#define max_cols 100
using std::cout;
using std::mutex;

mutex mt;
void Matrix_C(int A[max_rows][max_cols], int B[max_rows][max_cols], int M,
              int N, int K) {
  mt.lock();
  int C[max_rows][max_cols]; // Matrix C
  for (int i = 0; i <= M; i++) {
    for (int j = 0; j <= N; j++) {
      for (int k = 0; k <= K; k++) {
        C[i][j] += A[i][k] * B[k][j]; // Multiplacation of matrix A and B.
      }
    }
  }
  printf("*******Matrix C******\n");
  for (int i = 0; i < M; i++) {
    for (int j = 0; j < K; j++) {
      cout << C[i][j] << " ";
    }
    printf("\n");
  }
  mt.unlock();
}
int main(int argc, char **argv) { // Takes cmd arguments for the matrix.
  if (argc < 4) {
    cout << "Invalid amount of arguments for program.\n";
  }
  int A[max_rows][max_cols], B[max_rows][max_cols]; // Matrices
  int M, N, K;
  M = atoi(argv[1]);
  N = atoi(argv[2]);
  K = atoi(argv[3]);
  std::ifstream File_A; // Uses A.txt for the matrix input.
  File_A.open("A.txt");
  if (File_A.is_open()) {
    cout << "File A has been successfully opened.\n";
  } else {
    cout << "File A failed to open.\n";
  }
  for (int i = 0; i < M; i++) {
    for (int j = 0; j < N; j++) {
      File_A >> A[i][j];
    }
  }
  File_A.close();
  cout << "******Matrix A******\n";
  for (int i = 0; i < M; i++) {
    for (int j = 0; j < N; j++) {
      cout << A[i][j] << " ";
      if (j == (N - 1)) {
        cout << '\n';
      }
    }
  }
  std::ifstream File_B;
  File_B.open("B.txt");
  if (File_B.is_open()) {
    cout << "File B has been opened successfully.\n";
  } else {
    cout << "File B has failed to open.\n";
  }
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < K; j++) {
      File_B >> B[i][j];
    }
  }
  File_B.close();
  cout << "******Matrix B******\n";
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < K; j++) {
      cout << B[i][j] << " ";
      if (j == (K - 1)) {
        cout << '\n';
      }
    }
  }
  std::thread threadObj1(Matrix_C, A, B, M, N, K);
  std::thread threadObj2(Matrix_C, A, B, M, N, K);
  threadObj1.join();
  threadObj2.join();
  cout << "Multiplication finished.\n";
  return 0;
}
