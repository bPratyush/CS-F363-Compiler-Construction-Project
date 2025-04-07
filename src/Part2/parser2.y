%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function declarations
extern int yylex();
extern FILE *yyin;
extern int yylineno;
void yyerror(const char *s);

// Global variables from lexer we might use
extern char* symbolTable[256];
extern int symbolCount;

int syntax_errors = 0;  // Counter to track syntax errors

// Flag to track if we should print syntax analysis or lexeme-token pairs
int print_lexeme_token_pairs = 1; // Default to printing lexeme-token pairs
%}

/* Tokens from lexer */
%token TK_BEGIN TK_END TK_PROGRAM TK_VARDECL TK_INT TK_CHAR TK_COLON TK_SEP
%token TK_IF TK_ELSE TK_WHILE TK_FOR TK_DO TK_TO TK_INC TK_DEC
%token TK_PRINT TK_SCAN TK_MAIN
%token<str> IDENTIFIER INTEGER_CONST CHAR_CONST STRING_LITERAL
%token LPAREN RPAREN COMMA
%token PLUS MINUS MULT DIV MOD
%token EQ GT LT GE LE NE
%token ASSIGN PLUS_ASSIGN MINUS_ASSIGN MULT_ASSIGN DIV_ASSIGN MOD_ASSIGN
%token TK_BLOCKBEGIN
/* Handle the dangling else problem with proper precedence */
%nonassoc IFX
%nonassoc ELSE
/* Union for semantic values */
%union {
    char* str;
}

/* Define start symbol */
%start program

%%
program: 
    TK_BEGIN TK_PROGRAM TK_COLON program_body TK_END TK_PROGRAM
    {
        if (!print_lexeme_token_pairs) {
            if (syntax_errors == 0) {
                printf("Syntax analysis completed successfully. Program is syntactically correct.\n");
            } else {
                printf("Syntax analysis completed with %d error(s).\n", syntax_errors);
            }
        }
    }
    | error { 
        if (!print_lexeme_token_pairs) {
            yyerror("Syntax error in program structure");
        }
        yyerrok; 
    }
    ;

program_body:
    var_decl_section
    | var_decl_section main_section
    ;

main_section:
    statement_list
    | TK_BEGIN TK_MAIN TK_COLON statement_list TK_END TK_MAIN
    ;

var_decl_section:
    TK_BEGIN TK_VARDECL TK_COLON var_decl_list TK_END TK_VARDECL
    | TK_BEGIN TK_VARDECL TK_COLON TK_END TK_VARDECL  /* Empty declarations */
    ;

var_decl_list:
    var_decl
    | var_decl_list var_decl
    | error TK_SEP { 
        if (!print_lexeme_token_pairs) {
            yyerror("Syntax error in declaration");
        }
        yyerrok; 
    }
    ;

var_decl:
    LPAREN IDENTIFIER COMMA type RPAREN TK_SEP
    ;

type:
    TK_INT
    | TK_CHAR 
    | IDENTIFIER { 
        if (!print_lexeme_token_pairs) {
            yyerror("Invalid data type"); 
            syntax_errors++; 
        }
    }
    ;

statement_list:
    statement
    |  statement statement_list
    | statement_list error { 
        if (!print_lexeme_token_pairs) {
            yyerror("Syntax error in statement");
        }
        yyerrok; 
    }
    ;

statement:
    expression_statement
    | print_statement
    | scan_statement
    | compound_statement
    | selection_statement
    | iteration_statement
    ;

expression_statement:
    expression TK_SEP
    | TK_SEP  /* Empty statement */
    | error TK_SEP { 
        if (!print_lexeme_token_pairs) {
            yyerror("Syntax error in expression"); 
        }
        yyerrok; 
    }
    ;

print_statement:
    TK_PRINT LPAREN STRING_LITERAL optional_print_args RPAREN TK_SEP
    ;

optional_print_args:
    /* empty */
    | COMMA print_arg_list
    ;

print_arg_list:
    expression
    | print_arg_list COMMA expression
    ;
scan_statement:
    TK_SCAN LPAREN STRING_LITERAL COMMA id_list RPAREN TK_SEP
    ;

id_list:
    IDENTIFIER
    | id_list COMMA IDENTIFIER
    ;

compound_statement:
    TK_BLOCKBEGIN statement_list TK_END  
    ;


selection_statement:
    TK_IF ifexpr  statement %prec IFX
    | TK_IF  ifexpr statement TK_ELSE statement
    ;
ifexpr:expression


iteration_statement:
    TK_WHILE LPAREN expression RPAREN TK_DO statement
    | TK_WHILE expression TK_DO statement
    | TK_FOR LPAREN IDENTIFIER ASSIGN expression TK_TO expression optional_inc expression RPAREN TK_DO statement
    | TK_FOR IDENTIFIER ASSIGN expression TK_TO expression optional_inc expression TK_DO statement
    | TK_DO statement TK_WHILE LPAREN expression RPAREN TK_SEP
    ;

optional_inc:
    /* empty */
    | TK_INC expression
    ;

expression:
    assignment_expression
    | error { 
        if (!print_lexeme_token_pairs) {
            yyerror("Invalid expression"); 
        }
        yyerrok; 
    }
    ;

assignment_expression:
    logical_or_expression
    | IDENTIFIER assignment_operator assignment_expression
    ;

assignment_operator:
    ASSIGN
    | PLUS_ASSIGN
    | MINUS_ASSIGN
    | MULT_ASSIGN
    | DIV_ASSIGN
    | MOD_ASSIGN
    ;

logical_or_expression:
    logical_and_expression
    ;

logical_and_expression:
    equality_expression
    ;

equality_expression:
    relational_expression
    | equality_expression EQ relational_expression
    | equality_expression NE relational_expression
    ;

relational_expression:
    additive_expression
    | relational_expression LT additive_expression
    | relational_expression GT additive_expression
    | relational_expression LE additive_expression
    | relational_expression GE additive_expression
    ;

additive_expression:
    multiplicative_expression
    | additive_expression PLUS multiplicative_expression
    | additive_expression MINUS multiplicative_expression
    ;

multiplicative_expression:
    unary_expression
    | multiplicative_expression MULT unary_expression
    | multiplicative_expression DIV unary_expression
    | multiplicative_expression MOD unary_expression
    ;

unary_expression:
    postfix_expression
    | PLUS unary_expression
    | MINUS unary_expression
    | TK_INC unary_expression
    | TK_DEC unary_expression
    ;

postfix_expression:
    primary_expression
    | postfix_expression TK_INC
    | postfix_expression TK_DEC
    ;

primary_expression:
    IDENTIFIER
    | INTEGER_CONST
    | CHAR_CONST
    | LPAREN expression RPAREN
    ;
%%

void yyerror(const char *s) {
    syntax_errors++;
    if (!print_lexeme_token_pairs) {
        fprintf(stderr, "Error: %s\n", s);
    }
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
