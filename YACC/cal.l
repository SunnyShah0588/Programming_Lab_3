%option reentrant
%option bison-bridge
%option noyywrap
%option bison-locations
%{
  #include "parser.h"

%}

%%
[0-9]+	{sscanf(yytext, "%d", &yylval->value); return NUM;}
[-+*/]	{return yytext[0];}
\n {return(N);}
.|[ \t]+   { }
%%

