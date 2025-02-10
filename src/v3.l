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
%}

%%

"int"|"char"|"if"|"else"|"while"|"for"|"main"|"begin"|"end"|"print"|"scan"|"program"|"VarDecl"|"inc"|"dec" { printf("KEYWORD: %s\n", yytext); }

[a-z][a-z0-9_]* { 
    int underscore_count = 0;
    for (int i = 0; yytext[i] != '\0'; i++) {
        if (yytext[i] == '_') underscore_count++;
        if (underscore_count > 1) {
            printf("INVALID IDENTIFIER: %s\n", yytext);
            return 0;
        }
    }
    printf("IDENTIFIER: %s\n", yytext); 
}

\/\/.*                 { printf("COMMENT: %s\n", yytext); }

0b[01]+                { printf("BINARY CONSTANT: %s (base 2)\n", yytext); }
0[0-7]+                { printf("OCTAL CONSTANT: %s (base 8)\n", yytext); }
[1-9][0-9]*            { printf("DECIMAL CONSTANT: %s (base 10)\n", yytext); }

'[^']'                 { printf("CHARACTER CONSTANT: %s\n", yytext); }

\"[^\"]*\"             { process_string(yytext + 1); } // Remove first and last quotes

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