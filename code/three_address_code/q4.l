%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "q4.tab.h"

extern int yylineno;

extern void yyerror(char* s);

%}

%option noyywrap case-insensitive

DIGIT    [0-9]
ID       [a-zA-Z_][a-zA-Z0-9_]*

%%

[ \t]+
\n              { yylineno++; }
"//".*
"/*"            {
                  int c;
                  while((c = input()) != 0) {
                    if(c == '*') {
                      if((c = input()) == '/') break;
                      else unput(c);
                    } else if (c == '\n') {
                      yylineno++;
                    }
                  }
                  if (c == 0) yyerror("Unterminated block comment");
                }

"if"            { return IF; }
"else"          { return ELSE; }
"while"         { return WHILE; }
"int"           { return INT; }
"float"         { return FLOAT; }
"void"          { return VOID; }
"return"        { return RETURN; }

"{"             { return '{'; }
"}"             { return '}'; }
"("             { return '('; }
")"             { return ')'; }
";"             { return ';'; }
"+"             { return '+'; }
"-"             { return '-'; }
"*"             { return '*'; }
"/"             { return '/'; }
"%"             { return '%'; }
"="             { return '='; }
"=="            { return EQ; }
"!="            { return NE; }
"<"             { return LT; }
">"             { return GT; }
"<="            { return LE; }
">="            { return GE; }
"&&"            { return AND; }
"||"            { return OR; }
","             { return ','; }

{DIGIT}+        {
                  yylval.num = atoi(yytext);
                  return NUMBER;
                }

{DIGIT}+\.{DIGIT}+ {
                  yylval.fnum = atof(yytext);
                  return FLOAT_NUM;
                 }

{ID}            {
                  yylval.id = strdup(yytext);
                  if (!yylval.id) { yyerror("Memory allocation failed for ID"); exit(1); }
                  return ID;
                }

.               {
                  char msg[100];
                  sprintf(msg, "Unknown character '%s'", yytext);
                  yyerror(msg);
                }

%%