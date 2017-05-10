#include "parser.h"
#include "lexer.h"
//to read filenames for parsing
struct fname
{
  char fn[10];
};

//to store temp. result of scanner
 struct pwc {
   char op[20];
 };


int main(int argc, char **argv) {
  int result,n,i;
  struct fname file[10];
  struct pwc mypwc;
  yyscan_t scanner;  
  FILE *f;
  yylex_init(&scanner);
  printf("\n Enter no. of files: ");
  scanf("%d",&n);
  printf("\n Enter file names: ");
  for(i=0;i<n;i++)
  {
    scanf("%s",file[i].fn);
  }
  printf("\n");
	#pragma omp parallel num_threads(n) shared(file) private(f,scanner,result,mypwc) 
 		{		
			if(yylex_init_extra(&mypwc, &scanner)) 
			{
					perror("init alloc failed");
					//return 1;
			}				
			
			int tid=omp_get_thread_num();
			f=fopen(file[tid].fn,"r");
			yyset_in(f,scanner);
			 result = (yyparse(scanner));
			 yylex_destroy(scanner);
									
		}
printf("\n Parsing Completed\n");
sleep(10);
return 0;
}

/*
flex --header-file=lexer.h lex1.l
bison --defines=parser.h pars.y
cc lexer.c parser.c main.c -o parser
./parser

**/
