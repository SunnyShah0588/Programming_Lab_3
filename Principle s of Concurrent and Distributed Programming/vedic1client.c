#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#define SHMSZ 25

int main()
{
int shmid;
key_t key;
char *shm, *s;
key = 5678;
if ((shmid = shmget(key, SHMSZ, 0666)) < 0) {
perror("shmget");
return 1;
}
if ((shm = shmat(shmid, NULL, 0)) == (char *) -1) {
perror("shmat");
return 1;
}
int i,n1;
char n;
s=shm;
printf("Enter a 2 digit number : ");
scanf("%2d",&n1);
n=(char)n1;
s++;
*s=n;
*shm='*';
while (*shm != '%')
sleep(1);
s=shm;
s++;
for (i=0; s != NULL && i<4;i++){
printf("%c",*s);
s++;
}
putchar('\n');
*shm = '$';
return 0;
}

