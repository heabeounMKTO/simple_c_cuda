#include "vec.h"
#include "vec_gpu.h"
#include <cuda_runtime.h>
#include <cuda_runtime_api.h>
#include <driver_types.h>
#include <stdlib.h>

__device__ void vec_add_device(float* v1, float* v2, float* result, int idx) {
    result[idx] = v1[idx] + v2[idx];
}

__global__ void vec_add_kernel(float* v1, float* v2, float* result, int n) {
    int idx = blockIdx.x * blockDim.x + threadIdx.x;
    if (idx < n) {
        vec_add_device(v1, v2, result, idx);
    }
}

void vec_add_cu(const vec_N* v1, const vec_N* v2, vec_N* result) {
  size_t components_memsize = v1->dimension * sizeof(float);
  float *d_v1 , *d_v2, *d_res;   

  if (cudaMalloc(&d_v1, components_memsize) != cudaSuccess ||
      cudaMalloc(&d_v2, components_memsize)  != cudaSuccess ||
      cudaMalloc(&d_res, components_memsize) != cudaSuccess) {
    fprintf(stderr, "CUDA memory allocation failed\n");
  }

  if (cudaMemcpy(d_v1, v1->components, components_memsize, cudaMemcpyHostToDevice) != cudaSuccess ||
      cudaMemcpy(d_v2, v2->components, components_memsize, cudaMemcpyHostToDevice) != cudaSuccess)
  {
    fprintf(stderr, "CUDA memory copy to device failed\n");
  }

  int threadsPerBlock = 256;
  int blocksPerGrid = (v1->dimension + threadsPerBlock - 1) / threadsPerBlock;
  vec_add_kernel<<<blocksPerGrid, threadsPerBlock>>>(d_v1, d_v2, d_res, v1->dimension);
  
  cudaError_t kernelError = cudaGetLastError();

  if (kernelError != cudaSuccess) {
    fprintf(stderr, "kernel launch error: %s\n",
            cudaGetErrorString(kernelError));
  }

  if (cudaMemcpy(result->components, d_res, components_memsize, cudaMemcpyDeviceToHost) !=
      cudaSuccess) 
  {
    cudaError_t cpy_error = cudaGetLastError();
    fprintf(stderr, "CUDA memory copy to host failed\n");
    fprintf(stderr, "device to host Copy error: %s\n",
            cudaGetErrorString(cpy_error));
  }
  
  cudaFree(d_v1);
  cudaFree(d_v2);
  cudaFree(d_res);

  
}
