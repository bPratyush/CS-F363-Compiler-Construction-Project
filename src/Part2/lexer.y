%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int validate_identifier(const char *text);
int isKeyword(const char *text);
int isDeclared(const char *id);
extern void record_token(const char* lexeme, const char* token);
void yyerror(const char *s) {
    fprintf(stderr, "%s\n", s);
}
int yylex(void);
FILE *yyin;
extern char* token_output[];
extern int token_output_count;
extern char* symbolTable[256];
extern int symbolCount;
extern int varDeclPos;
extern int varDeclFlag;
%}
%union {
    char* str;
}
%token TK_BEGIN TK_PROGRAM TK_VARDECL TK_END TK_INT TK_CHAR TK_COLON TK_SEP
%token <str> IDENTIFIER
%token LPAREN RPAREN COMMA
/* Nonterminals carrying a string value */
%type <str> type decl

%%
program:
    TK_BEGIN TK_PROGRAM TK_COLON var_decl_block TK_END TK_PROGRAM
       { }
    ;

var_decl_block:
    TK_BEGIN TK_VARDECL TK_COLON decl_list TK_END TK_VARDECL
    ;

decl_list:
      decl_list decl
    | decl
    | decl_list error TK_SEP { yyerror("Syntax error in declaration"); yyerrok; }
    ;

decl:
    LPAREN IDENTIFIER COMMA type RPAREN TK_SEP
       {
         /* Save current token_output count before processing declaration tokens */
         int tokens_start = token_output_count;
         if (!validate_identifier($2)) {
            token_output_count = tokens_start;
            char err_line[256];
            snprintf(err_line, sizeof(err_line), "( %s, %s ); Syntax Error: invalid identifier", $2, $4);
            token_output[token_output_count++] = strdup(err_line);
         }
         else if (isKeyword($2)) {
            token_output_count = tokens_start;
            char err_line[256];
            snprintf(err_line, sizeof(err_line), "( %s, %s ); Syntax Error: identifier is a keyword", $2, $4);
            token_output[token_output_count++] = strdup(err_line);
         }
         else if (isDeclared($2)) {
            token_output_count = tokens_start;
            char err_line[256];
            snprintf(err_line, sizeof(err_line), "( %s, %s ); Syntax Error: identifier already declared", $2, $4);
            token_output[token_output_count++] = strdup(err_line);
         }
         else {
            symbolTable[symbolCount++] = strdup($2);
         }
         free($2);
         free($4);
       }
    ;

type:
    TK_INT { $$ = strdup("int"); }
  | TK_CHAR { $$ = strdup("char"); }
  | IDENTIFIER {
      char* invalid_type = strdup($1);
      int i;
      for (i = token_output_count - 1; i >= 0; i--) {
          if (strstr(token_output[i], invalid_type) != NULL && 
              strstr(token_output[i], "Identifier") != NULL) {
              free(token_output[i]);
              int j;
              for (j = i; j < token_output_count - 1; j++) {
                  token_output[j] = token_output[j + 1];
              }
              token_output_count--;
              break;
          }
      }
      char err_token[256];
      snprintf(err_token, sizeof(err_token), "%-20s  %s", invalid_type, "Error: invalid data type)");
      token_output[token_output_count++] = strdup(err_token);
      char err_msg[256];
      snprintf(err_msg, sizeof(err_msg), "%s (invalid data type)", invalid_type);
      $$ = strdup(err_msg);
      free(invalid_type);
      free($1);
    }
  ;
  
%%

int main(int argc, char **argv) {
    if (argc != 2) {
       fprintf(stderr, "Usage: %s <input file>\n", argv[0]);
       exit(1);
    }
    yyin = fopen(argv[1], "r");
    if (!yyin) {
       perror("Error opening file");
       exit(1);
    }
    /* Print header before parsing */
    printf("%-20s  %s\n", "LEXEME", "TOKEN TYPE");
    yyparse();
    fclose(yyin);
    for (int i = 0; i < token_output_count; i++) {
        printf("%s\n", token_output[i]);
        free(token_output[i]);
    }
    return 0;
}