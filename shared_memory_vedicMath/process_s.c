#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define SHMSZ     27

int main()
{
    char c;
    int shmid;
    key_t key;
    char *shm, *s;
    int i=0;
    int n;
    int r,l;
    int sr,sl,ans;
    char buff[100];

    /*
     * We'll name our shared memory segment
     * "5678".
     */
    key = 5555;

    /*
     * Create the segment.
     */
    if((shmid = shmget(key, SHMSZ, IPC_CREAT | 0666)) < 0)
    {
        perror("shmget");
        return 1;
    }

    /*
     * Now we attach the segment to our data space.
     */
    if ((shm = shmat(shmid, NULL, 0)) == (char *) -1) 
    {
        perror("shmat");
        return 1;
    }

    /*
     * Now put some things into the memory for the
     * other process to read.
     */
    s = shm;

    printf("Enter Number:");
    scanf("%d",&n);

    r=n%10;
    l=(n/10)%10;

    sr=r*r;
    sl=l*l;

    ans = (sl*100+sr)+(r*l*2*10);
    sprintf(buff,"%d",ans);

    while(buff[i]!='\0')
    {	
        *s++ = buff[i];
	     i++;
    }

    printf("\n");
	

    *s = 0;

    /*
     * Finally, we wait until the other process 
     * changes the first character of our memory
     * to '*', indicating that it has read what 
     * we put there.
     */
    while (*shm != '*')
        sleep(1);

    return 0;
}


/* output...........

pccoe@DMSA-19:~$ cd Desktop
pccoe@DMSA-19:~/Desktop$ gcc process_s.c -o process_s
pccoe@DMSA-19:~/Desktop$ ./process_s 

Enter Number:25

*/





