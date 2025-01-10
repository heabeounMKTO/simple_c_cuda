#include "vec.h"
#include "time.h"
#include <stdlib.h>


double random_float() {
  return rand() / (float) (RAND_MAX) + 1.0;
}

int main() {
  int vec_N_length = 10;
  clock_t begin = clock();
  for (int i = 0; i < 5; i++) {
    vec_N vec_1 = vec_N_new(vec_N_length);
    vec_N vec_2 = vec_N_new(vec_N_length);
    vec_N result = vec_N_new(vec_N_length);
    for (int i = 0; i < vec_N_length; i++) {
      vec_N_set(&vec_1, i, random_float());
      vec_N_set(&vec_2, i, random_float());
    } 
    vec_N_add(&vec_1, &vec_2, &result);
  }
  clock_t end = clock();
  double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
  printf("time spent %f\n", time_spent);
  return 0;
}

