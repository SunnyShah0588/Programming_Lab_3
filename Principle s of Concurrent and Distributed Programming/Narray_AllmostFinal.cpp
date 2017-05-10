#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<omp.h>

using namespace std;


void NarySearch (int *Array, int low, int high, int key, int Ntrvl, int *position)
{

	float offset, step;	
	int *mid = new int[Ntrvl+1];
	char *locate = new char[Ntrvl+2];
	int i;
	int totalThreads;
	int ThreadNumber;

	locate[0] = 'R';
	locate[Ntrvl+1] = 'L';

    cout<<"TOTOAL NUMBER OF THREADS ---> "<<Ntrvl<<endl;


	#pragma omp parallel num_threads(Ntrvl)
 	{

 	
 		while(low <= high && *position == -1) 
		{	
	
		int localMid;
 		#pragma omp single
   		{
   			
    			mid[0] = low - 1;
    			step = (float)(high - low +1)/(Ntrvl+1);
    			
    		}

 		#pragma omp for private(offset) firstprivate(step)
		for (i = 1; i <= Ntrvl; i++) 
		{
			offset = step* i + (i - 1);
			localMid = mid[i] = low + (int)offset;
			if(localMid <= high) 
			{
	 			if(Array[localMid] > key)
	  				locate[i] = 'L';
	 			else if (Array[localMid] < key)
	  				locate[i] = 'R';
	 			else 
				{
	  				locate[i] = 'E';
	   				*position = localMid; 
	   				ThreadNumber = omp_get_thread_num();
					cout<<"NUMBER OF THE THREAD THAT FOUND THE NUMBER ---> "<<ThreadNumber<<endl;
			    } 
	    	}
			else {
	  			mid[i] = high + 1;
	  			locate[i] = 'L';
			}
       	}


 		#pragma omp single
		{
    			for (i = 1; i <= Ntrvl; i++)
			{
      		if (locate[i] != locate[i-1]) {
        			low = mid[i-1] + 1;
        			high = mid[i] - 1;
      		}
   			}
   			if (locate[Ntrvl] != locate[Ntrvl+1]) 
   		 		low = mid[Ntrvl] +1;
   		    } 
  		} 
 	} 
}

int main()
{
	
	
	int size;

			cout<<"\n ENTER SIZE OF ARRAY ---->  ";
			cin>>size;

	int Array[size]; 

	for (int i = 0; i < size ; i++){
		Array[i] = 0;
	}

			cout<<"\n ********* ENTER ELEMENTS IN ARRAY *******\n";
				
				for(int i=0;i<size;i++)
					{
						cout<<"ENTER "<<i+1<<" ELEMENT -->  "; 
						cin>>Array[i];
					}
 
    	int temp;

	 for(int i = 0 ; i <= size ; i++ ) {

 		for(int j = 0 ; j <= size-i ; j++ ) {

 			if( Array[j] > Array[j+1] ) {

								 temp = Array[j];
 								 Array[j] = Array[j+1];
 								 Array[j+1] = temp;
				 }
 			}
 		}

 		cout<<"\nDATA AFTER SORTING : ";
 
 		for(int j=0;j<size;j++) {

 			cout<<Array[j]<<" ";
 		}

	int low = 0;
	int high = size-1;

 
	int key;
				cout<<"\n ENTER ELEMENT TO BE SERACHED:   ";
				cin>>key;


	int Ntrvl;

				cout<<"\n ENTER THE VALUE OF N FOR N-rray:   ";
				cin>>Ntrvl;

	int position = -1;
	
	double start_time = omp_get_wtime();

	NarySearch(Array,low,high,key,Ntrvl,&position);

	if(position!=-1)
	{
		cout<<"\n ELEMENT IS FOUND AT LOCATION : "<<(position+1)<<"\n";
	}
	else
		cout<<"\n ELEMENT NOT FOUND\n";


		cout<<"\nTotal time taken to execute n-ary search:  "<<omp_get_wtime() - start_time<<endl;
	}
