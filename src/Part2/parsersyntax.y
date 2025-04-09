%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function declarations
extern int yylex();
extern FILE *yyin;
extern int yylineno;
void yyerror(const char *s);
int print_lexeme_token_pairs = 0;
// Global variables from lexer we might use
extern char* symbolTable[256];
extern int symbolCount;
extern int suppress_lexer_output;

int syntax_errors = 0;  // Counter to track syntax errors
int semantic_errors = 0; // Counter to track semantic errors
int output_printed = 0;  // Flag to prevent multiple output messages
// Function to check if a variable is declared
int is_declared(const char* id) {
    int i;
    for (i = 0; i < symbolCount; i++) {
        if (symbolTable[i] && strcmp(symbolTable[i], id) == 0) {
            return 1; // Found
        }
    }
    return 0; // Not found
}

// Function to add a variable to symbol table
void add_variable(const char* id) {
    if (!is_declared(id)) {
        symbolTable[symbolCount++] = strdup(id);
    }
}

// Function to report a semantic error
void semantic_error(const char* msg) {
    semantic_errors++;
}

// Print result exactly once
void print_result() {
    if (!output_printed) {
        if (syntax_errors == 0 && semantic_errors == 0) {
            printf("Successfully Parsed !!!\n");
        } else {
            printf("Syntax Error !!!\n");
        }
        output_printed = 1;
    }
}
%}

%union{
    char *str;
    int num;
}
/* Tokens from lexer */
%token <str> TK_BEGIN TK_END TK_PROGRAM TK_VARDECL TK_INT TK_CHAR TK_COLON TK_SEP
%token <str> TK_IF TK_ELSE TK_WHILE TK_FOR TK_DO TK_TO TK_INC TK_DEC
%token <str> TK_PRINT TK_SCAN TK_MAIN
%token <str> IDENTIFIER INTEGER_CONST CHAR_CONST STRING_LITERAL
%token <str> LPAREN RPAREN COMMA
%token <str> PLUS MINUS MULT DIV MOD
%token <str> EQ GT LT GE LE NE
%token <str> ASSIGN PLUS_ASSIGN MINUS_ASSIGN MULT_ASSIGN DIV_ASSIGN MOD_ASSIGN
%token <str> TK_BLOCKBEGIN

/* Handle the dangling else problem with proper precedence */
%nonassoc IFX
%nonassoc TK_ELSE

/* Operator precedence */
%left EQ NE
%left LT GT LE GE
%left PLUS MINUS
%left MULT DIV MOD
%right UNARY

/* Define start symbol */
%start program

%%
program: 
    TK_BEGIN TK_PROGRAM TK_COLON program_body TK_END TK_PROGRAM
    {
        print_result();
    }
    | error { 
        yyerrok; 
        print_result();
        YYABORT;
    }
    ;

program_body:
    var_decl_section
    {
    }
    | var_decl_section main_section
    {
    }
    ;

main_section:
    statement_list
    {
    }
    | TK_BEGIN TK_MAIN TK_COLON statement_list TK_END TK_MAIN
    {
    }
    ;

var_decl_section:
    TK_BEGIN TK_VARDECL TK_COLON var_decl_list TK_END TK_VARDECL
    {
    }
    | TK_BEGIN TK_VARDECL TK_COLON TK_END TK_VARDECL  /* Empty declarations */
    {
    }
    ;

var_decl_list:
    var_decl
    {
    }
    | var_decl_list var_decl
    {
    }
    | error TK_SEP { 
        yyerrok; 
        syntax_errors++; 
    }
    ;

var_decl:
    LPAREN IDENTIFIER COMMA type RPAREN TK_SEP
    {
        add_variable($2); // Add the variable to the symbol table
    }
    ;

type:
    TK_INT
    {
    }
    | TK_CHAR 
    {
    }
    | IDENTIFIER { 
        yyerror("Invalid data type"); 
    }
    ;

statement_list:
    statement
    {
    }
    | statement statement_list
    {
    }
    ;

statement:
    expression_statement
    {
    }
    | print_statement
    {
    }
    | scan_statement
    {
    }
    | compound_statement
    {
    }
    | selection_statement
    {
    }
    | iteration_statement
    {
    }
    | conditional_statement
    {
    }
    ;

conditional_statement:
    IDENTIFIER GE INTEGER_CONST
    {
        if (!is_declared($1)) {
            char error_msg[100];
            snprintf(error_msg, sizeof(error_msg), "Variable '%s' not declared", $1);
            semantic_error(error_msg);
        }
    }
    | IDENTIFIER EQ INTEGER_CONST
    {
        if (!is_declared($1)) {
            char error_msg[100];
            snprintf(error_msg, sizeof(error_msg), "Variable '%s' not declared", $1);
            semantic_error(error_msg);
        }
    }
    | IDENTIFIER GT INTEGER_CONST
    {
        if (!is_declared($1)) {
            char error_msg[100];
            snprintf(error_msg, sizeof(error_msg), "Variable '%s' not declared", $1);
            semantic_error(error_msg);
        }
    }
    | IDENTIFIER LE INTEGER_CONST
    {
        if (!is_declared($1)) {
            char error_msg[100];
            snprintf(error_msg, sizeof(error_msg), "Variable '%s' not declared", $1);
            semantic_error(error_msg);
        }
    }
    | IDENTIFIER LT INTEGER_CONST
    {
        if (!is_declared($1)) {
            char error_msg[100];
            snprintf(error_msg, sizeof(error_msg), "Variable '%s' not declared", $1);
            semantic_error(error_msg);
        }
    }
    | IDENTIFIER NE INTEGER_CONST
    {
        if (!is_declared($1)) {
            char error_msg[100];
            snprintf(error_msg, sizeof(error_msg), "Variable '%s' not declared", $1);
            semantic_error(error_msg);
        }
    }
    ;

expression_statement:
    expression TK_SEP
    {
    }
    | TK_SEP  /* Empty statement */
    {
    }
    ;

print_statement:
    TK_PRINT LPAREN STRING_LITERAL optional_print_args RPAREN TK_SEP
    {
    }
    ;

optional_print_args:
    /* empty */
    {
    }
    | COMMA print_arg_list
    {
    }
    ;

print_arg_list:
    expression
    {
    }
    | print_arg_list COMMA expression
    {
    }
    ;

scan_statement:
    TK_SCAN LPAREN STRING_LITERAL COMMA id_list RPAREN TK_SEP
    {
    }
    ;

id_list:
    IDENTIFIER
    {
        if (!is_declared($1)) {
            char error_msg[100];
            snprintf(error_msg, sizeof(error_msg), "Variable '%s' not declared", $1);
            semantic_error(error_msg);
        }
    }
    | id_list COMMA IDENTIFIER
    {
        if (!is_declared($3)) {
            char error_msg[100];
            snprintf(error_msg, sizeof(error_msg), "Variable '%s' not declared", $3);
            semantic_error(error_msg);
        }
    }
    ;

compound_statement:
    TK_BLOCKBEGIN statement_list TK_END
    {
    }
    ;

selection_statement:
     TK_IF ifexpr compound_statement TK_SEP %prec IFX
    | TK_IF ifexpr compound_statement TK_ELSE statement

    /* if with single statement (requires semicolon if no else) */
    | TK_IF ifexpr statement TK_SEP %prec IFX
    | TK_IF ifexpr statement TK_ELSE statement

    /* if with parentheses */
    | TK_IF LPAREN ifexpr RPAREN compound_statement TK_SEP %prec IFX
    | TK_IF LPAREN ifexpr RPAREN compound_statement TK_ELSE statement
    | TK_IF LPAREN ifexpr RPAREN statement TK_SEP %prec IFX
    | TK_IF LPAREN ifexpr RPAREN statement TK_ELSE statement
    ;

ifexpr:
    INTEGER_CONST
    {
    }
    | IDENTIFIER
    {
        if (!is_declared($1)) {
            char error_msg[100];
            snprintf(error_msg, sizeof(error_msg), "Variable '%s' not declared", $1);
            semantic_error(error_msg);
        }
    }
    | conditional_statement
    {
    }
    ;

iteration_statement:
    TK_WHILE LPAREN expression RPAREN TK_DO statement 
    {
    }
    | TK_WHILE expression TK_DO statement
    {
    }
    |
    TK_WHILE LPAREN expression RPAREN statement 
    {
    }
    | TK_WHILE expression statement
    {
    }
    | TK_FOR LPAREN IDENTIFIER ASSIGN expression TK_TO expression optional_inc expression RPAREN TK_DO statement
    {
        if (!is_declared($3)) {
            char error_msg[100];
            snprintf(error_msg, sizeof(error_msg), "Variable '%s' not declared", $3);
            semantic_error(error_msg);
        }
    }
    | TK_FOR IDENTIFIER ASSIGN expression TK_TO expression optional_inc expression TK_DO statement
    {
        if (!is_declared($2)) {
            char error_msg[100];
            snprintf(error_msg, sizeof(error_msg), "Variable '%s' not declared", $2);
            semantic_error(error_msg);
        }
    }
    | TK_DO statement TK_WHILE LPAREN expression RPAREN TK_SEP
    {
    }
    ;

optional_inc:
    /* empty */
    {
    }
    | TK_INC expression
    {
    }
    | TK_DEC expression
    {
    }
    ;

expression:
    assignment_expression
    {
    }
    | conditional_statement
    {
    }
    ;

assignment_expression:
    equality_expression
    {
    }
    | IDENTIFIER assignment_operator assignment_expression
    {
        if (!is_declared($1)) {
            char error_msg[100];
            snprintf(error_msg, sizeof(error_msg), "Variable '%s' not declared", $1);
            semantic_error(error_msg);
        }
    }
    ;

assignment_operator:
    ASSIGN
    {
    }
    | PLUS_ASSIGN
    {
    }
    | MINUS_ASSIGN
    {
    }
    | MULT_ASSIGN
    {
    }
    | DIV_ASSIGN
    {
    }
    | MOD_ASSIGN
    {
    }
    ;

equality_expression:
    relational_expression equality_expression_tail
    {
    }
    ;

equality_expression_tail:
    /* empty */
    {
    }
    | EQ relational_expression equality_expression_tail
    {
    }
    | NE relational_expression equality_expression_tail
    {
    }
    ;

relational_expression:
    additive_expression relational_expression_tail
    {
    }
    ;

relational_expression_tail:
    /* empty */
    {
    }
    | LT additive_expression
    {
    }
    | GT additive_expression
    {
    }
    | LE additive_expression
    {
    }
    | GE additive_expression
    {
    }
    ;

additive_expression:
    multiplicative_expression additive_expression_tail
    {
    }
    ;

additive_expression_tail:
    /* empty */
    {
    }
    | PLUS multiplicative_expression additive_expression_tail
    {
    }
    | MINUS multiplicative_expression additive_expression_tail
    {
    }
    ;

multiplicative_expression:
    unary_expression multiplicative_expression_tail
    {
    }
    ;

multiplicative_expression_tail:
    /* empty */
    {
    }
    | MULT unary_expression multiplicative_expression_tail
    {
    }
    | DIV unary_expression multiplicative_expression_tail
    {
    }
    | MOD unary_expression multiplicative_expression_tail
    {
    }
    ;

unary_expression:
    postfix_expression
    {
    }
    | PLUS unary_expression %prec UNARY
    {
    }
    | MINUS unary_expression %prec UNARY
    {
    }
    | TK_INC unary_expression
    {
    }
    | TK_DEC unary_expression
    {
    }
    ;

postfix_expression:
    primary_expression postfix_expression_tail
    {
    }
    ;

postfix_expression_tail:
    /* empty */
    {
    }
    | TK_INC
    {
    }
    | TK_DEC
    {
    }
    ;

primary_expression:
    IDENTIFIER
    {
        if (!is_declared($1)) {
            char error_msg[100];
            snprintf(error_msg, sizeof(error_msg), "Variable '%s' not declared", $1);
            semantic_error(error_msg);
        }
    }
    | INTEGER_CONST
    {
    }
    | CHAR_CONST
    {
    }
    | LPAREN expression RPAREN
    {
    }
    ;

%%

void yyerror(const char *s) {
    syntax_errors++;
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
// Reset globals
print_lexeme_token_pairs = 0; // Disable lexer token printing
output_printed = 0;           // Reset output flag
syntax_errors = 0;            // Reset error counters
semantic_errors = 0;

// Parse the input
yyparse();
fclose(yyin);
return 0;
}
