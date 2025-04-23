%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "for3Add1.tab.h"

void yyerror(char *s);
%}

%option yylineno

%%
"if"        { return IF; }
"else"      { return ELSE; }
"while"     { return WHILE; }
"for"       { return FOR; }
"switch"    { return SWITCH; }
"case"      { return CASE; }
"default"   { return DEFAULT; }
"break"     { return BREAK; }
"continue"  { return CONTINUE; }
"int"       { return INT; }
"float"     { return FLOAT; }
"void"      { return VOID; }
"return"    { return RETURN; }
"=="        { return EQ; }
"!="        { return NE; }
"<="        { return LE; }
">="        { return GE; }
"<"         { return LT; }
">"         { return GT; }
"&&"        { return AND; }
"||"        { return OR; }
[0-9]+      { yylval.num = atoi(yytext); return NUMBER; }
[0-9]+\.[0-9]+ { yylval.fnum = atof(yytext); return FLOAT_NUM; }
[a-zA-Z][a-zA-Z0-9_]* {
    yylval.id = strdup(yytext);
    if (!yylval.id) {
        yyerror("Memory allocation error");
        exit(1);
    }
    return ID;
}
[ \t\n]     ;  /* Skip whitespace */
.           { return yytext[0]; }
%%

int yywrap() {
    return 1;
}