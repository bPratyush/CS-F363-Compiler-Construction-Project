%{
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_COMMENT_SIZE 2048
static char comment_buffer[MAX_COMMENT_SIZE];
static int comment_index = 0;

static char print_string[1024];
static char print_args[1024];
static int print_state_string_captured = 0;
static int at_count = 0;
static int arg_count = 0;
static int parentheses_count = 0;

static char* symbolTable[256];
static int symbolCount = 0;

int while_parantheses_count = 0;
    char while_condition_buffer[1024];
    int while_condition_index = 0;

int isDeclared(const char* id) {
    int i;
    for(i = 0; i < symbolCount; i++){
        if(strcmp(symbolTable[i], id) == 0) return 1;
    }
    return 0;
}

void reset_print_buffers() {
    memset(print_string, 0, sizeof(print_string));
    memset(print_args, 0, sizeof(print_args));
    print_state_string_captured = 0;
    at_count = 0;
    arg_count = 0;
    parentheses_count = 0;
}

void reset_while_stats(){
        memset(while_condition_buffer, 0, sizeof(while_condition_buffer));
        while_parantheses_count = 0;

    }

void count_at_symbols(const char* s) {
    int i;
    for (i = 0; s[i]; i++) {
        if (s[i] == '@') at_count++;
    }
}

void finalize_print_statement() {
    if (!print_state_string_captured) {
        printf("INVALID PRINT STATEMENT: Missing string.\n");
        return;
    }
    if (at_count != arg_count) {
        printf("INVALID PRINT STATEMENT: @ count (%d) != argument count (%d).\n", at_count, arg_count);
        return;
    }
    printf("VALID PRINT STATEMENT: %s\n", print_string);
}

int validate_identifier(const char *text) {
    const char *keywords[] = {
        "int","char","if","else","while","for","main","begin","end",
        "print","scan","program","VarDecl","inc","dec", NULL
    };
    int i;
    for (i = 0; keywords[i] != NULL; i++) {
        if (strcmp(text, keywords[i]) == 0) return 0;
    }
    if (text[0] < 'a' || text[0] > 'z') return 0;
    {
        int underscore = 0;
        int j;
        for (j = 0; text[j] != '\0'; j++) {
            char c = text[j];
            if (c == '_') {
                underscore++;
                if (underscore > 1) return 0;
            } else if (!(c >= 'a' && c <= 'z') && !(c >= '0' && c <= '9')) {
                return 0;
            }
        }
    }
    return 1;
}

int validate_char_const(const char *text) {
    int len = strlen(text);
    if (text[0] == '\'' && text[len - 1] == '\'') {
        if (text[1] == '\\' && len == 4) return 1;
        else if (text[1] != '\\' && len == 3) return 1;
    }
    return 0;
}

int validate_decimal(const char *text) {
    int i;
    for (i = 0; text[i] != '\0'; i++) {
        if (text[i] < '0' || text[i] > '9') return 0;
    }
    return 1;
}

int validate_octal(const char *text) {
    int i;
    for (i = 0; text[i] != '\0'; i++) {
        if (text[i] < '0' || text[i] > '7') return 0;
    }
    return 1;
}

int validate_binary(const char *text) {
    int i;
    for (i = 0; text[i] != '\0'; i++) {
        if (text[i] != '0' && text[i] != '1') return 0;
    }
    return 1;
}

int validate_array_identifier(const char *text) {
    const char *keywords[] = {
        "int","char","if","else","while","for","main","begin","end",
        "print","scan","program","VarDecl","inc","dec", NULL
    };
    int i;
    for (i = 0; keywords[i] != NULL; i++) {
        if (strcmp(text, keywords[i]) == 0) return 0;
    }
    if (!((text[0] >= 'a' && text[0] <= 'z') || (text[0] >= 'A' && text[0] <= 'Z'))) return 0;
    {
        int underscore = 0;
        int j;
        for (j = 0; text[j] != '\0'; j++) {
            char c = text[j];
            if (c == '_') {
                underscore++;
                if (underscore > 1) return 0;
            } else if (!((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9'))) {
                return 0;
            }
        }
    }
    return 1;
}

int validate_relational_expression(char * condition){
        char id1[256],op[3],id2[256];
        if(sscanf(condition,"%s %s %s",id1,op,id2)==3){
            if(!validate_identifier(id1) || !validate_identifier(id2)){
                return 0;
            }
            if(!(strcmp(op,"=")||strcmp(op,"<>")||strcmp(op,">")||strcmp(op,"<")||strcmp(op,">=")||strcmp(op,"<="))){
                return 0;
            }
            return 1;
        }
        else if(sscanf(condition,"%s",id1)==1){
            return validate_identifier(id1);
        }
        return 0;
    }

void check_while_condition(){
        while_condition_buffer[while_condition_index] = '\0';
        if(validate_relational_expression(while_condition_buffer)){
            printf("VALID CONDITION IN WHILE LOOP\n");
        }
        else{
            printf("INVALID CONDITION IN WHILE LOOP\n");
        }
}
%}

%x VARDECL
%x NUMRELATIONS
%x COMMENT
%x PRINT
%x WHILE
%x CONDITION
%%

"begin"[ \t]+"VarDecl:"   { BEGIN(VARDECL); printf("BEGIN VARIABLE DECLARATION\n"); }

<VARDECL>"end"[ \t]+"VarDecl"[ \t]*\n? {
    BEGIN(INITIAL);
    printf("END VARIABLE DECLARATION\n");
}

<VARDECL>[ \t]*\([ \t]*[a-zA-Z][a-z0-9_]*[ \t]*(\[[ \t]*[0-9]+\s*\])?[ \t]*,[ \t]*(int|char)[ \t]*\)[ \t]*;[ \t]*(\/\/.*)?[ \t]*\n {
    char lineCopy[1024];
    strncpy(lineCopy, yytext, 1023);
    lineCopy[1023] = '\0';
    {
        char *commentStart = strstr(lineCopy, "//");
        if(commentStart) {
            printf("COMMENT: %s\n", commentStart);
            *commentStart = '\0';
        }
    }
    if (strchr(lineCopy, '[')) {
        char id[64], typ[16];
        int size;
        if (sscanf(lineCopy, " ( %63[^[]%*c%d%*c , %15[^)] ) ;", id, &size, typ) == 3) {
            char *nl = strpbrk(typ, " \t");
            if (nl) *nl = '\0';
            if (size > 0 && validate_array_identifier(id))
                printf("VALID ARRAY DECLARATION: (%s[%d], %s)\n", id, size, typ);
            else
                printf("INVALID ARRAY DECLARATION: %s\n", yytext);
        } else {
            printf("INVALID ARRAY DECLARATION: %s\n", yytext);
        }
    } else {
        char id[64], typ[16];
        if (sscanf(lineCopy, " ( %63[^,] , %15[^)] ) ;", id, typ) == 2) {
            char *nl = strpbrk(typ, " \t");
            if(nl) *nl = '\0';
            if (validate_identifier(id))
                printf("VALID VARIABLE DECLARATION: (%s, %s)\n", id, typ);
            else
                printf("INVALID VARIABLE DECLARATION: %s\n", yytext);
        } else {
            printf("INVALID VARIABLE DECLARATION: %s\n", yytext);
        }
    }
}

<VARDECL>"//".* {
    printf("COMMENT: %s\n", yytext);
}

<VARDECL>[ \t]*\n {
}

<VARDECL>.*\n {
    printf("INVALID VARIABLE DECLARATION: %s", yytext);
}

"int"|"char"|"if"|"else"|"for"|"main"|"begin"|"end"|"program"|"VarDecl"|"inc"|"dec" {
    printf("KEYWORD: %s\n", yytext);
}

"print" {
    printf("KEYWORD: %s\n", yytext);
    reset_print_buffers();
    BEGIN(PRINT);
}

"scan" {
    printf("KEYWORD: %s\n", yytext);
}
"while" {
    printf("KEYWORD: %s\n",yytext);
    BEGIN(WHILE);
}
[a-z][a-z0-9_]* {
    if (validate_identifier(yytext)) {
        if (isDeclared(yytext)) printf("IDENTIFIER: %s\n", yytext);
        else printf("UNDEFINED IDENTIFIER: %s\n", yytext);
    }
}

"//".* {
    printf("COMMENT: %s\n", yytext);
}

"/*" {
    BEGIN(COMMENT);
    comment_index = 0;
    comment_buffer[0] = '\0';
}

<COMMENT>"*/" {
    printf("COMMENT (multiline): /*%s*/\n", comment_buffer);
    BEGIN(INITIAL);
}

<COMMENT>"\n" {
    if(comment_index < MAX_COMMENT_SIZE - 1) {
        comment_buffer[comment_index++] = '\n';
        comment_buffer[comment_index] = '\0';
    }
}

<COMMENT>. {
    if(comment_index < MAX_COMMENT_SIZE - 1) {
        comment_buffer[comment_index++] = yytext[0];
        comment_buffer[comment_index] = '\0';
    }
}

\([ \t]*[0-9]+[ \t]*,[ \t]*2[ \t]*\) {
    char tmp[128];
    char *start = yytext + 1;
    while (*start == ' ' || *start == '\t') start++;
    {
        int value_len = (int)(strchr(yytext, ',') - start);
        strncpy(tmp, start, value_len);
        tmp[value_len] = '\0';
    }
    if (validate_binary(tmp)) printf("BINARY INTEGER CONSTANT: (%s, 2)\n", tmp);
    else printf("INVALID BINARY CONSTANT: %s\n", yytext);
}

\([ \t]*[0-9]+[ \t]*,[ \t]*8[ \t]*\) {
    char tmp[128];
    char *start = yytext + 1;
    while (*start == ' ' || *start == '\t') start++;
    {
        int value_len = (int)(strchr(yytext, ',') - start);
        strncpy(tmp, start, value_len);
        tmp[value_len] = '\0';
    }
    if (validate_octal(tmp))
        printf("OCTAL INTEGER CONSTANT: (%s, 8)\n", tmp);
    else
        printf("INVALID OCTAL CONSTANT: %s\n", yytext);
}

\([ \t]*[0-9]+[ \t]*,[ \t]*10[ \t]*\) {
    char tmp[128];
    char *start = yytext + 1;
    while (*start == ' ' || *start == '\t') start++;
    {
        int value_len = (int)(strchr(yytext, ',') - start);
        strncpy(tmp, start, value_len);
        tmp[value_len] = '\0';
    }
    if (validate_decimal(tmp)) printf("DECIMAL INTEGER CONSTANT: (%s, 10)\n", tmp);
    else printf("INVALID DECIMAL CONSTANT: %s\n", yytext);
}

([0-9]+) {
    printf("INVALID INTEGER CONSTANT: Missing base in %s\n", yytext);
}

'([^']|\\.)+' {
    if (validate_char_const(yytext)) printf("CHARACTER CONSTANT: %s\n", yytext);
    else printf("INVALID CHARACTER CONSTANT: %s\n", yytext);
}

<PRINT>"(" { parentheses_count++; }

<PRINT>\"[^\"]*\" {
    if(!print_state_string_captured) {
        strncpy(print_string, yytext, sizeof(print_string)-1);
        count_at_symbols(yytext);
        print_state_string_captured = 1;
    }
}

<PRINT>"," {
}

<PRINT>\([ \t]*[0-9]+[ \t]*,[ \t]*(2|8|10)[ \t]*\) {
    arg_count++;
}

<PRINT>\'([^']|\\.)+\' {
    arg_count++;
}

<PRINT>[a-z][a-z0-9_]* {
    arg_count++;
}

<PRINT>")" {
    if (parentheses_count > 0) parentheses_count--;
    else printf("INVALID PRINT STATEMENT: Unmatched closing parenthesis.\n");
}

<PRINT>";" {
    if (parentheses_count != 0) printf("INVALID PRINT STATEMENT: Parentheses not closed.\n");
    else finalize_print_statement();
    BEGIN(INITIAL);
}

<PRINT>\n {
    if (parentheses_count != 0) printf("INVALID PRINT STATEMENT: Missing closing parenthesis and semicolon.\n");
    else printf("INVALID PRINT STATEMENT: Missing semicolon.\n");
    reset_print_buffers();
    BEGIN(INITIAL);
}

<WHILE>"(" {
 reset_while_stats();
 while_parantheses_count++;
 BEGIN(CONDITION);
}
<CONDITION>[\s]*[a-z][a-z0-9]*[\s]*((<|>|<=|>=|<>)[\s]*(([a-z][a-z0-9]*)|[0-9]*)[\s]*)? {
    printf("VALID CONDITION IDENTIFIED INSIDE WHILE LOOP: %s\n",yytext);
 }
<CONDITION>")\n" {
    while_parantheses_count--;
    if(while_parantheses_count!=0){
        printf("INVALID WHILE LOOP STATEMENT: MISSING MATCHING PARANTHESES\n");
        while_parantheses_count = 0;
    }
    BEGIN(WHILE);
}


<WHILE>"begin" {
    while_parantheses_count++;
}
<WHILE>"end;" {
    while_parantheses_count--;
    if(while_parantheses_count){
        printf("ERROR: you have entered end without a matching begin\n");
    }
    else{
        printf("CORRECT WHILE LOOP\n");
    }
    BEGIN(INITIAL);
}

"@" {
    printf("SEPARATOR: %s\n", yytext);
}

"+"|"-"|"*"|"/"|"%" {
    printf("ARITHMETIC OPERATOR (INTEGER): %s\n", yytext);
}

"="|">"|"<"|">="|"<="|"<>" {
    printf("RELATIONAL OPERATOR (INTEGER): %s\n", yytext);
}

":="|"+="|"-="|"*="|"/="|"%=" {
    printf("ASSIGNMENT OPERATOR (INTEGER): %s\n", yytext);
}

"("|")"|","|";"|"{"|"}"|":" {
    printf("SEPARATOR: %s\n", yytext);
}

[ \t\n]+ {
}

. {
    if (YYSTATE == PRINT) printf("INVALID PRINT STATEMENT: Unexpected token '%s'\n", yytext);
    else printf("UNKNOWN TOKEN: %s\n", yytext);
}

%%

int main(int argc, char **argv) {
    yylex();
    return 0;
}