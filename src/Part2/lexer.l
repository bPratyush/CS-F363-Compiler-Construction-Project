%{
#include "lexer.tab.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX_TOKENS 1024
#define MAX_COMMENT_SIZE 2048
char comment_buffer[MAX_COMMENT_SIZE];
int comment_index = 0;
char scan_args[1024];
char print_string[1024];
char print_args[1024];
int print_state_string_captured = 0;
int at_count = 0;
int arg_count = 0;
int parentheses_count = 0;
int varDeclPos = 0;
char* symbolTable[256];
int symbolCount = 0;
int varDeclFlag = 0;
char* token_output[MAX_TOKENS];
int token_output_count = 0;

void record_token(const char* lexeme, const char* token) {
    char line[256];
    snprintf(line, sizeof(line), "%-20s  %s", lexeme, token);
    token_output[token_output_count++] = strdup(line);
}

/* New function to print the token output */
void print_token_output() {
    printf("%-20s  %s\n", "LEXEME", "TOKEN TYPE");
    
    /* Filter out error messages */
    int j = 0;
    for (int i = 0; i < token_output_count; i++) {
        if (strcmp(token_output[i], "syntax error") == 0 || 
            strstr(token_output[i], "Syntax error in declaration") != NULL) {
            free(token_output[i]);
        } 
        else {
            if (j != i) {
                token_output[j] = token_output[i];
            }
            j++;
        }
    }
    token_output_count = j;
    
    /* Print the tokens */
    for (int i = 0; i < token_output_count; i++) {
        printf("%s\n", token_output[i]);
        free(token_output[i]);
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

void count_all_symbols(char* str)
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
        "begin", "end", "VarDecl", "int", "char", "if", "else","while",
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

%%
"//".*                       { }
"/*"([^*]|[\r\n]|(\*+([^*/]|[\r\n])))*\*+"/"   { }
"begin"      { record_token(yytext, "Keyword"); return TK_BEGIN; }
"program"    { record_token(yytext, "Keyword"); return TK_PROGRAM; }
"VarDecl"    { record_token(yytext, "Keyword"); return TK_VARDECL; }
"end"        { record_token(yytext, "Keyword"); return TK_END; }
"int"        { record_token(yytext, "Keyword"); return TK_INT; }
"char"       { record_token(yytext, "Keyword"); return TK_CHAR; }
":"          { record_token(yytext, "Separator"); return TK_COLON; }
";"          { record_token(yytext, "Separator"); return TK_SEP; }
"("          { record_token(yytext, "Separator"); return LPAREN; }
")"          { record_token(yytext, "Separator"); return RPAREN; }
","          { record_token(yytext, "Separator"); return COMMA; }

([a-z][a-z0-9]*(_[a-z0-9]+)?) {
    record_token(yytext, "Identifier");
    yylval.str = strdup(yytext);
    return IDENTIFIER;
}

[ \t\n]+    { }

. {
    record_token(yytext, "Error: unexpected token");
    return yytext[0];
}

%%

int yywrap(void) {
    return 1;
}