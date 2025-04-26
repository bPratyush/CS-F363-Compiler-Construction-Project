%{
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "threeac.tab.h"
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
char* symbolTable[256];
int symbolCount = 0;
static int varDeclFlag = 0;
int suppress_lexer_output = 1;
extern int print_lexeme_token_pairs;
void print_token(const char *lexeme, const char *token_type) {
    if(print_lexeme_token_pairs && !suppress_lexer_output)
        fprintf(stderr, "%-20s  %-20s\n", lexeme, token_type);
}
char* strdup_safe(const char *s) {
    char* dup = (char*)malloc(strlen(s)+1);
    if(dup) strcpy(dup, s);
    return dup;
}
int isDeclared(const char *id) {
    int i;
    for(i=0; i<symbolCount; i++){
        if(strcmp(symbolTable[i], id)==0)
            return 1;
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
void count_at_symbols(const char *s) {
    int i;
    for(i=0; s[i]; i++){
        if(s[i]=='@') at_count++;
    }
}
void finalize_print_statement() {
    char temp[1204];
    if(strlen(print_args)>0)
         snprintf(temp, sizeof(temp), "print(\"%s\", %s);", print_string, print_args);
    else
         snprintf(temp, sizeof(temp), "print(\"%s\");", print_string);
}
int validate_identifier(const char *text) {
    const char *keywords[] = {"int","char","if","else","while","for","main","begin","end","print","scan","program","VarDecl","inc","dec","to","do",NULL};
    int i; for(i=0; keywords[i]!=NULL; i++){ if(strcmp(text,keywords[i])==0)return 0; }
    if(text[0] < 'a' || text[0] > 'z') return 0;
    { int underscore=0,j; for(j=0; text[j]!='\0'; j++){
         if(text[j]=='_'){ underscore++; if(underscore>1)return 0; }
         else if(!(text[j]>='a' && text[j]<='z') && !(text[j]>='0' && text[j]<='9'))
            return 0;
       } }
    return 1;
}
int validate_char_const(const char *text) {
    int len = strlen(text);
    if(len<3)return 0;
    if(text[0]=='\'' && text[len-1]=='\'')
         return 1;
    return 0;
}
int validate_decimal(const char *text) {
    int i; for(i=0; text[i]!='\0'; i++){ if(text[i]<'0' || text[i]>'9') return 0; } return 1;
}
int validate_octal(const char *text) {
    int i; for(i=0; text[i]!='\0'; i++){ if(text[i]<'0' || text[i]>'7') return 0; } return 1;
}
int validate_binary(const char *text) {
    int i; for(i=0; text[i]!='\0'; i++){ if(text[i]!='0' && text[i]!='1') return 0; } return 1;
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
    scan_args[0]='\0';
}
void count_all_symbols(char* str){
    int idx=0;
    while(str[idx]!='\0'){
        if(str[idx]=='@')
            scan_symbol_count++;
        idx++;
    }
}
int validate_scan_placeholders(const char *s) {
    int atCount=0, commaCount=0, i;
    int len=strlen(s), start=0, end=len;
    if(len>=2 && s[0]=='\"' && s[len-1]=='\"'){
        start=1; end=len-1;
    }
    for(i=start;i<end;i++){
         if(s[i]=='\"')
             return 0;
         if(s[i]=='@')
             atCount++;
         else if(s[i]==',')
             commaCount++;
    }
    if(atCount < 1 || commaCount != atCount-1)return 0;
    return 1;
}
int statement_fl=0;
int isKeyword(const char *word) {
    const char *keywords[] = {"begin","end","VarDecl","int","char","if","else","while","for","print","scan","program","inc","dec","do","to","main",NULL};
    int i; for(i=0; keywords[i]!=NULL; i++){ if(strcmp(word,keywords[i])==0)return 1; } return 0;
}
%}
%option noyywrap yylineno
%x VARDECL STRING PRINT SCAN
%%
\([ \t]*[0-9]+[ \t]*,[ \t]*[0-9]+[ \t]*\) { yylval.str = strdup_safe(yytext); return INTEGER_CONST; }
"/*"([^*]|"*"+[^*/])*"*"+"/" { }
"//".* { }
"/*" { }
"begin"/[ \t]*("program"|"VarDecl")[ \t]* { print_token(yytext, "KEYWORD"); return TK_BEGIN; }
"begin" { print_token(yytext, "KEYWORD"); return TK_BLOCKBEGIN; }
"end" { print_token(yytext, "KEYWORD"); return TK_END; }
"program" { print_token(yytext, "KEYWORD"); return TK_PROGRAM; }
"VarDecl" { print_token(yytext, "KEYWORD"); varDeclFlag = 1; return TK_VARDECL; }
":" { print_token(yytext, "SEPARATOR"); if(varDeclFlag){ varDeclFlag=0; BEGIN(VARDECL); } return TK_COLON; }
<VARDECL>"end" { print_token(yytext, "KEYWORD"); BEGIN(INITIAL); return TK_END; }
<VARDECL>"/*"([^*]|"*"+[^*/])*"*"+"/" { }
<VARDECL>"//".* { }
<VARDECL>"VarDecl" { print_token(yytext, "KEYWORD"); BEGIN(INITIAL); return TK_VARDECL; }
<VARDECL>"(" { print_token(yytext, "SEPARATOR"); varDeclPos=0; return LPAREN; }
<VARDECL>")" { print_token(yytext, "SEPARATOR"); return RPAREN; }
<VARDECL>"," { print_token(yytext, "SEPARATOR"); varDeclPos++; return COMMA; }
<VARDECL>";" { print_token(yytext, "SEPARATOR"); varDeclPos=0; return TK_SEP; }
<VARDECL>"int" { print_token(yytext, "KEYWORD"); return TK_INT; }
<VARDECL>"char" { print_token(yytext, "KEYWORD"); return TK_CHAR; }
<VARDECL>[A-Za-z][A-Za-z0-9_]*\[[0-9]+\] {
  char arrName[256], sizeStr[64];
  if(sscanf(yytext, "%[^[][%[0-9]]", arrName, sizeStr)==2) {
    if(varDeclPos==0) {
      if(isKeyword(arrName))
         print_token(yytext, "Error: Keyword used as identifier");
      else if(validate_identifier(arrName)){
         int size = atoi(sizeStr);
         if(size>0){
           print_token(yytext, "array declaration");
           yylval.str = strdup_safe(yytext);
           if(!isDeclared(arrName))
             symbolTable[symbolCount++] = strdup_safe(arrName);
           return IDENTIFIER;
         } else { print_token(yytext, "Error: invalid array size"); }
      } else { print_token(yytext, "Error: invalid identifier"); }
    } else { print_token(yytext, "keyword"); }
    varDeclPos++;
  } else { print_token(yytext, "Error: invalid array declaration"); }
}
<VARDECL>[a-z][a-z0-9_]* {
    if(varDeclPos==0) {
      if(!validate_identifier(yytext))
         print_token(yytext, "ERROR: Invalid identifier");
      else if(isDeclared(yytext))
         print_token(yytext, "ERROR: Identifier already declared");
      else {
         print_token(yytext, "IDENTIFIER");
         symbolTable[symbolCount++] = strdup_safe(yytext);
      }
    } else if(varDeclPos==1)
         print_token(yytext, "ERROR: Invalid data type");
    yylval.str = strdup_safe(yytext);
    return IDENTIFIER;
}
<VARDECL>[^a-z0-9_(),; \t\n]+ { print_token(yytext, "ERROR: Invalid token in VarDecl"); return yytext[0]; }
<VARDECL>[ \t\n]+ { }
"if" {yylval.str = strdup_safe(yytext); print_token(yytext, "KEYWORD"); return TK_IF; }
"else" {yylval.str = strdup_safe(yytext); print_token(yytext, "KEYWORD"); return TK_ELSE; }
"while" {yylval.str = strdup_safe(yytext); print_token(yytext, "KEYWORD"); return TK_WHILE; }
"for" {yylval.str = strdup_safe(yytext); print_token(yytext, "KEYWORD"); return TK_FOR; }
"do" {yylval.str = strdup_safe(yytext); print_token(yytext, "KEYWORD"); return TK_DO; }
"to" {yylval.str = strdup_safe(yytext); print_token(yytext, "KEYWORD"); return TK_TO; }
"inc" {yylval.str = strdup_safe(yytext); print_token(yytext, "KEYWORD"); return TK_INC; }
"dec" {yylval.str = strdup_safe(yytext); print_token(yytext, "KEYWORD"); return TK_DEC; }
"main" {yylval.str = strdup_safe(yytext); print_token(yytext, "KEYWORD"); return TK_MAIN; }
"int" {yylval.str = strdup_safe(yytext); print_token(yytext, "KEYWORD"); return TK_INT; }
"char" {yylval.str = strdup_safe(yytext); print_token(yytext, "KEYWORD"); return TK_CHAR; }
"or" {yylval.str = strdup_safe(yytext); print_token(yytext, "KEYWORD"); return OR; }
"and" {yylval.str = strdup_safe(yytext); print_token(yytext, "KEYWORD"); return AND; }
"not" {yylval.str = strdup_safe(yytext); print_token(yytext, "KEYWORD"); return NOT; }
";" {yylval.str = strdup_safe(yytext); print_token(yytext, "SEPARATOR"); return TK_SEP; }
"(" {yylval.str = strdup_safe(yytext); print_token(yytext, "SEPARATOR"); return LPAREN; }
")" {yylval.str = strdup_safe(yytext); print_token(yytext, "SEPARATOR"); return RPAREN; }
"," {yylval.str = strdup_safe(yytext); print_token(yytext, "SEPARATOR"); return COMMA; }
"+" {yylval.str = strdup_safe(yytext); print_token(yytext, "OPERATOR"); return PLUS; }
"-" {yylval.str = strdup_safe(yytext); print_token(yytext, "OPERATOR"); return MINUS; }
"*" {yylval.str = strdup_safe(yytext); print_token(yytext, "OPERATOR"); return MULT; }
"/" {yylval.str = strdup_safe(yytext); print_token(yytext, "OPERATOR"); return DIV; }
"%" {yylval.str = strdup_safe(yytext); print_token(yytext, "OPERATOR"); return MOD; }
"=" {yylval.str = strdup_safe(yytext); print_token(yytext, "OPERATOR"); return EQ; }
">" {yylval.str = strdup_safe(yytext); print_token(yytext, "OPERATOR"); return GT; }
"<" {yylval.str = strdup_safe(yytext); print_token(yytext, "OPERATOR"); return LT; }
">=" {yylval.str = strdup_safe(yytext); print_token(yytext, "OPERATOR"); return GE; }
"<=" {yylval.str = strdup_safe(yytext); print_token(yytext, "OPERATOR"); return LE; }
"<>" {yylval.str = strdup_safe(yytext); print_token(yytext, "OPERATOR"); return NE; }
":=" {yylval.str = strdup_safe(yytext); print_token(yytext, "Assignment operator"); return ASSIGN; }
"+=" {yylval.str = strdup_safe(yytext); print_token(yytext, "OPERATOR"); return PLUS_ASSIGN; }
"-=" {yylval.str = strdup_safe(yytext); print_token(yytext, "OPERATOR"); return MINUS_ASSIGN; }
"*=" {yylval.str = strdup_safe(yytext); print_token(yytext, "OPERATOR"); return MULT_ASSIGN; }
"/=" {yylval.str = strdup_safe(yytext); print_token(yytext, "OPERATOR"); return DIV_ASSIGN; }
"%=" {yylval.str = strdup_safe(yytext); print_token(yytext, "OPERATOR"); return MOD_ASSIGN; }
"print" { print_token(yytext, "KEYWORD"); reset_print_buffers(); BEGIN(PRINT); return TK_PRINT; }
<PRINT>"(" { print_token(yytext, "SEPARATOR"); parentheses_count++; return LPAREN; }
<PRINT>\" { BEGIN(STRING); }
<STRING>[^\"]+ { strncat(print_string, yytext, sizeof(print_string)-strlen(print_string)-1); }
<STRING>\" { print_state_string_captured = 1; count_at_symbols(print_string); BEGIN(PRINT); yylval.str = strdup_safe(print_string); return STRING_LITERAL; }
<PRINT>"," { print_token(yytext, "SEPARATOR"); return COMMA; }
<PRINT>[a-z][a-z0-9_]* {
    print_token(yytext, "IDENTIFIER");
    arg_count++;
    if(strlen(print_args)>0)
         strncat(print_args, ", ", sizeof(print_args)-strlen(print_args)-1);
    strncat(print_args, yytext, sizeof(print_args)-strlen(print_args)-1);
    yylval.str = strdup_safe(yytext);
    return IDENTIFIER;
}
<PRINT>[A-Za-z][A-Za-z0-9_]*\[[0-9]+\] {
  char arrName[256], sizeStr[64];
  if(sscanf(yytext, "%[^[][%[0-9]]", arrName, sizeStr)==2) {
    if(varDeclPos==0) {
      if(isKeyword(arrName))
         print_token(yytext, "Error: Keyword used as identifier");
      else if(validate_identifier(yytext)) {
         int size = atoi(sizeStr);
         if(size>0) { print_token(yytext, "array declaration"); yylval.str = strdup_safe(yytext); return IDENTIFIER; }
         else print_token(yytext, "Error: invalid array size");
      } else print_token(yytext, "Error: invalid identifier");
    } else { print_token(yytext, "keyword"); }
    varDeclPos++;
  } else { print_token(yytext, "Error: invalid array declaration"); }
}
<PRINT>\([ \t]*[0-9]+[ \t]*,[ \t]*(2|8|10)[ \t]*\) {
    print_token(yytext, "INTEGER_CONST");
    arg_count++;
    yylval.str = strdup_safe(yytext);
    return INTEGER_CONST;
}
<PRINT>\'([^']|\\.)+\' {
    print_token(yytext, "CHARACTER_CONST");
    arg_count++;
    yylval.str = strdup_safe(yytext);
    return CHAR_CONST;
}
<PRINT>")" { print_token(yytext, "SEPARATOR"); parentheses_count--; return RPAREN; }
<PRINT>";" { print_token(yytext, "SEPARATOR"); finalize_print_statement(); BEGIN(INITIAL); return TK_SEP; }
<PRINT>[ \t]+ { }
<PRINT>\n { }
<PRINT>. { print_token(yytext, "ERROR: unexpected character in print statement"); return yytext[0]; }
"scan" { print_token(yytext, "KEYWORD"); reset_scan_buffers(); BEGIN(SCAN); return TK_SCAN; }
<SCAN>"(" { print_token(yytext, "SEPARATOR"); scan_paranthesis_count++; return LPAREN; }
<SCAN>\"[^\"]*\" {
    print_token(yytext, "STRING_LITERAL");
    strncpy(scan_string, yytext, yyleng);
    scan_string[yyleng] = '\0';
    count_all_symbols(scan_string);
    yylval.str = strdup_safe(yytext);
    return STRING_LITERAL;
}
<SCAN>"," { print_token(yytext, "SEPARATOR"); return COMMA; }
<SCAN>[a-z][a-z0-9_]* {
    print_token(yytext, "IDENTIFIER");
    scan_arg_count++;
    if(!validate_identifier(yytext))
         scan_fl = 1;
    else
         scan_fl = (!isDeclared(yytext)) ? 1 : scan_fl;
    if(strlen(scan_args)>0)
         strncat(scan_args, ", ", sizeof(scan_args)-strlen(scan_args)-1);
    strncat(scan_args, yytext, sizeof(scan_args)-strlen(scan_args)-1);
    yylval.str = strdup_safe(yytext);
    return IDENTIFIER;
}
<SCAN>[A-Za-z][A-Za-z0-9_]*\[[0-9]+\] {
  char arrName[256], sizeStr[64];
  if(sscanf(yytext, "%[^[][%[0-9]]", arrName, sizeStr)==2) {
    if(varDeclPos==0) {
      if(isKeyword(arrName))
         print_token(yytext, "Error: Keyword used as identifier");
      else if(validate_identifier(arrName)) {
         int size = atoi(sizeStr);
         if(size>0) { print_token(yytext, "array declaration"); yylval.str = strdup_safe(yytext); return IDENTIFIER; }
         else print_token(yytext, "Error: invalid array size");
      } else print_token(yytext, "Error: invalid identifier");
    } else { print_token(yytext, "keyword"); }
    varDeclPos++;
  } else { print_token(yytext, "Error: invalid array declaration"); }
}
<SCAN>")" { print_token(yytext, "SEPARATOR"); scan_paranthesis_count--; return RPAREN; }
<SCAN>";" {
    print_token(yytext, "SEPARATOR");
    { char temp[1204]; snprintf(temp, sizeof(temp), "scan(%s, %s);", scan_string, scan_args); }
    if(!validate_scan_placeholders(scan_string) || scan_paranthesis_count!=0 || scan_arg_count!=scan_symbol_count){}
    BEGIN(INITIAL);
    return TK_SEP;
}
[a-z][a-z0-9_]* {
    if(validate_identifier(yytext))
         print_token(yytext, "IDENTIFIER");
    else print_token(yytext, "ERROR: Invalid identifier");
    yylval.str = strdup_safe(yytext);
    return IDENTIFIER;
}
[A-Za-z][A-Za-z0-9_]*\[[0-9]+\] {
  char arrName[256], sizeStr[64];
  if(sscanf(yytext, "%[^[][%[0-9]]", arrName, sizeStr)==2) {
    if(varDeclPos==0) {
      if(isKeyword(arrName))
         print_token(yytext, "Error: Keyword used as identifier");
      else if(validate_identifier(arrName)) {
         int size = atoi(sizeStr);
         if(size>0) { print_token(yytext, "array declaration"); yylval.str = strdup_safe(yytext); return IDENTIFIER; }
         else print_token(yytext, "Error: invalid array size");
      } else print_token(yytext, "Error: invalid identifier");
    } else { print_token(yytext, "keyword"); }
    varDeclPos++;
  } else { print_token(yytext, "Error: invalid array declaration"); }
}
\([ \t]*[0-9]+[ \t]*,[ \t]*[0-9]+[ \t]*\) {
    print_token(yytext, "ERROR: Invalid integer format");
    yylval.str = strdup_safe(yytext);
    return INTEGER_CONST;
}
\'(\\.|[^\\'\n])+\' {
    print_token(yytext, (validate_char_const(yytext) ? "CHARACTER_CONST" : "ERROR: Invalid character constant"));
    yylval.str = strdup_safe(yytext);
    return CHAR_CONST;
}
\"([^"\\\n]|\\.)*\" {
    print_token(yytext, "STRING_LITERAL");
    yylval.str = strdup_safe(yytext);
    return STRING_LITERAL;
}
[ \t]+ { }
\n { }
. { print_token(yytext, "ERROR: unexpected character"); return yytext[0]; }
%%
