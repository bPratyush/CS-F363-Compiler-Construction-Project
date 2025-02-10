%{
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void process_string(const char *text) {
    int len = strlen(text);
    int i = 0, start = 0;
    
    while (i < len) {
        if (text[i] == '@') {
            if (i > start) {
                printf("STRING CONSTANT: \"%.*s\"\n", i - start, text + start);
            }
            printf("SEPARATOR: @\n");
            start = i + 1;
        }
        i++;
    }
    
    if (start < len) {
        printf("STRING CONSTANT: \"%s\"\n", text + start);
    }
}

int validate_binary(const char *text) {
    for (int i = 0; text[i] != ','; i++) {
        if (text[i] != '0' && text[i] != '1') {
            printf("INVALID BINARY CONSTANT: %s\n", text);
            return 0;
        }
    }
    return 1;
}

int validate_octal(const char *text) {
    for (int i = 0; text[i] != ','; i++) {
        if (text[i] < '0' || text[i] > '7') {
            printf("INVALID OCTAL CONSTANT: %s\n", text);
            return 0;
        }
    }
    return 1;
}

int validate_base_format(const char *text) {
    if (strchr(text, ',') == NULL) {
        printf("INVALID INTEGER CONSTANT: Missing base in %s\n", text);
        return 0;
    }
    return 1;
}

int validate_identifier(const char *text) {
    int underscore_count = 0;
    for (int i = 0; text[i] != '\0'; i++) {
        if (text[i] == '_') underscore_count++;
        if (underscore_count > 1) {
            printf("INVALID IDENTIFIER: %s\n", text);
            return 0;
        }
    }
    return 1;
}
%}

%%

"int"|"char"|"if"|"else"|"while"|"for"|"main"|"begin"|"end"|"print"|"scan"|"program"|"VarDecl"|"inc"|"dec" { printf("KEYWORD: %s\n", yytext); }

[a-z][a-z0-9_]* { 
    if (validate_identifier(yytext)) {
        printf("IDENTIFIER: %s\n", yytext);
    }
}

\/\/.*                 { printf("COMMENT: %s\n", yytext); }

([0-9]+,[ \t]+2) {
    if (validate_binary(yytext)) {
        printf("BINARY INTEGER CONSTANT: (%.*s, 2)\n", 
               (int)(strchr(yytext, ',') - yytext), yytext);
    }
}

([0-9]+,[ \t]+8) {
    if (validate_octal(yytext)) {
        printf("OCTAL INTEGER CONSTANT: (%.*s, 8)\n", 
               (int)(strchr(yytext, ',') - yytext), yytext);
    }
}

([0-9]+,[ \t]+10) {
    if (validate_base_format(yytext)) {
        printf("DECIMAL INTEGER CONSTANT: (%.*s, 10)\n", 
               (int)(strchr(yytext, ',') - yytext), yytext);
    }
}

([0-9]+) { 
    printf("INVALID INTEGER CONSTANT: Missing base in %s\n", yytext); 
}

'(\\.|[^\\'])' { printf("CHARACTER CONSTANT: %s\n", yytext); }

\"[^\"]*\"             { process_string(yytext + 1); }

"@"                    { printf("SEPARATOR: %s\n", yytext); }

"+"|"-"|"*"|"/"|"%"    { printf("ARITHMETIC OPERATOR: %s\n", yytext); }
"="|">"|"<"|">="|"<="|"<>" { printf("RELATIONAL OPERATOR: %s\n", yytext); }
":="|"+="|"-="|"*="|"/="|"%=" { printf("ASSIGNMENT OPERATOR: %s\n", yytext); }

"("|")"|","|";"|"{"|"}"|":"  { printf("SEPARATOR: %s\n", yytext); }

[ \t\n]+               ; // ignoring whitespace

.                      { printf("UNKNOWN TOKEN: %s\n", yytext); }

%%

int main(int argc, char **argv) {
    yylex();
    return 0;
}