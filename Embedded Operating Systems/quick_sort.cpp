#include <iostream>
#include <omp.h>

using namespace std;

void quick_sort(int array[], int begin, int end);
int partition(int array[], int begin, int end);
//int k=0, TID;

int main()
{
	int total;

	cout<<"Enter No of Elements : ";
	cin>>total;

	int array[total];

	cout<<"Enter Elements : ";
	for(int i = 0; i < total; i++)
	{
		cin>>array[i];
	}

	quick_sort(array,0,total-1);

	cout<<endl<<"Sorted Elements : ";
	for(int i = 0; i < total; i++)
	{
		cout<<array[i]<<" ";
	}

	cout<<endl;

	return 0;
}


void quick_sort(int array[], int begin, int end)
{
	int middle;

	if(begin<end)
	{
		middle = partition(array,begin,end);
		cout<<"Pivot element with index "<<middle<<" has been found"<<"\n"<<endl;// out by thread "<<k<<"\n";

#pragma omp parallel sections
		{
#pragma omp section
			{
				//TID = omp_get_thread_num();
				//cout<<"1 SECTION "<<TID<<endl;

				//k=k+1;			
				quick_sort(array,begin,middle-1);
			}

#pragma omp section
			{

				//TID = omp_get_thread_num();
				//cout<<"2 SECTION "<<TID<<endl;

				//k=k+1;			
				quick_sort(array,middle+1,end);
			}
		}

	}//if

}//quick_sort

int partition(int array[], int begin, int end)
{

	int temp;
	int pivot = array[begin];
	int startPointer = begin+1;
	int endPointer = end;

	while(1)
	{
		while(startPointer < endPointer && pivot >= array[startPointer])
			startPointer++;

		while(pivot < array[endPointer])
			endPointer--;

		if(startPointer < endPointer)
		{
			temp = array[startPointer];
			array[startPointer] = array[endPointer];
			array[endPointer] = temp;
		}
		else
		{
			temp = array[begin];
			array[begin] = array[endPointer];
			array[endPointer] = temp;
			return(endPointer);
		}//else
	}//while

}//partition
