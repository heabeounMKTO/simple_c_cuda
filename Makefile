run_cpu:
	gcc main.c -o main -lm -s 
	./main

static_gpu:
	nvcc -c vec.cu -o vec_gpu.o
	ar rcs libvec_gpu.a vec_gpu.o
	rm vec_gpu.o


run_gpu: static_gpu
	gcc -DVEC_USE_GPU=ON main.c -L. -lvec_gpu -lcudart -o main_gpu -lm -s
	./main_gpu
