#include <stdio.h>
#include <omp.h>
#include <time.h>
#define N 100
#define T 5000

int main(){
  //int num_thread = 1;//edit here to change the number of thread
  int chunk_size = 0;
  clock_t start, finish;
  start = clock();
  // initialise array h
  float h[N][N][2];
  for (int i=0; i<N; i++){
    if(i < N * 0.3 || i>= N * 0.7){
      h[0][i][0] = 20.0;
    }else{
      h[0][i][0] = 100.0;
    }
  }
  for(int i=1; i<N; i++){
    for (int j=0; j<N; j++){
      h[i][j][0] = 20.0;
    }
  }
  // iterate array and update value
  for (int iteration = 0; iteration < T; iteration++){
    //#pragma omp parallel num_threads(num_thread)
    //#pragma omp parallel for schedule(static, chunk_size);
    //#pragma omp parallel for schedule(dynamic, chunk_size);
    #pragma omp parallel for 
    for(int i = 1; i < N-1; i++){
      for (int j = 1; j < N-1; j++){
        h[i][j][1] = 0.25 * (h[i-1][j][0] + h[i+1][j][0] + h[i][j-1][0] + h[i][j+1][0]);
        h[i][j][0] = h[i][j][1];
      }
    }
  }
  // print out reformated 10 * 10 matrix
  for (int i=0; i<N; i+=10){
    for (int j=0; j<N; j+=10){
      printf("%.2f ", h[i][j][0]);
    }
    printf("\n");
  }
  finish = clock();
  FILE* f = fopen("q4_default.txt", "a");
  //fprintf(f, "%d %lf\n", num_thread, (double)(finish - start) / CLOCKS_PER_SEC);
  fprintf(f, "%d %lf\n", chunk_size, (double)(finish - start) / CLOCKS_PER_SEC);
  fclose(f);
  return 0;
}
