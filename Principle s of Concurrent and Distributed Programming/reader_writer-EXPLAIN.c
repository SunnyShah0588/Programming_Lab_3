#include<omp.h>
#include<semaphore.h>
#include<stdio.h>
#include<unistd.h>

int var=10;
int ReadCount=0;

sem_t Sem;   // represents one semaphore

int main()
{
	sem_init(&Sem, 0, 1);	/*sem_init - initialize an unnamed semaphore, 
                                    sem_init() initializes the unnamed semaphore at the address pointed
       to by sem.  The value argument specifies the initial value for the
       semaphore.

       The pshared argument indicates whether this semaphore is to be shared
       between the threads of a process, or between processes.

       If pshared has the value 0, then the semaphore is shared between the
       threads of a process, and should be located at some address that is
       visible to all threads (e.g., a global variable, or a variable
       allocated dynamically on the heap).
                                initialize semaphore at the address ,1 = initial value , 0 =for threads of process*/
	int ThreadId = 0;
	int NReader, NWriter;
	int i,j;

	printf("\nEnter number of readers: ");
	scanf("%d",&NReader);
	printf("\nEnter number of writers: ");
	scanf("%d",&NWriter);


	#pragma omp parallel num_threads( (NReader+NWriter) ) shared(ThreadId)  /*Specifies that one or more variables should be shared among all threads.
                                                                             specifies threadId variable is shared among all threads*/                                                                                                 
	{
		printf("\n");
           // printf("\n in parallel construct");



            #pragma omp for nowait
            for(i=0 ; i<NReader ; i++)
            {
		printf("\n");
               printf("\n%d Reader started",i+1);
                sleep(2);

                #pragma omp critical  //Directive CRITICAL Specifies that code is only be executed on one thread at a time.
                {           
                    ReadCount++;
                    if(ReadCount==1)
                        sem_wait(&Sem);	/*If the value of the semaphore is negative, 
                                        the calling process blocks; one of the blocked processes wakes
                                         up when another process calls sem_post*/
                }

                ThreadId = omp_get_thread_num();
                printf("\n\nReader %d with thread id %d is reading shared variable %d ",i+1,ThreadId,var);    

                #pragma omp critical
                {           
                    ReadCount--;
                    if(ReadCount==0)
                        sem_post(&Sem);  /*It increments the value of the semaphore and wakes
                                           up a blocked process waiting on the semaphore, if any.*/
                }
               sleep(2);       
            }



            #pragma omp for nowait
            for(j=0 ; j<NWriter ; j++)
            {
		       
               printf("\n");
               printf("\n%d Writer started",j+1);


                sem_wait(&Sem);	//lock
                sleep(1);

                var=var+2;	//12

                ThreadId = omp_get_thread_num();

                printf("\nWriter %d with ThreadId %d has updated the shared variable to %d ",j+1,ThreadId,var);

                sem_post(&Sem);


            }


        }
        //end of parallel construct



    }
