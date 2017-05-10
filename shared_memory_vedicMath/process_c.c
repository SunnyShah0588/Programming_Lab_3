/*
 * shm-client - client program to demonstrate shared memory.
 */
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <unistd.h>

#define SHMSZ     27

int main()
{
    int shmid;
    key_t key;
    char *shm, *s;

    /*
     * We need to get the segment named
     * "5678", created by the server.
     */
    key = 5555;

    /*
     * Locate the segment.
     */
    if ((shmid = shmget(key, SHMSZ, 0666)) < 0) {
        perror("shmget");
        return 1;
    }

    /*
     * Now we attach the segment to our data space.
     */
    if ((shm = shmat(shmid, NULL, 0)) == (char *) -1) {
        perror("shmat");
        return 1;
    }

    /*
     * Now read what the server put in the memory.
     */
    for (s = shm; *s != NULL; s++)
	{
        putchar(*s);  //he C library function int putchar(int char) writes a 
                       // character (an unsigned char) specified by the argument char to stdout.
        /*Parameters
char -- This is the character to be written. This is passed as its int promotion.

Return Value
This function returns the character written as an unsigned char cast to an int or EOF on error.*/
	}
    putchar('\n');

    /*
     * Finally, change the first character of the 
     * segment to '*', indicating we have read 
     * the segment.
     */
    *shm = '*';

    return 0;
}

/*  output.....

pccoe@DMSA-19:~$ cd Desktop
pccoe@DMSA-19:~/Desktop$ gcc process_c.c -o process_c
pccoe@DMSA-19:~/Desktop$ ./process_c
625

*/

