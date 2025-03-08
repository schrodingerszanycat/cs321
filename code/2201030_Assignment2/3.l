%{ 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct TagNode {
    char tag[100];
    int count;
    struct TagNode* next;
} TagNode;

TagNode* tagListHead = NULL;

void normalizeTag(char* tag) {
    int i;
    for (i = 0; tag[i] != '\0'; i++) {
        tag[i] = tag[i + 1]; 
    }
    tag[i - 2] = '\0';

    if (tag[0] == '/') {
        for (int i = 0; tag[i] != '\0'; i++) {
            tag[i] = tag[i + 1];
        }
    }
}

void pushTag(const char* tag) {
    TagNode* current = tagListHead;
    while (current != NULL) {
        if (strcmp(current->tag, tag) == 0) {
            current->count++;
            return;
        }
        current = current->next;
    }
    TagNode* newNode = (TagNode*) malloc(sizeof(TagNode));
    strcpy(newNode->tag, tag);
    newNode->count = 1;
    newNode->next = tagListHead;
    tagListHead = newNode;
}

void printTags() {
    TagNode* current = tagListHead;
    while (current != NULL) {
        printf("%s: %d\n", current->tag, current->count);
        TagNode* temp = current;
        current = current->next;
        free(temp);
    }
}
%} 

%% 

"<"[^>]*">"         {
                        char tag[100];
                        strncpy(tag, yytext, sizeof(tag));
                        tag[sizeof(tag) - 1] = '\0';
                        normalizeTag(tag);
                        pushTag(tag);
                    }
[ \t\r\n]+          ;
(.)                 ;  

%%     

int main(int argc, char* argv[]) 
{ 
    if (argc > 1) {
        FILE *file = fopen(argv[1], "r");
        if (file) {
            yyin = file; 
            yylex();
            fclose(file);
            printTags();
        } else {
            fprintf(stderr, "Error opening file %s\n", argv[1]);
            return 1;
        }
    } else {
        fprintf(stderr, "Usage: %s <input-file>\n", argv[0]);
        return 1;
    }
    return 0;
} 

int yywrap(){
    return 1;
}


