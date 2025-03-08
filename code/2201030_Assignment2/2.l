%{
FILE *txtfile; 
%}

%% 

\/\/(.*)                                        ; 
"/**"([^*]|[\r\n]|(\*+([^*/]|[\r\n])))*\*+\/    { fputs(yytext, txtfile); fputc('\n', txtfile); }
"/*"([^*]|[\r\n]|(\*+([^*/]|[\r\n])))*\*+\/     ;

%%

int main(int argc, char *argv[]) {
    if (argc > 1) {
        FILE *file = fopen(argv[1], "r");
        txtfile = fopen("documentation.txt", "w"); 
        if (file && txtfile) {
            yyin = file; 
            yyout = fopen("OutputFile2.java", "w"); 
            yylex();
            fclose(file);
            fclose(txtfile);
            if (yyout) fclose(yyout); 
        } else {
            fprintf(stderr, "Error opening input or output file.\n");
            if (file) fclose(file);
            if (txtfile) fclose(txtfile);
            return 1;
        }
    } else {
        fprintf(stderr, "Usage: %s <input-file>.java\n", argv[0]);
        return 1;
    }
    return 0;
}

int yywrap() {                                      
    return 1;
}
