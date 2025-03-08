%{ 
%}

%% 

\/\/(.*)                                        ; 
"/*"([^*]|[\r\n]|(\*+([^*/]|[\r\n])))*\*+\/     ;

%%

int main(int argc, char *argv[]) {
    if (argc > 1) {
        FILE *file = fopen(argv[1], "r");
        if (file) {
            yyin = file; 
            yyout=fopen("OutputFile1.java","w"); 
            yylex();
            fclose(file);
        } else {
            fprintf(stderr, "Error opening file %s\n", argv[1]);
            return 1;
        }
    } else {
        fprintf(stderr, "Usage: %s <input-file>.java\n", argv[0]);
        return 1;
    }
}

int yywrap() {                                        
    return 1;
}