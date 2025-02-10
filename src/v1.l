%{
    #include <stdio.h>
    %}
    
    %%
    
    "int"|"char"|"if"|"else"|"while"|"for"|"main"|"begin"|"end"|"print"|"scan"|"program"|"VarDecl"|"inc"|"dec" { printf("KEYWORD: %s\n", yytext); }
    
    [a-z][a-z0-9_]*    { printf("IDENTIFIER: %s\n", yytext); }
    \/\/.*               { printf("COMMENT: %s\n" , yytext); }
    [0-9]+             { printf("DECIMAL CONSTANT: %s\n", yytext); }
    0[0-7]+            { printf("OCTAL CONSTANT: %s\n", yytext); }
    0b[01]+            { printf("BINARY CONSTANT: %s\n", yytext); }
    
    '[^']'             { printf("CHARACTER CONSTANT: %s\n", yytext); }
    \"[^\"]*\"         { printf("STRING CONSTANT: %s\n", yytext); }
    "@"		   { printf("SEPARATOR: %s\n", yytext); }
    "+"|"-"|"*"|"/"|"%" { printf("ARITHMETIC OPERATOR: %s\n", yytext); }
    "="|">"|"<"|">="|"<="|"<>" { printf("RELATIONAL OPERATOR: %s\n", yytext); }
    ":="|"+="|"-="|"*="|"/="|"%=" { printf("ASSIGNMENT OPERATOR: %s\n", yytext); }
    
    "("|")"|","|";"|"{"|"}"|":"|"\"" 
    
    [ \t\n]+           ; // ignoring whitespace
    
    .                  { printf("UNKNOWN TOKEN: %s\n", yytext); }
    
    %%
    
    int main(int argc, char **argv) {
        yylex();
        return 0;
    }