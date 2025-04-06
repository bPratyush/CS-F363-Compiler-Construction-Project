%{
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "parser.tab.h"  

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

// External variable from parser to check if we should print tokens
extern int print_lexeme_token_pairs;

// Function to print lexeme-token pairs
void print_token(const char* lexeme, const char* token_type) {
    if (print_lexeme_token_pairs) {
        printf("%-20s  %-20s\n", lexeme, token_type);
    }
}

int isDeclared(const char* id) {
    int i;
    for(i = 0; i < symbolCount; i++){
        if(strcmp(symbolTable[i], id) == 0) return 1;
    }
    return 0;
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
int validate_identifier(const char *text) {
    const char *keywords[] = {
        "int","char","if","else","while","for","main","begin","end",
        "print","scan","program","VarDecl","inc","dec","to","do", NULL
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
static char scan_args[1024];


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
%}

%option noyywrap yylineno
%x COMMENT
%x VARDECL
%x  SCAN
%%
"//".*                  { /* skip single line comments */ }
"/*"                    { BEGIN(COMMENT); comment_index = 0; comment_buffer[0] = '\0'; }
<COMMENT>"*/"           { BEGIN(INITIAL); }
<COMMENT>\n             { 
                          if (comment_index < MAX_COMMENT_SIZE - 1) {
                              comment_buffer[comment_index++] = '\n';
                              comment_buffer[comment_index] = '\0';
                          }
                        }
<COMMENT>.              { if (comment_index < MAX_COMMENT_SIZE - 1) {
                              comment_buffer[comment_index++] = yytext[0];
                              comment_buffer[comment_index] = '\0';
                          }
                        }

"begin"                 { print_token(yytext, "KEYWORD"); return TK_BEGIN; }
"end"                   { print_token(yytext, "KEYWORD"); return TK_END; }
"program"               { print_token(yytext, "KEYWORD"); return TK_PROGRAM; }

"VarDecl"               { 
                          print_token(yytext, "KEYWORD"); 
                          varDeclFlag = 1;
                          return TK_VARDECL; 
                        }

":"                     { 
                          print_token(yytext, "SEPARATOR"); 
                          if (varDeclFlag) {
                              varDeclFlag = 0;
                              BEGIN(VARDECL);
                          }
                          return TK_COLON; 
                        }

<VARDECL>"end"          { 
                          print_token(yytext, "KEYWORD"); 
                          BEGIN(INITIAL);
                          return TK_END; 
                        }

<VARDECL>"VarDecl"      { 
                          print_token(yytext, "KEYWORD");
                          BEGIN(INITIAL);
                          return TK_VARDECL; 
                        }

<VARDECL>"("            { 
                          print_token(yytext, "SEPARATOR"); 
                          varDeclPos = 0;
                          return LPAREN; 
                        }

<VARDECL>")"            { 
                          print_token(yytext, "SEPARATOR"); 
                          return RPAREN; 
                        }

<VARDECL>","            { 
                          print_token(yytext, "SEPARATOR"); 
                          varDeclPos++;
                          return COMMA; 
                        }

<VARDECL>";"            { 
                          print_token(yytext, "SEPARATOR"); 
                          varDeclPos = 0;
                          return TK_SEP; 
                        }

<VARDECL>"int"          { 
                          print_token(yytext, "KEYWORD"); 
                          return TK_INT; 
                        }

<VARDECL>"char"         { 
                          print_token(yytext, "KEYWORD"); 
                          return TK_CHAR; 
                        }

<VARDECL>[a-z][a-z0-9_]* { 
                          if (varDeclPos == 0) { 
                              if (!validate_identifier(yytext)) {
                                  print_token(yytext, "ERROR: Invalid identifier");
                              } else if (isDeclared(yytext)) {
                                  print_token(yytext, "ERROR: Identifier already declared");
                              } else {
                                  print_token(yytext, "IDENTIFIER");
                                  symbolTable[symbolCount++] = strdup(yytext);
                              }
                          } else if (varDeclPos == 1) {
                              print_token(yytext, "ERROR: Invalid data type");
                          }
                          yylval.str = strdup(yytext);
                          return IDENTIFIER;
                        }

<VARDECL>[^a-z0-9_(),; \t\n]+ {
                          print_token(yytext, "ERROR: Invalid token in VarDecl");
                          return yytext[0]; /* Return first char to allow parser to recover */
                        }

<VARDECL>[ \t\n]+       { /* Skip whitespace in VARDECL mode */ }

"if"                    { print_token(yytext, "KEYWORD"); return TK_IF; }
"else"                  { print_token(yytext, "KEYWORD"); return TK_ELSE; }
"while"                 { print_token(yytext, "KEYWORD"); return TK_WHILE; }
"for"                   { print_token(yytext, "KEYWORD"); return TK_FOR; }
"do"                    { print_token(yytext, "KEYWORD"); return TK_DO; }
"to"                    { print_token(yytext, "KEYWORD"); return TK_TO; }
"inc"                   { print_token(yytext, "KEYWORD"); return TK_INC; }
"dec"                   { print_token(yytext, "KEYWORD"); return TK_DEC; }
"print"                 { print_token(yytext, "KEYWORD"); return TK_PRINT; }
"scan"                  { reset_scan_buffers();
                                BEGIN(SCAN);     return TK_SCAN; }
"main"                  { print_token(yytext, "KEYWORD"); return TK_MAIN; }
"int"                   { print_token(yytext, "KEYWORD"); return TK_INT; }
"char"                  { print_token(yytext, "KEYWORD"); return TK_CHAR; }

";"                     { print_token(yytext, "SEPARATOR"); return TK_SEP; }
"("                     { print_token(yytext, "SEPARATOR"); return LPAREN; }
")"                     { print_token(yytext, "SEPARATOR"); return RPAREN; }
","                     { print_token(yytext, "SEPARATOR"); return COMMA; }

"+"                     { print_token(yytext, "OPERATOR"); return PLUS; }
"-"                     { print_token(yytext, "OPERATOR"); return MINUS; }
"*"                     { print_token(yytext, "OPERATOR"); return MULT; }
"/"                     { print_token(yytext, "OPERATOR"); return DIV; }
"%"                     { print_token(yytext, "OPERATOR"); return MOD; }

"="                     { print_token(yytext, "OPERATOR"); return EQ; }
">"                     { print_token(yytext, "OPERATOR"); return GT; }
"<"                     { print_token(yytext, "OPERATOR"); return LT; }
">="                    { print_token(yytext, "OPERATOR"); return GE; }
"<="                    { print_token(yytext, "OPERATOR"); return LE; }
"<>"                    { print_token(yytext, "OPERATOR"); return NE; }

":="                    { print_token(yytext, "Assignment operator"); return ASSIGN; }
"+="                    { print_token(yytext, "OPERATOR"); return PLUS_ASSIGN; }
"-="                    { print_token(yytext, "OPERATOR"); return MINUS_ASSIGN; }
"*="                    { print_token(yytext, "OPERATOR"); return MULT_ASSIGN; }
"/="                    { print_token(yytext, "OPERATOR"); return DIV_ASSIGN; }
"%="                    { print_token(yytext, "OPERATOR"); return MOD_ASSIGN; }


<SCAN>"(" {scan_paranthesis_count++; return LPAREN;}
<SCAN>\"[^\"]*\"  { 
                    strncpy(scan_string,yytext,yyleng);
                    scan_string[yyleng]='\0';
                    count_all_symbols(scan_string);
                    return SCAN_STRING;
                     }
                                                                     
<SCAN>[a-z][a-z0-9_]* { 
    scan_arg_count++;
    if(!validate_identifier(yytext))
         scan_fl = 1;
    else
         scan_fl = (check_for_no_declaration(yytext)==0)?1:scan_fl; 
    if(scan_args[0] != '\0')
         strncat(scan_args, ", ", sizeof(scan_args)-strlen(scan_args)-1);
    strncat(scan_args, yytext, sizeof(scan_args)-strlen(scan_args)-1);
    
    return IDENTIFIER;
}
<SCAN>")" {scan_paranthesis_count--; return RPAREN;}
<SCAN>[ \t]*";"[ \t]* {
    char temp[1204];
   
    snprintf(temp, sizeof(temp), "scan(%s, %s);", scan_string, scan_args);
    if (!validate_scan_placeholders(scan_string))
         printf("\t%-20s\t\t%s\t\n", temp, "Error:invalid input statement");
    else if (scan_paranthesis_count != 0)
         printf("\t%-20s\t\t%s\t\n", temp, "Error: invalid input statement");
    else if (scan_arg_count != scan_symbol_count)
         printf("\t%-20s\t\t%s\t\n", temp, "Error:invalid input statement");
    else
         printf("\t%-20s\t\t%s\t\n", temp, "Valid input statement");
    BEGIN(INITIAL);
    return TK_SEP;
}
<SCAN>"," {}
<SCAN>\n {
            printf("Error: invalid input statement\n"); 
            BEGIN(INITIAL); 
        }




[a-z][a-z0-9_]*         { 
                          if (validate_identifier(yytext)) {
                              print_token(yytext, "IDENTIFIER");
                          } else {
                              print_token(yytext, "ERROR: Invalid identifier");
                          }
                          yylval.str = strdup(yytext);
                          return IDENTIFIER; 
                        }

\([ \t]*[0-9]+[ \t]*,[ \t]*2[ \t]*\)  {
                          char tmp[128];
                          char *start = yytext + 1;
                          while (*start == ' ' || *start == '\t') start++;
                          int value_len = (int)(strchr(yytext, ',') - start);
                          strncpy(tmp, start, value_len);
                          tmp[value_len] = '\0';
                          if (validate_binary(tmp)) {
                              print_token(yytext, "BINARY_INTEGER");
                          } else {
                              print_token(yytext, "ERROR: Invalid binary integer");
                          }
                          yylval.str = strdup(yytext);
                          return INTEGER_CONST;
                        }

\([ \t]*[0-9]+[ \t]*,[ \t]*8[ \t]*\)  {
                          char tmp[128];
                          char *start = yytext + 1;
                          while (*start == ' ' || *start == '\t') start++;
                          char *comma_ptr = strchr(start, ',');
                          int value_len = (int)(comma_ptr - start);
                          strncpy(tmp, start, value_len);
                          tmp[value_len] = '\0';
                          
                          if (validate_octal(tmp)) {
                              print_token(yytext, "OCTAL_INTEGER");
                          } else {
                              print_token(yytext, "ERROR: Invalid octal integer");
                          }
                          yylval.str = strdup(yytext);
                          return INTEGER_CONST;
                        }

\([ \t]*[0-9]+[ \t]*,[ \t]*10[ \t]*\) {
                          char tmp[128];
                          char *start = yytext + 1;
                          while (*start == ' ' || *start == '\t') start++;
                          char *comma_ptr = strchr(start, ',');
                          int value_len = (int)(comma_ptr - start);
                          strncpy(tmp, start, value_len);
                          tmp[value_len] = '\0';
                          
                          if (validate_decimal(tmp)) {
                              print_token(yytext, "DECIMAL_INTEGER");
                          } else {
                              print_token(yytext, "ERROR: Invalid decimal integer");
                          }
                          yylval.str = strdup(yytext);
                          return INTEGER_CONST;
                        }

\([ \t]*[0-9]+[ \t]*,[ \t]*[0-9]+[ \t]*\) {
                          print_token(yytext, "ERROR: Invalid integer format");
                          yylval.str = strdup(yytext);
                          return INTEGER_CONST;  
                        }

'([^']|\\.)+\'          {
                          if (validate_char_const(yytext)) {
                              print_token(yytext, "CHARACTER_CONST");
                          } else {
                              print_token(yytext, "ERROR: Invalid character constant");
                          }
                          yylval.str = strdup(yytext);
                          return CHAR_CONST;
                        }

\"([^"\\\n]|\\.)*\"     { 
                          print_token(yytext, "STRING_LITERAL"); 
                          yylval.str = strdup(yytext); 
                          return STRING_LITERAL; 
                        }

[ \t]+                  { /* skip whitespace */ }
\n                      { /* skip newlines */ }
.                       { print_token(yytext, "ERROR: unexpected character"); return yytext[0]; }

%%