%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "y.tab.h"
int line_number = 1;
%}

%option noyywrap
%option noinput
%option nounput
FloatConstant      ([0-9]*\.?[0-9]+([eE][+-]?[0-9]+)?)|([0-9]+[eE][+-]?[0-9]+)
IntConstant        [0-9]+
%%
[ \t\r]                     { /* Ignore whitespaces */ }
\n                          { line_number++; }
"/*"([^*]|"*"+[^*/])*"*"+"/"  {
                              for (int i = 0; yytext[i]; i++)
                                if (yytext[i] == '\n')
                                  line_number++;
                            }
"//"[^\n]*                  { /* Skip one-line comments */ }
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
{IntConstant}                 {
                            yylval.ival = atoi(yytext);
                            return INT_CONST;
                            }
{FloatConstant}               {
                            yylval.fval = atof(yytext);
                            return FLOAT_CONST;
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
.                          { printf("Lexical error due to unknown token %s\n", yytext); }
