%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "y.tab.h"

int line_num = 1;
%}

%option noyywrap
%option noinput
%option nounput

FloatConst      ([0-9]*\.?[0-9]+([eE][+-]?[0-9]+)?)|([0-9]+[eE][+-]?[0-9]+)

IntConst        [0-9]+

%%
[ \t\r]                     { /* Ignore whitespace */ }
\n                          { line_num++; }
"/*"([^*]|"*"+[^*/])*"*"+"/"  { 
                              /* Count newlines in comments */
                              for (int i = 0; yytext[i]; i++) 
                                if (yytext[i] == '\n') 
                                  line_num++; 
                            }
"//"[^\n]*                  { /* Skip single-line comments */ }

"int"                       { return INT; }
"float"                     { return FLOAT; }
"char"                      { return CHAR; }
"void"                      { return VOID; }
"if"                        { return IF; }
"else"                      { return ELSE; }
"while"                     { return WHILE; }
"for"                       { return FOR; }
"return"                    { return RETURN; }

[a-zA-Z_][a-zA-Z0-9_]*     {
                              yylval.str = strdup(yytext);
                              return ID;
                            }

{FloatConst}               { 
                            yylval.fval = atof(yytext); 
                            return FLOAT_CONST; 
                            }

{IntConst}                 { 
                            yylval.ival = atoi(yytext); 
                            return INT_CONST; 
                            }

\"[^\"]*\"                 {
                              yylval.str = strdup(yytext);
                              return STRING;
                            }

\'[^\']\'                  {
                              yylval.str = strdup(yytext);
                              return CHAR_CONST;
                            }

"+"                        { return PLUS; }
"-"                        { return MINUS; }
"*"                        { return MULT; }
"/"                        { return DIV; }
"%"                        { return MOD; }
"="                        { return ASSIGN; }
"+="                       { return PLUS_ASSIGN; }
"-="                       { return MINUS_ASSIGN; }
"*="                       { return MULT_ASSIGN; }
"/="                       { return DIV_ASSIGN; }
"%="                       { return MOD_ASSIGN; }
"++"                       { return INC; }
"--"                       { return DEC; }
"=="                       { return EQ; }
"!="                       { return NEQ; }
">"                        { return GT; }
"<"                        { return LT; }
">="                       { return GTE; }
"<="                       { return LTE; }
"&&"                       { return AND; }
"||"                       { return OR; }
"!"                        { return NOT; }
"&"                        { return ADDR; }
"("                        { return LPAREN; }
")"                        { return RPAREN; }
"{"                        { return LBRACE; }
"}"                        { return RBRACE; }
"["                        { return LSQUARE; }
"]"                        { return RSQUARE; }
";"                        { return SEMI; }
","                        { return COMMA; }

.                          { printf("Lexical error on line %d: Unknown token %s\n", line_num, yytext); }

%%