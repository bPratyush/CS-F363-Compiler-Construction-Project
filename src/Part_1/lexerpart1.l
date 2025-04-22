%{
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_COMMENT_SIZE 2048
static char comment_buffer[MAX_COMMENT_SIZE];
static int comment_index = 0;
static char scan_args[1024];
static char print_string[1024];
static char print_args[1024];
static int print_state_string_captured = 0;
static int at_count = 0;
static int arg_count = 0;
static int parentheses_count = 0;
static int varDeclPos = 0;
static char* symbolTable[256];
static int symbolCount = 0;
static int varDeclFlag = 0;

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

void count_at_symbols(const char* s) {
    int i;
    for (i = 0; s[i]; i++) {
        if (s[i] == '@') at_count++;
    }
}

void finalize_print_statement() {
    char temp[1204];
    if(strlen(print_args) > 0)
         snprintf(temp, sizeof(temp), "print(\"%s\", %s);", print_string, print_args);
    else
         snprintf(temp, sizeof(temp), "print(\"%s\");", print_string);
    
    if (!print_state_string_captured) {
         printf("\t%-20s\t\t%s\t\n", temp, "Error: Invalid output statement");
         return;
    }
    if (at_count != arg_count) {
         char err_msg[256];
         snprintf(err_msg, sizeof(err_msg), "Error: Invalid output statement");
         printf("\t%-20s\t\t%s\t\n", temp, err_msg);
         return;
    }
    
    printf("\t%-20s\t\t%s\t\n", temp, "Valid output statement");
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

int scan_arg_count=0;
int scan_paranthesis_count=0;
int scan_symbol_count=0;
int scan_fl=0;
char scan_string[1024];

void reset_scan_buffers(){
    scan_arg_count = 0;
    scan_paranthesis_count = 0;
    scan_symbol_count = 0;
    scan_fl = 0;
    scan_string[0] = '\0';
    scan_args[0] = '\0';
}

void count_all_symbols(char*str)
{
    int idx=0;
    while(str[idx]!='\0')
    {
        if(str[idx]=='@')
        {
            scan_symbol_count++;
        }
        idx++;
    }
}

int validate_scan_placeholders(const char *s) {
    int atCount = 0, commaCount = 0;
    int len = strlen(s);
    int start = 0, end = len;

    if (len >= 2 && s[0] == '\"' && s[len - 1] == '\"') {
        start = 1;
        end = len - 1;
    }
    for (int i = start; i < end; i++) {
         if (s[i] == '\"')
             return 0;
         if (s[i] == '@')
             atCount++;
         else if (s[i] == ',')
             commaCount++;
    }
    if (atCount < 1 || commaCount != atCount - 1)
         return 0;
    return 1;
}
int statement_fl=0;
int isKeyword(const char *word) {
    const char *keywords[] = {
        "begin", "end", "VarDecl", "int", "char", "if", "else", "while",
        "for", "print", "scan", "program", "inc", "dec", "do", "to", "main", NULL
    };
    int i;
    for (i = 0; keywords[i] != NULL; i++) {
        if (strcmp(word, keywords[i]) == 0)
            return 1;
    }
    return 0;
}

%}

%x VARDECL
%x NUMRELATIONS
%x COMMENT
%x PRINT
%x CONDITION
%x SCAN
%x STRING

rel_op ("="|">"|"<"|">="|"<="|"<>")
assign_op (":="|"+="|"-="|"*="|"/="|"%=")
%%

"begin" {
    printf("\t%-20s\t\t%s\t\n", yytext, "Keyword");
}

[ \t]+  {}

"VarDecl" {
    printf("\t%-20s\t\t%s\t\n", yytext, "Keyword");
    varDeclFlag = 1;
}

":" {
    printf("\t%-20s\t\t%s\t\n", yytext, "Separator");
    if (varDeclFlag) {
         BEGIN(VARDECL);
         varDeclFlag = 0;
    }
}

<VARDECL>"end" {
    printf("\t%-20s\t\t%s\t\n", yytext, "Keyword");
}

<VARDECL>"VarDecl" {
    printf("\t%-20s\t\t%s\t\n", yytext, "Keyword");
    BEGIN(INITIAL);
}

<VARDECL>{
    "(" { 
         varDeclPos = 0;
         printf("\t%-20s\t\t%s\t\n", yytext, "Separator");
    }
    ")" { 
         printf("\t%-20s\t\t%s\t\n", yytext, "Separator");
         varDeclPos = 0;
    }
    "," { 
         printf("\t%-20s\t\t%s\t\n", yytext, "Separator");
    }
    ";" { 
         printf("\t%-20s\t\t%s\t\n", yytext, "Separator");
    }
    "//".* { 
         //printf("\t%-20s\t\t%s\t\n", yytext, "Comment");
    }
    [A-Za-z][A-Za-z0-9_]*\[[0-9]+\] {
         char arrName[256], sizeStr[64];
         if (sscanf(yytext, "%[^[][%[0-9]]", arrName, sizeStr) == 2) {
             if (varDeclPos == 0) {
                 if (isKeyword(arrName)) {
                     printf("\t%-20s\t\t%s\t\n", yytext, "Error: Keyword is used as an identifier");
                 } else if (validate_identifier(arrName)) {
                     int size = atoi(sizeStr);
                     if (size > 0) {
                         printf("\t%-20s\t\t%s\t\n", yytext, "array declaration");
                         if (!isDeclared(arrName)) {
                             symbolTable[symbolCount++] = strdup(arrName);
                         }
                     } else {
                         printf("\t%-20s\t\t%s\t\n", yytext, "Error: invalid array size");
                     }
                 } else {
                     printf("\t%-20s\t\t%s\t\n", yytext, "Error: invalid identifier");
                 }
             } else {  
                 printf("\t%-20s\t\t%s\t\n", yytext, "keyword");
             }
             varDeclPos++;
         } else {
             printf("\t%-20s\t\t%s\t\n", yytext, "Error: invalid array declaration");
         }
    }
    [A-Za-z][A-Za-z0-9_]* {
    if (varDeclPos == 0) { 
        if (isKeyword(yytext)) {
            printf("\t%-20s\t\t%s\t\n", yytext, "Error: Keyword is used as an identifier");
        } else if (validate_identifier(yytext)) {
            if (!isDeclared(yytext)) {
                printf("\t%-20s\t\t%s\t\n", yytext, "Identifier");
                symbolTable[symbolCount++] = strdup(yytext);
            } else {
                printf("\t%-20s\t\t%s\t\n", yytext, "Error: identifier already declared");
            }
        } else {
            printf("\t%-20s\t\t%s\t\n", yytext, "Error: invalid identifier");
        }
    } else if (varDeclPos == 1) {  
        if (strcmp(yytext, "int") == 0 || strcmp(yytext, "char") == 0) {
            printf("\t%-20s\t\t%s\t\n", yytext, "Keyword");
        } else {
            printf("\t%-20s\t\t%s\t\n", yytext, "Error: invalid datatype");
        }
    } else {
        printf("\t%-20s\t\t%s\t\n", yytext, "Error: unexpected token in VarDecl");
    }
    varDeclPos++;
}
    [^ \t\n()\,;]+ {
         printf("\t%-20s\t\t%s\t\n", yytext, "Error: invalid token in VarDecl");
    }
}

"int"|"char"|"if"|"else"|"for"|"main"|"begin"|"end"|"program"|"VarDecl"|"inc"|"dec"|"while"|"do"|"to" {
    printf("\t%-20s\t\t%s\t\n", yytext, "Keyword");
}

"print" {
    reset_print_buffers();
    BEGIN(PRINT);
}

"scan" {
    reset_scan_buffers();
    BEGIN(SCAN);
}

[a-z][a-z0-9_]* {
    if (validate_identifier(yytext)) {
        if (isDeclared(yytext))
            printf("\t%-20s\t\t%s\t\n", yytext, "Identifier");
        else 
            printf("\t%-20s\t\t%s\t\n", yytext, "Error: undefined identifier");
    }
}

"//".* {
    //printf("\t%-20s\t\t%s\t\n", yytext, "Comment");
}

"/*" {
    BEGIN(COMMENT);
    comment_index = 0;
    comment_buffer[0] = '\0';
}

<COMMENT>"*/" {
    //printf("\t%-20s\t\t%s\t\n", comment_buffer, "Comment");
    BEGIN(INITIAL);
}

<COMMENT>"\n" {
    if (comment_index < MAX_COMMENT_SIZE - 1) {
        comment_buffer[comment_index++] = '\n';
        comment_buffer[comment_index] = '\0';
    }
}

<COMMENT>. {
    if (comment_index < MAX_COMMENT_SIZE - 1) {
        comment_buffer[comment_index++] = yytext[0];
        comment_buffer[comment_index] = '\0';
    }
}


\([ \t]*[0-9]+[ \t]*,[ \t]*2[ \t]*\) {
    char tmp[128];
    char *start = yytext + 1;
    while (*start == ' ' || *start == '\t') start++;
    int value_len = (int)(strchr(yytext, ',') - start);
    strncpy(tmp, start, value_len);
    tmp[value_len] = '\0';
    if (validate_binary(tmp))
         printf("\t%-20s\t\t%s\t\n", yytext, "Integer constant");
    else 
         printf("\t%-20s\t\t%s\t\n", yytext, "Error: invalid integer constant");
}

\([ \t]*[0-9]+[ \t]*,[ \t]*8[ \t]*\) {
    char tmp[128];
    char *start = yytext + 1; 
    while (*start == ' ' || *start == '\t') 
        start++;
    char *comma_ptr = strchr(start, ','); 
    int value_len = (int)(comma_ptr - start);
    strncpy(tmp, start, value_len);
    tmp[value_len] = '\0';
    if (validate_octal(tmp))
         printf("\t%-20s\t\t%s\t\n", yytext, "Integer constant");
    else 
         printf("\t%-20s\t\t%s\t\n", yytext, "Error: invalid integer constant");
}

\([ \t]*[0-9]+[ \t]*,[ \t]*10[ \t]*\) {
    char tmp[128];
    char *start = yytext + 1;
    while (*start == ' ' || *start == '\t') 
        start++;
    char *comma_ptr = strchr(start, ',');  
    int value_len = (int)(comma_ptr - start);
    strncpy(tmp, start, value_len);
    tmp[value_len] = '\0';
    if (validate_decimal(tmp))
         printf("\t%-20s\t\t%s\t\n", yytext, "Integer constant");
    else 
         printf("\t%-20s\t\t%s\t\n", yytext, "Error: invalid integer constant");
}

([0-9]+) {
    printf("\t%-20s\t\t%s\t\n", yytext, "Error: invalid integer constant");
}

'([^']|\\.)+' {
    if (validate_char_const(yytext))
         printf("\t%-20s\t\t%s\t\n", yytext, "Character constant");
    else 
         printf("\t%-20s\t\t%s\t\n", yytext, "Error: invalid character constant");
}

<PRINT>"(" { 
    if (parentheses_count > 1) {
         printf("\t%-20s\t\t%s\t\n", "(", "Error: parenthesis count exceeds 1");
    }
    parentheses_count++;
}

<PRINT>"\"" { BEGIN(STRING); }

<STRING>[^"\n]+ { 
    strncat(print_string, yytext, sizeof(print_string)-strlen(print_string)-1);
}

<STRING>"\"" {
     print_state_string_captured = 1;
     count_at_symbols(print_string);
     BEGIN(PRINT);
}

<STRING>\n { 
    char temp[1204];
    snprintf(temp, sizeof(temp), "print(\"%s\");", print_string);
    printf("\t%-20s\t\t%s\t\n", temp, "Error: Invalid output statement");
    reset_print_buffers();
    BEGIN(INITIAL);
}

<PRINT>"," {}

<PRINT>\([ \t]*[0-9]+[ \t]*,[ \t]*(2|8|10)[ \t]*\) {
    arg_count++;
}

<PRINT>\'([^']|\\.)+\' {
    arg_count++;
}

<PRINT>[a-z][a-z0-9_]* {
    if (!isDeclared(yytext)) {
         if(print_args[0] != '\0')
              strncat(print_args, ", ", sizeof(print_args)-strlen(print_args)-1);
         strncat(print_args, yytext, sizeof(print_args)-strlen(print_args)-1);
    } else {
         if(print_args[0] != '\0')
              strncat(print_args, ", ", sizeof(print_args)-strlen(print_args)-1);
         strncat(print_args, yytext, sizeof(print_args)-strlen(print_args)-1);
    }
    arg_count++;
}

<PRINT>")" {
    if (parentheses_count > 1)
        printf("\t%-20s\t\t%s\t\n", ")", "Error: parenthesis count exceeds 1");
    if (parentheses_count > 0)
        parentheses_count--;
    else
        printf("\t%-20s\t\t%s\t\n", ")", "Error: unmatched closing parenthesis");
}

<PRINT>";" {
    if (parentheses_count != 0)
        printf("\t%-20s\t\t%s\t\n", ";", "Error: parentheses not closed");
    else
        finalize_print_statement();
    BEGIN(INITIAL);
}

<PRINT>\n { 
    char temp[1204];
    snprintf(temp, sizeof(temp), "print(\"%s\");", print_string);
    if (parentheses_count != 0)
         printf("\t%-20s\t\t%s\t\n", temp, "Error: missing closing parenthesis and semicolon");
    else
         printf("\t%-20s\t\t%s\t\n", temp, "Error: missing semicolon");
    reset_print_buffers();
    BEGIN(INITIAL);
}

<SCAN>"(" {scan_paranthesis_count++;}
<SCAN>\"[^\"]*\"  { strncpy(scan_string,yytext,yyleng);
                    scan_string[yyleng] = '\0';
                    count_all_symbols(scan_string);
                     }
<SCAN>\([ \t]*[0-9]+[ \t]*,[ \t]*(2|8|10)[ \t]*\) { scan_arg_count++;}
                                                                                                
<SCAN>\'([^']|\\.)+\' { scan_arg_count++; }
<SCAN>[a-z][a-z0-9_]* { 
    scan_arg_count++;
    if(!validate_identifier(yytext))
         scan_fl = 1;
    else
         scan_fl = (!isDeclared(yytext))?1:scan_fl; 
    if(scan_args[0] != '\0')
         strncat(scan_args, ", ", sizeof(scan_args)-strlen(scan_args)-1);
    strncat(scan_args, yytext, sizeof(scan_args)-strlen(scan_args)-1);
}
<SCAN>")" {scan_paranthesis_count--;}
<SCAN>[ \t]*";"[ \t]* {
    char temp[1204];
    snprintf(temp, sizeof(temp), "scan(%s, %s);", scan_string, scan_args);
    if (!validate_scan_placeholders(scan_string))
         printf("\t%-20s\t\t%s\t\n", temp, "Error: invalid input statement");
    else if (scan_paranthesis_count != 0)
         printf("\t%-20s\t\t%s\t\n", temp, "Error: invalid input statement");
    else if (scan_arg_count != scan_symbol_count)
         printf("\t%-20s\t\t%s\t\n", temp, "Error: invalid input statement");
    else
         printf("\t%-20s\t\t%s\t\n", temp, "Valid input statement");
    BEGIN(INITIAL);
}
<SCAN>"," {}
<SCAN>\n {
            printf("Error: invalid input statement\n"); 
            BEGIN(INITIAL); 
        }

"@" {
    printf("\t%-20s\t\t%s\t\n", yytext, "Separator");
}

"+"|"-"|"*"|"/"|"%" {
    printf("\t%-20s\t\t%s\t\n", yytext, "Arithmetic operator");
}

"="|">"|"<"|">="|"<="|"<>" {
    printf("\t%-20s\t\t%s\t\n", yytext, "Relational operator");
}

":="|"+="|"-="|"*="|"/="|"%=" {
    printf("\t%-20s\t\t%s\t\n", yytext, "Assignment operator");
}

"("|")"|","|";"|"{"|"}"|":" {
    printf("\t%-20s\t\t%s\t\n", yytext, "Separator");
}

[ \t\n]+ {}

. {
    if(YYSTATE == PRINT)
        printf("\t%-20s\t\t%s\t\n", yytext, "Error: unexpected token");
    else
        printf("\t%-20s\t\t%s\t\n", yytext, "Error: unknown token");
}

%%

int main(int argc, char **argv) {
    FILE *file = fopen("t1.txt", "r");
     if (!file) {
        printf("File Not Found");
        exit(1);
    }
    yyin = file;
    printf("\t%-20s\t\t%s\t\n", "LEXEME", "TOKEN TYPE");
    yylex();
    fclose(file);
    return 0;
}

int yywrap(){
    return 1;
}