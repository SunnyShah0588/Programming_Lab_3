%define parse.error verbose
%define api.pure true
%locations
%token-table
%glr-parser
%lex-param {void *scanner}
%parse-param {void *scanner}

%{
/* your top code here */
#include<omp.h>
int t;
%}
%union
{
  int value;
}
%token <value> NUM
%token N
%left '+' '-'
%left '*' '/'
%type <value> expr
%%

stmt :%empty
   	  | stmt expr N {printf("\n Successful parsing by thread ID=%d\t Result of expression= %d\n",omp_get_thread_num(),$2); } 
;

expr
    : expr '+' expr  { $$ = $1+$3 ;}
    | expr '-' expr  { $$ = $1-$3 ;}
    |expr '*' expr  { $$ = $1*$3 ;}
    |expr '/' expr  { $$ = $1/$3 ;}
    |NUM {$$=$1;}
    ;


%%

int yyerror() {
    
}
