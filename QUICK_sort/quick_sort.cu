

 #include <stdio.h>
 #include <stdlib.h>

 #define MAX_THREADS 128
 #define N 10
 #define MAX_LEVELS	300

 int*	host_values;
 int*	device_values;

 __global__ static void quicksort(int* values)
{
	int pivot, L, R;
	int idx =  threadIdx.x + blockIdx.x * blockDim.x;
	int start[MAX_LEVELS];
	int end[MAX_LEVELS];

	start[idx] = idx;
	end[idx] = N - 1;
	while (idx >= 0)
	{
		L = start[idx];
		R = end[idx];
		if (L < R)
		{
			pivot = values[L];
			while (L < R)
			{
				while (values[R] >= pivot && L < R)
					R--;
				if(L < R)
					values[L++] = values[R];
				while (values[L] < pivot && L < R)
					L++;
				if (L < R)
					values[R--] = values[L];
			}
			values[L] = pivot;
			start[idx + 1] = L + 1;
			end[idx + 1] = end[idx];
			end[idx++] = L;
			if (end[idx] - start[idx] > end[idx - 1] - start[idx - 1])
			{

				int tmp = start[idx];
				start[idx] = start[idx - 1];
				start[idx - 1] = tmp;

				tmp = end[idx];
				end[idx] = end[idx - 1];
				end[idx - 1] = tmp;
	        }

		}
		else
		{
			idx--;
		}
	}
}


 int main()
 {

 	size_t size = N * sizeof(int);

 	host_values = (int*)malloc(size);

    cudaMalloc((void**)&device_values, size);

    const  int cThreadsPerBlock = 128;

    for (int x = 0; x < N; ++x)
    {
    	printf("Enter Number:");
    	scanf("%d",&host_values[x]);
    }

	cudaMemcpy(device_values, host_values, size, cudaMemcpyHostToDevice) ;

	quicksort <<< MAX_THREADS / cThreadsPerBlock, MAX_THREADS / cThreadsPerBlock, cThreadsPerBlock >>> (device_values);

	cudaMemcpy(host_values, device_values, size, cudaMemcpyDeviceToHost) ;

    for (int x = 0; x < N; ++x)
    {
    	printf("\n%d",host_values[x]);
    }

	cudaFree(device_values) ;
 	free(host_values);

 	cudaThreadExit();
}

 /*
  *
  *
  * Last login: Tue Apr  7 14:18:46 2015 from 10.80.0.65
echo $PWD'>'
/bin/sh -c "cd \"/tmp/nsight-debug\";\"/tmp/nsight-debug/test\"";exit
cuda-admin@cuda-admin:~$ echo $PWD'>'
/home/cuda-admin>
cuda-admin@cuda-admin:~$ /bin/sh -c "cd \"/tmp/nsight-debug\";\"/tmp/nsight-debu g/test\"";exit
Enter Number:
9
9

Enter Number:
8
8


Enter Number:
7
7

Enter Number:
6
6

Enter Number:
5
5


Enter Number:
4
4


Enter Number:
3
3


Enter Number:
2
2

Enter Number:
1
1

Enter Number:
10
10


1
2
3
4
5
6
7
8
9
10

logout
  *
  */

