#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<omp.h>

using namespace std;

void NarySearch (int *A, int lo, int hi, int key, int Ntrvl, int *pos)
{

/* step is the number of slots between each element to be tested
 in the current round. By computing indexes with floating-point 
 numbers and truncating any fractional parts before utilizing
 the value, we can ensure that the computed key test indexes
 are more equitably spread out within the search array  */
	float offset, step;

	//The mid[0] element holds the index of the leftmost bound of the search array,
	
	int *mid = new int[Ntrvl+1];
	char *locate = new char[Ntrvl+2];
	int i;
	int tot_threads;
	int thrd_num;

	locate[0] = 'R';
	locate[Ntrvl+1] = 'L';

 	printf("\nTotal number of threads :  %d\n",Ntrvl);


/*The parallel region encloses the while loop, which means that
 each thread on the team will be executing all iterations of
 the while loop (the curly braces on the parallel pragma aren’t 
 strictly needed, but they serve to point out the extent of
 the parallel region). For threads to keep in sync with 
 these iterations, the variables for lo, hi, and pos must
 be globally accessible to each thread. This will ensure
 that the results of the while conditional test are the same 
 in all threads and that the threads will end the parallel
 region at the same time.*/

 	//Parallel=== Directive that Defines a parallel region, which is code that will be executed by multiple threads in parallel.
 	//num_threads(Ntrvl) =====CLAUSE that Sets the number of threads in a thread team.

	#pragma omp parallel num_threads(Ntrvl)
 	{

 		/*  The while loop continues to iterate a new search
 		 round as long as there is at least one array item 
 		 to be searched and no element of the array has been
 		  found to have a matching key.*/

 		while(lo <= hi && *pos == -1) 
		{

	/*In addition, this code includes the lmid variable to give 
	threads a local value for holding the index value of
      a key to be compared against the search key.*/		
	/* The declaration of lmid within the while loop gives each 
	thread a local copy*/	
	
		int lmid;
 		#pragma omp single
   		{
   			
    			mid[0] = lo - 1;
    			step = (float)(hi - lo +1)/(Ntrvl+1);
    			
    		}

    /* The firstprivate clause will create a private copy of 
    this variable for each thread and initialize that copy with
     the value computed outside of the worksharing construct.*/
//firstPrivate ====Specifies that each thread should have its own instance of a variable,
// and that the variable should be initialized with the value of the variable,
// because it exists before the parallel construct. The variable to have 
 //instances in each thread and that will be initialized with the value
 // of the variable, because it exists before the parallel construct.
 // If more than one variable is specified, separate variable names with a comma.

 // private===Specifies that each thread should have its own instance of a variable.
 
 /*private variables are not initialised, i.e. they start with random values
  like any other local automatic variable (and they are often implemented using
   automatic variables on the stack of each thread).If i is made firstprivate,
    then it is initialised with the value that it has before the parallel region*/	

 		#pragma omp for private(offset) firstprivate(step)
		for (i = 1; i <= Ntrvl; i++) 
		{
			offset = step* i + (i - 1);
			lmid = mid[i] = lo + (int)offset;
			if(lmid <= hi) {
	 			if(A[lmid] > key)
	  				locate[i] = 'L';
	 			else if (A[lmid] < key)
	  				locate[i] = 'R';
	 			else 
				{
	  				locate[i] = 'E';
	   				*pos = lmid; 
	   				thrd_num = omp_get_thread_num();
					printf("Number found by thread %d",thrd_num);
					} //found
	    			}
			else {
	  			mid[i] = hi + 1;
	  			locate[i] = 'L';
			}
       	}

/* Using the single worksharing construct makes certain that the 
second for loop and the last boundary check of the algorithm
 will be executed in serial.*/
//Lets you specify that a section of code should be executed on 
       	//a single thread, not necessarily the master thread.
 		#pragma omp single
		{
    			for (i = 1; i <= Ntrvl; i++)
			{
      		if (locate[i] != locate[i-1]) {
        			lo = mid[i-1] + 1;
        			hi = mid[i] - 1;
      		}
   			}

   // loop breaking condition if the element is not preset in the array 			
   			if (locate[Ntrvl] != locate[Ntrvl+1]) 
   				lo = mid[Ntrvl] +1;
   		}  // end single
  		} //End of while
 	} // end parallel region
}

int main()
{
	
	//array to be searched (A)
	int A[30]; 
	int size;

			cout<<"\n ENTER SIZE OF ARRAY ---->  ";
			cin>>size;

			cout<<"\n ********* ENTER ELEMENTS IN ARRAY *******\n";
				
				for(int i=0;i<size;i++)
					{
						cout<<"ENTER "<<i<<" ELEMENT -->  "; 
						cin>>A[i];
					}

//the initial index bounds of the search space (lo and hi)
	int lo = 0;
	int hi = size-1;

 //the value of the key the algorithm is attempting to find
	int key;
				cout<<"\n ENTER ELEMENT TO BE SERACHED:   ";
				cin>>key;

/*the number of intervals to divide the search array into each round (Ntrval
  The Ntrvl parameter is likely going to be the number of threads */

	int Ntrvl = 3;

//the pointer to return the index position of a record with a matching key (pos)
	int pos = -1;
	
	double start_time = omp_get_wtime();

	NarySearch(A,lo,hi,key,Ntrvl,&pos);

	if(pos!=-1)
	{
		cout<<"\n ELEMENT IS FOUND AT LOCATION : "<<(pos+1)<<"\n";
	}
	else
		cout<<"\n ELEMENT NOT FOUND\n";

		cout<<"\nTotal time taken to execute n-ary search:  "<<omp_get_wtime() - start_time<<endl;
	}

/*   This function declares two arrays. These will hold the index of the key
test element (mid) and the results of the corresponding key comparison (locate).
The locate array has two more slots than the number of intervals to be used. The
first and last elements mimic the key comparison results from the phantom array
slots just outside the bounds of the search array and are initialized to R and
L, respectively.

The body of the while loop has three separate parts. The first for loop computes an offset into
the search array for each interval and stores the computed index into the corresponding
element of mid (if the computed index is outside of the search array, the saved value is hi + 1
and this will be treated like the rightmost phantom element). Next, the key found at each of
these positions is compared to the search key and the relationship of the location of the search
key to the element key is recorded in the corresponding locate element. If there is a match on
the search key, the value of pos is updated with the index of the matching element.

Once all of the test indexes are computed and the results of the key comparisons have been
noted, the second for loop checks all consecutive pairs of elements from the locate array to see
whether the characters stored there are different. As shown in Figure 9-1, this difference
indicates that the record that matches the search key will lie between the two corresponding
index points in the search array. When such a difference is found, the values of lo and hi are
updated to set the bounds of the search array for the next iteration of the while loop. The third
part of the while loop body does this same locate element test, but it does so with the rightmost
phantom index (Ntrvl + 1). If this value is different from the locate element of the final
computed test index, then only the lower bound of the search array needs to be updated.

>>>>>>>>The main reason that we’re using
OpenMP for the concurrent version of NarySearch() is because of the need for two barrier
synchronizations. We need the first between the determination of the location of the matching
element from the data array and the search through the locate array to identify the difference
between two consecutive items. We need the second barrier between the update of lo and hi
and the start of the next iteration of the while loop. Of course, the decision to use OpenMP is
helped along by the fact that the algorithm has a data decomposition solution and uses for
loops for iteration within the while loop.

Thus, the loop worksharing construct will divide up
the intervals (via division of the loop iterations) among the 
threads of the team. If the number of intervals (Ntrvl) is
equal to the number of threads, we will get one interval per
thread; if there are more intervals than threads, multiple
intervals will be assigned to threads.*/