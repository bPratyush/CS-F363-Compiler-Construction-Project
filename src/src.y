//TRIAL BISON PARSER: DEBUG
%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void yyerror(const char *s);
int yylex(void);
FILE *yyin;
extern int symbolCount;
extern char* symbolTable[256];
extern int isDeclared(const char *id);
%}

%union {
    char* str;
}

/* Tokens provided by the lexer */
%token <str> IDENTIFIER INTEGER_CONSTANT CHARACTER_CONSTANT STRING_CONSTANT
%token TK_BEGIN TK_END TK_VARDECL TK_PROGRAM TK_INT TK_CHAR TK_IF TK_ELSE TK_WHILE TK_FOR TK_PRINT TK_SCAN
%token TK_ASSIGN TK_RELOP TK_ARITHOP
%token TK_SEP TK_COLON TK_TO TK_INC TK_DEC TK_DO

/* This declaration resolves the dangling-else ambiguity */
%nonassoc TK_ELSE
%nonassoc IFX

/* Every nonterminal value is a char* (when needed) */
%type <str> type decl stmt_block statement assignment_stmt scan_stmt print_stmt id_list print_arg_opt expr_list if_stmt while_stmt for_stmt inc_dec expression

%%
/* Program structure */
program:
      TK_BEGIN TK_PROGRAM TK_COLON var_decl_block stmt_block compound_end TK_PROGRAM trailing
         { printf("Program parsed successfully.\n"); }
    | error TK_END TK_PROGRAM { yyerror("Syntax error in program definition"); yyerrok; }
    ;

/* compound_end accepts either a single TK_END or a TK_END, optional separator, then another TK_END.
   This handles cases like: … end ; end program
*/
compound_end:
      TK_END
    | TK_END optional_sep TK_END
    ;

/* optional_sep allows either nothing or a single TK_SEP */
optional_sep:
      /* empty */
    | TK_SEP
    ;

/* trailing – allow extra separators after TK_PROGRAM */
trailing:
      /* empty */
    | trailing TK_SEP
    ;

/* Variable declaration block */
var_decl_block:
      TK_BEGIN TK_VARDECL TK_COLON decl_list TK_END TK_VARDECL
         { /* Successful declaration block */ }
    | error TK_END TK_VARDECL { yyerror("Syntax error in variable declaration block"); yyerrok; }
    ;

/* List of declarations */
decl_list:
      decl_list decl { /* Nothing extra */ }
    | decl
    | error { yyerror("Syntax error in declaration list"); yyerrok; }
    ;

/* A single variable declaration: (identifier : type); */
decl:
      "(" IDENTIFIER TK_COLON type ")" TK_SEP
         {
           printf("Declaration: %s of type %s\n", $2, $4);
           /* Register the identifier if not already declared */
           if (!isDeclared($2))
               symbolTable[symbolCount++] = strdup($2);
           free($2);
           free($4);
         }
    | error TK_SEP { yyerror("Invalid variable declaration"); yyerrok; }
    ;

/* A type is either int or char */
type:
      TK_INT { $$ = strdup("int"); }
    | TK_CHAR { $$ = strdup("char"); }
    | error { yyerror("Invalid type specification"); yyerrok; $$ = NULL; }
    ;

/* Statement block: one or more statements */
stmt_block:
      stmt_block statement
    | /* empty */ { $$ = NULL; }
    ;

/* A statement can be one of several types */
statement:
       assignment_stmt
    | scan_stmt
    | print_stmt
    | if_stmt
    | while_stmt
    | for_stmt
    | error TK_SEP { yyerror("Invalid statement syntax"); yyerrok; }
    ;

/* Assignment: identifier := expression; */
assignment_stmt:
      IDENTIFIER TK_ASSIGN expression TK_SEP
         { 
           printf("Assignment: %s := %s\n", $1, $3);
           free($1);
           free($3);
         }
    ;

/* Scan statement: TK_SCAN ( STRING_CONSTANT , id_list ) TK_SEP */
scan_stmt:
      TK_SCAN "(" STRING_CONSTANT "," id_list ")" TK_SEP
         {
           printf("Scan statement with format %s and identifiers %s\n", $3, $5);
           free($3);
           free($5);
         }
    ;

/* Print statement: TK_PRINT ( STRING_CONSTANT [ print_arg_opt ] ) TK_SEP */
print_stmt:
      TK_PRINT "(" STRING_CONSTANT print_arg_opt ")" TK_SEP
         {
           if ($4)
              printf("Print statement: %s with args %s\n", $3, $4);
           else
              printf("Print statement: %s\n", $3);
           free($3);
           if($4) free($4);
         }
    ;

/* id_list: one or more identifiers separated by commas */
id_list:
      IDENTIFIER
         { $$ = strdup($1); free($1); }
    | id_list "," IDENTIFIER
         {
           char *temp = malloc(strlen($1) + strlen($3) + 3);
           sprintf(temp, "%s, %s", $1, $3);
           free($1);
           free($3);
           $$ = temp;
         }
    | error { yyerror("Error in identifier list"); yyerrok; $$ = NULL; }
    ;

/* Optional print arguments */
print_arg_opt:
      /* empty */ { $$ = NULL; }
    | "," expr_list { $$ = $2; }
    | error { yyerror("Error in print argument list"); yyerrok; $$ = NULL; }
    ;

/* expr_list: one or more expressions separated by commas */
expr_list:
      expression { $$ = strdup($1); free($1); }
    | expr_list "," expression
         {
           char *temp = malloc(strlen($1) + strlen($3) + 3);
           sprintf(temp, "%s, %s", $1, $3);
           free($1);
           free($3);
           $$ = temp;
         }
    | error { yyerror("Error in expression list"); yyerrok; $$ = NULL; }
    ;

/* If statement (with optional else). Uses %prec IFX to resolve dangling else */
if_stmt:
      TK_IF expression statement %prec IFX
         { printf("If statement without else.\n"); free($2); }
    | TK_IF expression statement TK_ELSE statement
         { printf("If statement with else.\n"); free($2); }
    | error { yyerror("Invalid if statement syntax"); yyerrok; }
    ;

/* While statement */
while_stmt:
      TK_WHILE "(" expression ")" statement
         { printf("While statement.\n"); free($3); }
    ;

/* For statement:
   TK_FOR ( IDENTIFIER TK_ASSIGN expression TK_TO expression inc_dec expression TK_DO statement )
*/
for_stmt:
      TK_FOR "(" IDENTIFIER TK_ASSIGN expression TK_TO expression inc_dec expression TK_DO statement ")"
         {
           printf("For statement with control variable %s.\n", $3);
           /* Free declared values: IDENTIFIER = $3, remaining as needed */
           free($3);
           free($5);
           free($7);
           free($8);
           free($9);
           free($11);
         }
    | error ")" 
         {
           yyerror("Invalid for statement syntax");
           yyerrok;
         }
    ;

/* inc_dec production */
inc_dec:
      TK_INC { $$ = strdup("inc"); }
    | TK_DEC { $$ = strdup("dec"); }
    | error { yyerror("Invalid increment/decrement operator"); yyerrok; $$ = NULL; }
    ;

/* Expression production.
   For simplicity, expressions are either identifiers, constants or parenthesized expressions.
*/
expression:
      IDENTIFIER { $$ = strdup($1); free($1); }
    | INTEGER_CONSTANT { $$ = strdup($1); free($1); }
    | CHARACTER_CONSTANT { $$ = strdup($1); free($1); }
    | STRING_CONSTANT { $$ = strdup($1); free($1); }
    | expression TK_ARITHOP expression { $$ = NULL; /* Build AST as needed */ }
    | "(" expression ")" { $$ = $2; }
    | error { yyerror("Invalid expression syntax"); yyerrok; $$ = NULL; }
    ;
%%
 
void yyerror(const char *s) {
    fprintf(stderr, "Syntax error: %s\n", s);
}
 
int main(int argc, char *argv[]) {
    if (argc != 2) {
       fprintf(stderr, "Usage: %s <input file>\n", argv[0]);
       return 1;
    }
    yyin = fopen(argv[1], "r");
    if (!yyin) {
       perror("Error opening file");
       return 1;
    }
    yyparse();
    fclose(yyin);
    return 0;
}