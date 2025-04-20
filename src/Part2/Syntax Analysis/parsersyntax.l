%{
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "parsersyntax.tab.h"  // Include Bison-generated header

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
// External variable from parser to check if we should print tokens
extern int print_lexeme_token_pairs;

void print_token(const char* lexeme, const char* token_type) {
    if (print_lexeme_token_pairs && !suppress_lexer_output) {
        fprintf(stderr, "%-20s  %-20s\n", lexeme, token_type);
    }
}

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
    // Removed any direct output here
    char temp[1204];
    if(strlen(print_args) > 0)
         snprintf(temp, sizeof(temp), "print(\"%s\", %s);", print_string, print_args);
    else
         snprintf(temp, sizeof(temp), "print(\"%s\");", print_string);
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

%option noyywrap yylineno
%x VARDECL
%x STRING
%x PRINT
%x SCAN

%%
"/*"([^*]|"*"+[^*/])*"*"+"/"  { }
"//".*                       { }
"/*"                    { }

"begin"/[ \t]*("program"|"VarDecl")[ \t]*               { print_token(yytext, "KEYWORD"); return TK_BEGIN; }

"begin"      {
     print_token(yytext, "KEYWORD"); return   TK_BLOCKBEGIN; }
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

<VARDECL>"/*"([^*]|"*"+[^*/])*"*"+"/"  {}
<VARDECL>"//".*                       { }

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
<VARDECL>[A-Za-z][A-Za-z0-9_]*\[[0-9]+\] {
         char arrName[256], sizeStr[64];
         if (sscanf(yytext, "%[^[][%[0-9]]", arrName, sizeStr) == 2) {
             if (varDeclPos == 0) {
                 if (isKeyword(arrName)) {
                     // Changed to use print_token() which checks flag
                     print_token(yytext, "Error: Keyword is used as an identifier");
                 } else if (validate_identifier(arrName)) {
                     int size = atoi(sizeStr);
                     if (size > 0) {
                         print_token(yytext, "array declaration");
                         yylval.str = strdup(yytext);
                         return IDENTIFIER;
                         if (!isDeclared(arrName)) {
                             symbolTable[symbolCount++] = strdup(arrName);
                         }
                     } else {
                         print_token(yytext, "Error: invalid array size");
                     }
                 } else {
                     print_token(yytext, "Error: invalid identifier");
                 }
             } else {  
                 print_token(yytext, "keyword");
             }
             varDeclPos++;
         } else {
             print_token(yytext, "Error: invalid array declaration");
         }
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

<VARDECL>[ \t\n]+       { }

"if"                    { print_token(yytext, "KEYWORD"); return TK_IF; }
"else"                  { print_token(yytext, "KEYWORD"); return TK_ELSE; }
"while"                 { print_token(yytext, "KEYWORD"); return TK_WHILE; }
"for"                   { print_token(yytext, "KEYWORD"); return TK_FOR; }
"do"                    { print_token(yytext, "KEYWORD"); return TK_DO; }
"to"                    { print_token(yytext, "KEYWORD"); return TK_TO; }
"inc"                   { print_token(yytext, "KEYWORD"); return TK_INC; }
"dec"                   { print_token(yytext, "KEYWORD"); return TK_DEC; }
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

"print"                 { 
                          print_token(yytext, "KEYWORD"); 
                          reset_print_buffers();
                          BEGIN(PRINT);
                          return TK_PRINT;
                        }

<PRINT>"("              { 
                          print_token(yytext, "SEPARATOR"); 
                          parentheses_count++;
                          return LPAREN;
                        }

<PRINT>\"               { BEGIN(STRING); }

<STRING>[^\"]+          { 
                          strncat(print_string, yytext, sizeof(print_string)-strlen(print_string)-1);
                        }

<STRING>\"              { 
                          print_state_string_captured = 1;
                          count_at_symbols(print_string);
                          BEGIN(PRINT);
                          yylval.str = strdup(print_string);
                          return STRING_LITERAL;
                        }

<PRINT>","              { 
                          print_token(yytext, "SEPARATOR"); 
                          return COMMA; 
                        }

<PRINT>[a-z][a-z0-9_]*  { 
                          print_token(yytext, "IDENTIFIER");
                          arg_count++;
                          if(print_args[0] != '\0')
                              strncat(print_args, ", ", sizeof(print_args)-strlen(print_args)-1);
                          strncat(print_args, yytext, sizeof(print_args)-strlen(print_args)-1);
                          yylval.str = strdup(yytext);
                          return IDENTIFIER;
                        }
<PRINT>[A-Za-z][A-Za-z0-9_]*\[[0-9]+\] {
         char arrName[256], sizeStr[64];
         if (sscanf(yytext, "%[^[][%[0-9]]", arrName, sizeStr) == 2) {
             if (varDeclPos == 0) {
                 if (isKeyword(arrName)) {
                     print_token(yytext, "Error: Keyword is used as an identifier");
                 } else if (validate_identifier(arrName)) {
                     int size = atoi(sizeStr);
                     if (size > 0) {
                         print_token(yytext, "array declaration");
                         yylval.str = strdup(yytext);
                         return IDENTIFIER;
                         if (!isDeclared(arrName)) {
                             symbolTable[symbolCount++] = strdup(arrName);
                         }
                     } else {
                         print_token(yytext, "Error: invalid array size");
                     }
                 } else {
                     print_token(yytext, "Error: invalid identifier");
                 }
             } else {  
                 print_token(yytext, "keyword");
             }
             varDeclPos++;
         } else {
             print_token(yytext, "Error: invalid array declaration");
         }
    }
    
<PRINT>\([ \t]*[0-9]+[ \t]*,[ \t]*(2|8|10)[ \t]*\) {
                          print_token(yytext, "INTEGER_CONST");
                          arg_count++;
                          yylval.str = strdup(yytext);
                          return INTEGER_CONST;
                        }

<PRINT>\'([^']|\\.)+\'  {
                          print_token(yytext, "CHARACTER_CONST");
                          arg_count++;
                          yylval.str = strdup(yytext);
                          return CHAR_CONST;
                        }

<PRINT>")"              { 
                          print_token(yytext, "SEPARATOR");
                          parentheses_count--;
                          return RPAREN; 
                        }

<PRINT>";"              { 
                          print_token(yytext, "SEPARATOR");
                          finalize_print_statement();
                          BEGIN(INITIAL);
                          return TK_SEP; 
                        }

<PRINT>[ \t]+           { /* Skip whitespace in print statements */ }

<PRINT>\n               { /* Skip newlines in print statements */ }

<PRINT>.                {
                          print_token(yytext, "ERROR: unexpected character in print statement");
                          return yytext[0];
                        }


"scan"                  { 
                          print_token(yytext, "KEYWORD");
                          reset_scan_buffers();
                          BEGIN(SCAN);
                          return TK_SCAN;
                        }

<SCAN>"("               { 
                          print_token(yytext, "SEPARATOR");
                          scan_paranthesis_count++;
                          return LPAREN; 
                        }

<SCAN>\"[^\"]*\"        { 
                          print_token(yytext, "STRING_LITERAL");
                          strncpy(scan_string, yytext, yyleng);
                          scan_string[yyleng] = '\0';
                          count_all_symbols(scan_string);
                          yylval.str = strdup(yytext);
                          return STRING_LITERAL;
                        }

<SCAN>","               { 
                          print_token(yytext, "SEPARATOR"); 
                          return COMMA; 
                        }

<SCAN>[a-z][a-z0-9_]*   { 
                          print_token(yytext, "IDENTIFIER");
                          scan_arg_count++;
                          if(!validate_identifier(yytext))
                              scan_fl = 1;
                          else
                              scan_fl = (!isDeclared(yytext))?1:scan_fl; 
                          if(scan_args[0] != '\0')
                              strncat(scan_args, ", ", sizeof(scan_args)-strlen(scan_args)-1);
                          strncat(scan_args, yytext, sizeof(scan_args)-strlen(scan_args)-1);
                          yylval.str = strdup(yytext);
                          return IDENTIFIER;
                        }
<SCAN>[A-Za-z][A-Za-z0-9_]*\[[0-9]+\] {
         char arrName[256], sizeStr[64];
         if (sscanf(yytext, "%[^[][%[0-9]]", arrName, sizeStr) == 2) {
             if (varDeclPos == 0) {
                 if (isKeyword(arrName)) {
                     print_token(yytext, "Error: Keyword is used as an identifier");
                 } else if (validate_identifier(arrName)) {
                     int size = atoi(sizeStr);
                     if (size > 0) {
                         print_token(yytext, "array declaration");
                         yylval.str = strdup(yytext);
                         return IDENTIFIER;
                         if (!isDeclared(arrName)) {
                             symbolTable[symbolCount++] = strdup(arrName);
                         }
                     } else {
                         print_token(yytext, "Error: invalid array size");
                     }
                 } else {
                     print_token(yytext, "Error: invalid identifier");
                 }
             } else {  
                 print_token(yytext, "keyword");
             }
             varDeclPos++;
         } else {
             print_token(yytext, "Error: invalid array declaration");
         }
    }

                        
<SCAN>")"               { 
                          print_token(yytext, "SEPARATOR");
                          scan_paranthesis_count--;
                          return RPAREN; 
                        }

<SCAN>";"               { 
                          print_token(yytext, "SEPARATOR");
                          char temp[1204];
                          snprintf(temp, sizeof(temp), "scan(%s, %s);", scan_string, scan_args);
                          if (!validate_scan_placeholders(scan_string) ||
                              scan_paranthesis_count != 0 ||
                              scan_arg_count != scan_symbol_count) {
                          }
                          BEGIN(INITIAL);
                          return TK_SEP; 
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
                        
[A-Za-z][A-Za-z0-9_]*\[[0-9]+\] {
         char arrName[256], sizeStr[64];
         if (sscanf(yytext, "%[^[][%[0-9]]", arrName, sizeStr) == 2) {
             if (varDeclPos == 0) {
                 if (isKeyword(arrName)) {
                     print_token(yytext, "Error: Keyword is used as an identifier");
                 } else if (validate_identifier(arrName)) {
                     int size = atoi(sizeStr);
                     if (size > 0) {
                         print_token(yytext, "array declaration");
                         yylval.str = strdup(yytext);
                         return IDENTIFIER;
                         if (!isDeclared(arrName)) {
                             symbolTable[symbolCount++] = strdup(arrName);
                         }
                     } else {
                         print_token(yytext, "Error: invalid array size");
                     }
                 } else {
                     print_token(yytext, "Error: invalid identifier");
                 }
             } else {  
                 print_token(yytext, "keyword");
             }
             varDeclPos++;
         } else {
             print_token(yytext, "Error: invalid array declaration");
         }
    }

\([ \t]*[0-1]+[ \t]*,[ \t]*2[ \t]*\)  {
    char tmp[128];
    char *start = yytext + 1;
    while (*start == ' ' || *start == '\t') start++;
    int value_len = (int)(strchr(yytext, ',') - start);
    strncpy(tmp, start, value_len);
    tmp[value_len] = '\0';
    print_token(yytext, validate_binary(tmp) ? "BINARY_INTEGER" : "ERROR: Invalid binary integer");
    yylval.str = strdup(yytext);
    return INTEGER_CONST;
}

\([ \t]*[0-7]+[ \t]*,[ \t]*8[ \t]*\)  {
    char tmp[128];
    char *start = yytext + 1;
    while (*start == ' ' || *start == '\t') start++;
    char *comma_ptr = strchr(start, ',');
    int value_len = (int)(comma_ptr - start);
    strncpy(tmp, start, value_len);
    tmp[value_len] = '\0';
    print_token(yytext, validate_octal(tmp) ? "OCTAL_INTEGER" : "ERROR: Invalid octal integer");
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
    print_token(yytext, validate_decimal(tmp) ? "DECIMAL_INTEGER" : "ERROR: Invalid decimal integer");
    yylval.str = strdup(yytext);
    return INTEGER_CONST;
}

'([^']|\\.)+\'          {
                          print_token(yytext, validate_char_const(yytext) ? "CHARACTER_CONST" : "ERROR: Invalid character constant");
                          yylval.str = strdup(yytext);
                          return CHAR_CONST;
                        }

\"([^"\\\n]|\\.)*\"     { 
                          print_token(yytext, "STRING_LITERAL"); 
                          yylval.str = strdup(yytext); 
                          return STRING_LITERAL; 
                        }

[ \t]+                  { /* skip whitespace */ }
\n                      {  }
.                       { print_token(yytext, "ERROR: unexpected character"); return yytext[0]; }

%%
