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
        printf("\t\t%s                        Error:Invalid output statement\n", yytext);
        return;
    }
    if (at_count != arg_count) {
        printf("\t\t%s                        Error:Invalid output statement\n", yytext);
        return;
    }
    printf("\t\t%s                        Valid output statement\n", print_string);
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
          int bert;
          // printf("VALID CONDITION IN WHILE LOOP\n");
        }
        else{
          printf("\t\t                        Error:Invalid loop condition\n");
        }
}

int scan_arg_count=0;
int scan_paranthesis_count=0;
int scan_symbol_count=0;
int scan_fl=0;
char scan_string[1024];

void reset_scan_buffers(){
        scan_arg_count=0;
        scan_paranthesis_count=0;
        scan_symbol_count=0;
        scan_fl=0;
        scan_string[0]='\0';
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

int statement_fl=0;
void reset_statement(){
    statement_fl=0;
}

int check_for_no_declaration(char*str){
    for(int i=0;i<symbolCount;i++)
    {
        if(strcmp(str,symbolTable[i])==0)
        {
            return 1;
        }
    }
    return 0;
}

%}

%x VARDECL
%x NUMRELATIONS
%x COMMENT
%x PRINT
%x WHILE
%x CONDITION
%x FOR
%x SCAN
%x STRING
%s ASSIGN

rel_op ("="|">"|"<"|">="|"<="|"<>")
assign_op (":="|"+="|"-="|"*="|"/="|"%=")
%%
"begin"[ \t]+"VarDecl:"   { BEGIN(VARDECL); 
                             /*printf("BEGIN VARIABLE DECLARATION\n");*/ 
                             printf("\t\tbegin                        Keyword\n");
                             printf("\t\tVarDecl                      Keyword\n");
                             printf("\t\t:                            Separator\n");
                           }

<VARDECL>"end"[ \t]+"VarDecl"[ \t]*\n? {
    BEGIN(INITIAL);
    printf("\t\tend                          Keyword\n");
    printf("\t\tVarDecl                      Keyword\n");
}

<VARDECL>[ \t]*\([ \t]*[a-zA-Z][a-z0-9_]*[ \t]*(\[[ \t]*[0-9]+\s*\])?[ \t]*,[ \t]*(int|char)[ \t]*\)[ \t]*;[ \t]*(\/\/.*)?[ \t]*\n {
    char lineCopy[1024];
    strncpy(lineCopy, yytext, 1023);
    lineCopy[1023] = '\0';
    {
        char *commentStart = strstr(lineCopy, "//");
        if(commentStart) {
            printf("\t\t%s                        Comment\n", commentStart);
            *commentStart = '\0';
        }
    }
    if (strchr(lineCopy, '[')) {
        char id[64], typ[16];
        int size;
        if (sscanf(lineCopy, " ( %63[^[]%*c%d%*c , %15[^)] ) ;", id, &size, typ) == 3) {
            char *nl = strpbrk(typ, " \t");
            if (nl) *nl = '\0';
            if (size > 0 && validate_array_identifier(id)) {
                printf("\t\t(%s[%d], %s)                        Array constant\n", id, size, typ);
                symbolTable[symbolCount++] = strdup(id);
            }
            else
                printf("\t\t%s                        Error:Invalid Array Declaration\n", yytext);
        } else {
            printf("\t\t%s                        Error:Invalid Array Declaration\n", yytext);
        }
    } else {
        char id[64], typ[16];
        if (sscanf(lineCopy, " ( %63[^,] , %15[^)] ) ;", id, typ) == 2) {
            char *nl = strpbrk(typ, " \t");
            if(nl) *nl = '\0';
            if (validate_identifier(id)) {
                printf("\t\t(%s, %s)                        Integer constant\n", id, typ);
                symbolTable[symbolCount++] = strdup(id);
            }
            else
                printf("\t\t%s                        Error:Invalid variable declaration\n", yytext);
        } else {
            printf("\t\t%s                        Error:Invalid variable declaration\n", yytext);
        }
    }
}

<VARDECL>"//".* {
    printf("\t\t%s                        Comment\n", yytext);
}

<VARDECL>[ \t]*\n {
}

<VARDECL>.*\n {
    printf("\t\t%s                        Error:Invalid variable declaration\n", yytext);
}

"for"/[ \t]+[a-z][a-z0-9_]*[ \t]*":=" {
    printf("\t\tfor                        Keyword\n");
    BEGIN(FOR);
}

<FOR>"while" {
    yyless(0);
    BEGIN(WHILE);
}

<FOR>[ \t\n]+ {}

<FOR>"to" {
    printf("\t\tto                        Keyword\n");
}

<FOR>"inc" {
    printf("\t\tinc                       Keyword\n");
}

<FOR>"dec" {
    printf("\t\tdec                       Keyword\n");
}

<FOR>"do" {
    printf("\t\tdo                        Keyword\n");
    BEGIN(INITIAL); 
}

<FOR>[a-z][a-z0-9_]* {
    printf("\t\t%s                        Identifier\n", yytext);
}

<FOR>":=" {
    printf("\t\t%s                        Assignment operator\n", yytext);
}

<FOR>\([ \t]*[0-9]+[ \t]*,[ \t]*(2|8|10)[ \t]*\) {
    printf("\t\t%s                        Integer constant\n", yytext);
}

<FOR>[0-9]+ {
    printf("\t\t%s                        Integer constant\n", yytext);
}

<FOR>"+"|"-"|"*"|"/"|"%" {
    printf("\t\t%s                        Arithmetic operator\n", yytext);
}

<FOR>. {
    printf("\t\t%s                        For-do token\n", yytext);
}

"int"|"char"|"if"|"else"|"for"|"main"|"begin"|"end"|"program"|"VarDecl"|"inc"|"dec"|"then" {
    printf("\t\t%s                        Keyword\n", yytext);
}

"print" {
    printf("\t\t%s                        Keyword\n", yytext);
    reset_print_buffers();
    BEGIN(PRINT);
}

"scan" {
    /* printf("KEYWORD: %s\n", yytext); */
    BEGIN(SCAN);
    reset_scan_buffers();
}

"while" {
    printf("\t\t%s                        Keyword\n",yytext);
    BEGIN(WHILE);
}

<WHILE>"while" {
    printf("\t\t%s                        Keyword\n", yytext);
}

[a-z][a-z0-9_]* {
    if (validate_identifier(yytext)) {
        if (isDeclared(yytext))
            printf("\t\t%s                        Identifier\n", yytext);
        else
            printf("\t\t%s                        Error: Undeclared Identifier\n", yytext);
    }
}
[ \t]*[a-z][a-z0-9_]*[ \t]*{assign_op}[ \t]* {

    BEGIN(ASSIGN);
    char var_name[64], assign_op[3];  
    sscanf(yytext, " %63[a-zA-Z0-9_] %2s", var_name, assign_op);
   

    if(!validate_identifier(var_name)) statement_fl=1;
     else {
         printf("\t\t%s                        Identifier\n",var_name);
         printf("\t\t%s                        Assign operator\n", assign_op);
         statement_fl=(check_for_no_declaration(var_name)==0)?1:statement_fl;
     }

}
"//".* {
    printf("\t\t%s                        Comment\n", yytext);
}

"/*" {
    BEGIN(COMMENT);
    comment_index = 0;
    comment_buffer[0] = '\0';
}

<COMMENT>"*/" {
   printf("\t\t/*%s*/                     Comment\n", comment_buffer);
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
    if (validate_binary(tmp)) printf("\t\t(%s, 2)                        Integer constant\n", tmp);
    else printf("\t\t%s                        Error: Invalid binary constant\n", yytext);
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
        printf("\t\t(%s, 8)                        Integer constant\n", tmp);
    else
        printf("\t\t%s                        Error: Invalid octal constant\n", yytext);
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
    if (validate_decimal(tmp)) printf("\t\t(%s, 10)                        Integer Constant\n", tmp);
    else printf("\t\t                        Error:Invalid decimal constant %s\n", yytext);
}

([0-9]+) {
    printf("\t\t                        Error:Missing base in %s\n", yytext);
}

'([^']|\\.)+' {
    if (validate_char_const(yytext)) printf("\t\t%s                        Character constant\n", yytext);
    else printf("\t\t                        Error: %s invalid character constant.\n", yytext);
}

<PRINT>"(" { 
 if(parentheses_count > 1) {
    printf("\t\t                        Error: invalid output statement.\n");
 }
 parentheses_count++;
 }

<PRINT>"\"" { BEGIN(STRING); }

<STRING>[^"\n]+ { strncat(print_string, yytext, sizeof(print_string)-strlen(print_string)-1); }

<STRING>"\"" { print_state_string_captured = 1; count_at_symbols(print_string); BEGIN(PRINT); }

<STRING>\n { printf("\t\t                        Error: invalid output statement.\n"); reset_print_buffers(); BEGIN(INITIAL); }

<PRINT>"," {
}

<PRINT>\([ \t]*[0-9]+[ \t]*,[ \t]*(2|8|10)[ \t]*\) {
    arg_count++;
}

<PRINT>\'([^']|\\.)+\' {
    arg_count++;
}

<PRINT>[a-z][a-z0-9_]* {
    if (!isDeclared(yytext)) {
        printf("\t\t                        Error: invalid output statement.\n");
    }
    arg_count++;
}

<PRINT>")" {
     if(parentheses_count > 1) {
        printf("\t\t                        Error: invalid output statement.\n");
     }
     if (parentheses_count > 0) parentheses_count--;
     else printf("\t\t                        Error: invalid output statement.\n");
}

<PRINT>";" {
    if (parentheses_count != 0) printf("\t\t                        Error: invalid output statement.\n");
    else finalize_print_statement();
    BEGIN(INITIAL);
}

<PRINT>\n {
    if (parentheses_count != 0) printf("\t\t                        Error: invalid output statement.\n");
    else printf("\t\t                        Error: invalid output statement.\n");
    reset_print_buffers();
    BEGIN(INITIAL);
}

<SCAN>"(" { scan_paranthesis_count++; }
<SCAN>\"[^\"]*\"  { strncpy(scan_string, yytext, yyleng);
                    count_all_symbols(scan_string);
                  }
<SCAN>\([ \t]*[0-9]+[ \t]*,[ \t]*(2|8|10)[ \t]*\) { scan_arg_count++; }
<SCAN>\'([^']|\\.)+\' { scan_arg_count++; }
<SCAN>[a-z][a-z0-9_]* { scan_arg_count++;
                        if(!validate_identifier(yytext)) scan_fl=1;
                        else scan_fl = (check_for_no_declaration(yytext)==0) ? 1 : scan_fl; 
                      }
<SCAN>")" { scan_paranthesis_count--; }
<SCAN>[ \t]*";"[ \t]* {
            if(scan_paranthesis_count==0 &&  scan_arg_count==scan_symbol_count  && !scan_fl)
                printf("\t\t                        Valid input statement\n");
            else if(scan_paranthesis_count !=0)
                printf("\t\t                        Error:Invalid input Statement\n");
            else if(scan_arg_count != scan_symbol_count)
                printf("\t\t                        Error:Invalid input Statement\n");
            else
                printf("\t\t                        Error:Invalid input Statement\n");
            BEGIN(INITIAL);
          }
<SCAN>"," {}
<SCAN>\n {
            printf("\t\tError:Invalid input Statement\n"); 
            BEGIN(INITIAL); 
        }

<WHILE>"\n" { BEGIN(INITIAL); }

<WHILE>[\t\n]* { /* ignore */ }
<WHILE>"(" {
 reset_while_stats();
 printf("\t\t%s                        Separator\n", yytext);
 while_parantheses_count++;
 BEGIN(CONDITION);
}
<CONDITION>[a-z][a-z0-9_]* {
    printf("\t\t%s                        Identifier\n", yytext);
}
<CONDITION>"<="|">="|"<>"|"="|"<"|">" {
    printf("\t\t%s                        Relational Operator\n", yytext);
}
<CONDITION>[0-9]+ {
    printf("\t\t%s                        While Constant\n", yytext);
}
<CONDITION>")" {
    while_parantheses_count--;
    if(while_parantheses_count != 0){
        printf("\t\tError: Parenthesis not matching\n");
        while_parantheses_count = 0;
    }
    printf("\t\t%s                        Separator\n", yytext);
    BEGIN(WHILE);
}

<WHILE>"begin" {
    printf("\t\t%s                        Keyword\n", yytext);
    while_parantheses_count++;
}

<WHILE>"end" {
    while_parantheses_count--;
    if(while_parantheses_count){
        printf("\t\tError: Parentheses not matching\n");
    }
    else{
        printf("\t\t%s                        Keyword\n", yytext);
    }
}
<WHILE>";" {
    printf("\t\t%s                        Separator\n", yytext);
    BEGIN(INITIAL);
}

"@" {
    printf("\t\t%s                        Separator\n", yytext);
}

"+"|"-"|"*"|"/"|"%" {
    printf("\t\t%s                        Arithmetic operator(integer)\n", yytext);
}

"="|">"|"<"|">="|"<="|"<>" {
    printf("\t\t%s                        Relational operator(integer)\n", yytext);
}

":="|"+="|"-="|"*="|"/="|"%=" {
    printf("\t\t%s                        Assignment operator(integer)\n", yytext);
}

<ASSIGN>";" {   
                printf("\t\t;                        Separator\n");
                if(!statement_fl)
                      printf("\t\t                        Valid assign statement\n");
                 else  
                      printf("\t\t                        Invalid assign statement\n");
                reset_statement();
                BEGIN(INITIAL);
            }   
<ASSIGN>[ \t]+ { }
<ASSIGN>.|[\n] {
            printf("\t\t                        Invalid assign statement\n");
            reset_statement();
            BEGIN(INITIAL);
         }

"("|")"|","|";"|"{"|"}"|":" {
    printf("\t\t%s                        Separator\n", yytext);
}

[ \t\n]+ { }

. {
    if (YYSTATE == PRINT)
        printf("\t\t                        Error: Unexpected token '%s' Invalid Print Statement\n", yytext);
    else
        printf("\t\t%s                        Error: invalid identifier\n", yytext);
}

%%

int main(int argc, char **argv) {
    printf("\t\tLEXEME                        TOKEN TYPE\n");
    yylex();
    return 0;
}

int yywrap(){
    return 1;
}