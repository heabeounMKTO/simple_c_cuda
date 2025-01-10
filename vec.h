#ifndef VEC_N_H
#define VEC_N_H
#include <stdio.h>
#include <stdlib.h>

/* n-length vector, for demonstration purposes 
 * we will be using a flat vector */
typedef struct {
  int dimension;
  float* components; 
} vec_N;

/* utility fucntions , create, set, free etc. */
static inline vec_N vec_N_new(int dimension) {
  vec_N* vec = (vec_N*)malloc(sizeof(vec_N));
  if (vec == NULL) {
    fprintf(stderr, "memalloc failed for vec_N!\n");
  }
  vec->dimension = dimension;
  vec->components = (float*)calloc(dimension, sizeof(float));
  if (vec->components == NULL) {
    fprintf(stderr, "memalloc failed for vec_N components!\n");
    free(vec);
  }
  return *vec;
}

static inline void vec_N_free(vec_N* vec_N) {
  if (vec_N) {
    free(vec_N->components);
    free(vec_N);
  }
}

static inline void vec_N_print(const vec_N* vec_N) {
    if (!vec_N) {
        printf("Invalid vector\n");
        return;
    }
    
    printf("vector (Dim %d): [", vec_N->dimension);
    for (int i = 0; i < vec_N->dimension; i++) {
        printf("%s%.2f", i > 0 ? ", " : "", vec_N->components[i]);
    }
    printf("]\n");
}

static inline int vec_N_set(vec_N* vec_N, int index, float value) {
  // we got bounds checking before gta6
  if(!vec_N || index < 0 || index >=  vec_N->dimension) {
    fprintf(stderr, "Invalid ahh index brah\n");
    return -1;
  }
  vec_N->components[index] = value;
  return 0;
}

#ifndef VEC_USE_GPU

static inline void vec_N_add(const vec_N* v1, const vec_N* v2, vec_N* result) {
  if (!v1 || !v2 || v1->dimension != v2->dimension) {
      fprintf(stderr, "vectors must have same dimension for addition\n");
      return;
  }

  if (!result || v1->dimension != result->dimension) {
    // sets result vec_Ntor to proper dims
    *result = vec_N_new(v1->dimension);
  }

  for (int i = 0; i < v1->dimension; i++) {
        result->components[i] = v1->components[i] + v2->components[i];
  } 
}
#else 

#include "vec_gpu.h"
void vec_N_add(const vec_N* v1, const vec_N* v2, vec_N* result){
  vec_add_cu(v1, v2, result);
}

#endif // VEC_USE_GPU



#endif 
