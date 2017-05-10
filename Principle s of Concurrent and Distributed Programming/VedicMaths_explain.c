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
    key_t key;  /*Unix requires a key of type key_t defined in file sys/types.h for
              requesting resources such as shared memory segments, message queues and semaphores.
               A key is simply an integer of type key_t; however, you should not use int or long,
                since the length of a key is system dependent.

There are three different ways of using keys, namely:

a specific integer value (e.g., 123456)
a key generated with function ftok()
a uniquely generated key using IPC_PRIVATE (i.e., a private key).
The first way is the easiest one; however, its use may be very risky since a process can 
access your resource as long as it uses the same key value to request that resource. The
 following example assigns 1234 to a key:

 key_t     SomeKey;

SomeKey = 1234;*/

    char *shm, *s;
    int i=0;
    int NumberToBeSquared;
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
     shmget() is used to obtain access to a shared memory segment. It is prottyped by:

int shmget(key_t key, size_t size, int shmflg);
The key argument is a access value associated with the semaphore ID. 
The size argument is the size in bytes of the requested shared memory.
 The shmflg argument specifies the initial access permissions and creation control flags.

When the call succeeds, it returns the shared memory segment ID.
 This call is also used to get the ID of an existing shared segment 
(from a process requesting sharing of some existing memory portion).

IPC_CREAT
Create the segment if it doesn't already exist in the kernel.

IPC_EXCL
When used with IPC_CREAT, fail if segment already exists.

If IPC_CREAT is used alone, shmget() either returns the segment identifier for a 
newly created segment, or returns the identifier for a segment which exists with the same key value.
 If IPC_EXCL is used along with IPC_CREAT, then either a new segment is created, 
 or if the segment exists, the call fails with -1. IPC_EXCL is useless by itself,
  but when combined with IPC_CREAT, it can be used as a facility to guarantee that
   no existing segment is opened for access.

   Read 4 - Allowed to read files
Write 2 - Allowed to write/modify files
eXecute1 - Read/write/delete/modify/directory

0666    -rw-rw-rw-  all have rw only (6)
     */
    if((shmid = shmget(key, SHMSZ, IPC_CREAT | 0666)) < 0)
    {
        perror("shmget");  //The C library function void perror(const char *str) prints 
                          //a descriptive error message to stderr. 
                         ///First the string str is printed, followed by a colon then a space.

        return 1;
    }

    /*
     * Now we attach the segment to our data space.

     #include <sys/types.h>#include <sys/shm.h>void *shmat(int shmid, const void *shmaddr,
int shmflg);int shmdt(const void *shmaddr);

shmat() attaches the shared memory segment identified by shmid to the 
address space of the calling process. The attaching address is specified
 by shmaddr with one of the following criteria:
If shmaddr is NULL, the system chooses a suitable (unused) 
address at which to attach the segment.

If shmaddr isn't NULL and SHM_RND is specified in shmflg, the attach 
occurs at the address equal to shmaddr rounded down to the nearest multiple 
of SHMLBA. Otherwise shmaddr must be a page-aligned address at which the attach occurs.

If SHM_RDONLY is specified in shmflg, the segment is attached for reading
 and the process must have read permission for the segment. Otherwise the
  segment is attached for read and write and the process must have read and
   write permission for the segment. There is no notion of a write-only 
   shared memory segment.
   
   On success shmat() returns the address of the attached shared memory segment;
    on error (void *) -1 is returned, and errno is set to indicate the cause of the error.
On success shmdt() returns 0; on error -1 is returned, and errno is se
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
    scanf("%d",&NumberToBeSquared);

    r=NumberToBeSquared%10;
    l=(NumberToBeSquared/10)%10;

    sr=r*r;
    sl=l*l;

    ans = (sl*100+sr)+(r*l*2*10);
    sprintf(buff,"%d",ans); //The C library function int sprintf(char *str, const char *format, ...)
                             // sends formatted output to a string pointed to, by str.

                       /*str − This is the pointer to an array of char elements where the resulting C string is stored.

format − This is the String that contains the text to be written to buffer. 
It can optionally contain embedded format tags that are replaced by the values
 specified in subsequent additional arguments and formatted as requested.
  Format tags prototype: %[flags][width][.precision][length]specifier, as explained below */


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





