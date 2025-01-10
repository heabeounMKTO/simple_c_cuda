#ifndef VEC_N_CUDA_H
#define VEC_N_CUDA_H


/// cpp compile directives 
/// to be able to link with CUDA
#ifdef __cplusplus
extern "C" {
#endif // extern cpp start
#include "vec.h"

void vec_add_cu(const vec_N* v1, const vec_N* v2, vec_N* result);


#ifdef __cplusplus
}
#endif // extern cpp end
#endif // vec_N_CUDA_H
