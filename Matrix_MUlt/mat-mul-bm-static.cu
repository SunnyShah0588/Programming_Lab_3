
/**
 * Copyright 1993-2012 NVIDIA Corporation.  All rights reserved.
 *
 * Please refer to the NVIDIA end user license agreement (EULA) associated
 * with this source code for terms and conditions that govern your use of
 * this software. Any use, reproduction, disclosure, or distribution of
 * this software and related documentation outside the terms of the EULA
 * is strictly prohibited.
 */
#include <stdio.h>
#include <stdlib.h>
#include <cuda.h>

#define Width 4
#define TILE_WIDTH 2
__global__ void mat_mul(int *a, int *b,int *ab, int width)
{
	// shorthand
	int tx = threadIdx.x, ty = threadIdx.y;
	int bx = blockIdx.x, by = blockIdx.y;
	// allocate tiles in __shared__ memory
	__shared__ float s_a[TILE_WIDTH][TILE_WIDTH];
	__shared__ float s_b[TILE_WIDTH][TILE_WIDTH];
	// calculate the row & col index
	int row = by*blockDim.y + ty;
	int col = bx*blockDim.x + tx;
	int result = 0;

	// loop over the tiles of the input in phases
	for(int p = 0; p < width/TILE_WIDTH; ++p)
	{
		// collaboratively load tiles into __shared__
		s_a[ty][tx] = a[row*width + (p*TILE_WIDTH + tx)];
		s_b[ty][tx] = b[(p*TILE_WIDTH + ty)*width + col];
		__syncthreads();
		// dot product between row of s_a and col of s_b
		for(int k = 0; k < TILE_WIDTH; ++k)
		result += s_a[ty][k] * s_b[k][tx];
		__syncthreads();
	}
	ab[row*width+col] = result;
}


int main()
{
    int mat_size=Width*Width*sizeof(int);	//Calculate memory size required for float matrix
    //int tot_elements=Width*Width;
    int M[Width][Width],N[Width][Width],P[Width][Width];	// Host matrix pointers

	int i=0,j=0;
	int *Md,*Nd,*Pd;		//Matrix Pointer on device memoryi.e GPU

	printf("\nEntering elements for matrix");
	for(i=0;i<Width;i++)
	{
		for(j=0;j<Width;j++)
		{
			M[i][j]=1;
			N[i][j]=1;
		}

	}

	printf("Matrix M=\n ");
	for(i=0;i<Width;i++)
	{
		for(j=0;j<Width;j++)
		{
			printf("%d\t",M[i][j]);
		}
		printf("\n");
	}
	printf("Matrix N=\n ");
	for(i=0;i<Width;i++)
	{
		for(j=0;j<Width;j++)
		{
			printf("%d\t",N[i][j]);
		}
		printf("\n");
	}
	cudaMalloc((void**)&Md,mat_size);		//Allocate memory on device global memory
	cudaMemcpy(Md,M,mat_size,cudaMemcpyHostToDevice);	//Copy matrix data from host to device memory
	cudaMalloc((void**)&Nd,mat_size);
	cudaMemcpy(Nd,N,mat_size,cudaMemcpyHostToDevice);
		cudaMalloc((void**)&Pd,mat_size);

	dim3 dimGrid(TILE_WIDTH,TILE_WIDTH);	//Variable for threads arrangement in a block.
	dim3 dimBlock(Width/TILE_WIDTH,Width/TILE_WIDTH);		//Variable for blocks arrangement in a grid.

	mat_mul<<<dimGrid,dimBlock>>>(Md,Nd,Pd,Width);	//Kernel invocation with grid and block specification in angle brackets


	cudaMemcpy(P,Pd,mat_size,cudaMemcpyDeviceToHost);	//Copy resultant matrix from device to host
	//display the resultant matrix
	printf("Product=\n ");
	for(i=0;i<Width;i++)
	{
		for(j=0;j<Width;j++)
		{
			printf("%d\t",P[i][j]);
		}
		printf("\n");
	}
	//Free device memory
	cudaFree(Md);
	cudaFree(Nd);
	cudaFree(Pd);

}

