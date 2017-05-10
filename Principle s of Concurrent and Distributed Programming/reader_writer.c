#include <omp.h>
#include <semaphore.h>
#include <stdio.h>
#include <unistd.h>

int var = 10;
int ReadCount = 0;
sem_t Sem;   // represents one semaphore

int main()
{
	sem_init(&Sem, 0, 1);	
	int ThreadId = 0;
	int NReader, NWriter;
	int i,j;

	printf("\nEnter number of readers: ");
	scanf("%d",&NReader);
	printf("\nEnter number of writers: ");
	scanf("%d",&NWriter);


	#pragma omp parallel num_threads( (NReader+NWriter) ) shared(ThreadId)                                                                                                
	{

		printf("\n");
          
            #pragma omp for nowait
            for( i = 0 ; i<NReader ; i++)
            {
		            printf("\n");
                printf("\n%d Reader started",i+1);
                sleep(1);

                #pragma omp critical
                {           
                    ReadCount++;
                    if( ReadCount == 1 )
                        sem_wait(&Sem);
                }

                ThreadId = omp_get_thread_num();
                printf("\n\nReader %d with thread id %d is reading shared variable %d ",i+1,ThreadId,var);    

                #pragma omp critical
                {           
                    ReadCount--;
                    if( ReadCount == 0 )
                        sem_post(&Sem); 
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
