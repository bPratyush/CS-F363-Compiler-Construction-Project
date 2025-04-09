%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parser4.h"

// Function declarations
extern int yylex();
extern FILE *yyin;
extern int yylineno;
void yyerror(const char *s);

// Root of the AST
ASTNode* astRoot = NULL;

// Global variables from lexer we might use
extern char* symbolTable[256];
extern int symbolCount;

int syntax_errors = 0;  // Counter to track syntax errors

// Flag to track if we should print syntax analysis or lexeme-token pairs
int print_lexeme_token_pairs = 0; // Changed to default to AST building
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
%nonassoc TK_ELSE

/* Operator precedence */
%left EQ NE
%left LT GT LE GE
%left PLUS MINUS
%left MULT DIV MOD
%right UNARY

/* Union for semantic values */
%union {
    char* str;
    int num;
    struct ASTNode* ast;
}

/* Define types for non-terminals */
%type <ast> program program_body main_section var_decl_section var_decl_list
%type <ast> var_decl type statement_list statement expression_statement
%type <ast> print_statement optional_print_args print_arg_list scan_statement
%type <ast> id_list compound_statement selection_statement ifexpr iteration_statement
%type <ast> optional_inc expression assignment_expression assignment_operator
%type <ast> equality_expression equality_expression_tail relational_expression
%type <ast> relational_expression_tail additive_expression additive_expression_tail
%type <ast> multiplicative_expression multiplicative_expression_tail
%type <ast> unary_expression postfix_expression postfix_expression_tail primary_expression
%type <ast> conditional_statement

/* Define start symbol */
%start program

%%
program: 
    TK_BEGIN TK_PROGRAM TK_COLON program_body TK_END TK_PROGRAM
    {
        astRoot = createNode(NODE_PROGRAM);
        astRoot->data.children.left = $4;
        
        if (!print_lexeme_token_pairs) {
            if (syntax_errors == 0) {
                printf("Syntax analysis completed successfully. Program is syntactically correct.\n");
                printf("\nAbstract Syntax Tree:\n");
                printAST(astRoot, 0);
            } else {
                printf("Syntax analysis completed with %d error(s).\n", syntax_errors);
            }
        }
        $$ = astRoot;
    }
    | error { 
        if (!print_lexeme_token_pairs) {
            yyerror("Syntax error in program structure");
        }
        $$ = NULL;
        yyerrok; 
        {return 0;}
    }
    ;

program_body:
    var_decl_section
    {
        $$ = $1;
    }
    | var_decl_section main_section
    {
        ASTNode* node = createNode(NODE_MAIN_SECTION);
        node->data.children.left = $2;
        
        /* Link variable declarations with main section */
        if ($1) {
            ASTNode* varSection = $1;
            $$ = varSection;
            
            /* Find the last node in the var_decl_section */
            while (varSection->next) {
                varSection = varSection->next;
            }
            varSection->next = node;
        } else {
            $$ = node;
        }
    }
    ;

main_section:
    statement_list
    {
        $$ = $1;
    }
    | TK_BEGIN TK_MAIN TK_COLON statement_list TK_END TK_MAIN
    {
        $$ = $4;
    }
    ;

var_decl_section:
    TK_BEGIN TK_VARDECL TK_COLON var_decl_list TK_END TK_VARDECL
    {
        ASTNode* node = createNode(NODE_VARDECL_SECTION);
        node->data.children.left = $4;
        $$ = node;
    }
    | TK_BEGIN TK_VARDECL TK_COLON TK_END TK_VARDECL  /* Empty declarations */
    {
        $$ = createNode(NODE_VARDECL_SECTION);
    }
    ;

var_decl_list:
    var_decl
    {
        $$ = $1;
    }
    | var_decl_list var_decl
    {
        if ($1) {
            addToList($1, $2);
            $$ = $1;
        } else {
            $$ = $2;
        }
    }
    | error TK_SEP { 
        if (!print_lexeme_token_pairs) {
            yyerror("Syntax error in declaration");
        }
        $$ = NULL;
        yyerrok; 
        {return 0;}
    }
    ;

var_decl:
    LPAREN IDENTIFIER COMMA type RPAREN TK_SEP
    {
        ASTNode* idNode = createStrNode(NODE_IDENTIFIER, $2);
        $$ = createBinaryNode(NODE_VARDECL, idNode, $4);
    }
    ;

type:
    TK_INT
    {
        $$ = createNode(NODE_TYPE_INT);
    }
    | TK_CHAR 
    {
        $$ = createNode(NODE_TYPE_CHAR);
    }
    | IDENTIFIER { 
        if (!print_lexeme_token_pairs) {
            yyerror("Invalid data type"); 
            syntax_errors++; 
        }
        $$ = createStrNode(NODE_IDENTIFIER, $1);
    }
    ;

statement_list:
    statement
    {
        ASTNode* node = createNode(NODE_STATEMENT_LIST);
        node->data.children.left = $1;
        $$ = node;
    }
    | statement statement_list
    {
        if ($2) {
            /* Add statement to the front of the statement list */
            ASTNode* stmtList = $2;
            ASTNode* existingStmts = stmtList->data.children.left;
            
            if ($1) {
                $1->next = existingStmts;
                stmtList->data.children.left = $1;
            }
            
            $$ = stmtList;
        } else {
            ASTNode* node = createNode(NODE_STATEMENT_LIST);
            node->data.children.left = $1;
            $$ = node;
        }
    }
    ;

statement:
    expression_statement
    {
        $$ = $1;
    }
    | print_statement
    {
        $$ = $1;
    }
    | scan_statement
    {
        $$ = $1;
    }
    | compound_statement
    {
        $$ = $1;
    }
    | selection_statement
    {
        $$ = $1;
    }
    | iteration_statement
    {
        $$ = $1;
    }
    | conditional_statement
    {
        $$ = $1;
    }
    ;

conditional_statement:
    IDENTIFIER GE INTEGER_CONST
    {
        ASTNode* idNode = createStrNode(NODE_IDENTIFIER, $1);
        ASTNode* constNode = createStrNode(NODE_INT_LITERAL, $3);
        $$ = createBinaryNode(NODE_GE, idNode, constNode);
    }
    | IDENTIFIER EQ INTEGER_CONST
    {
        ASTNode* idNode = createStrNode(NODE_IDENTIFIER, $1);
        ASTNode* constNode = createStrNode(NODE_INT_LITERAL, $3);
        $$ = createBinaryNode(NODE_EQ, idNode, constNode);
    }
    | IDENTIFIER GT INTEGER_CONST
    {
        ASTNode* idNode = createStrNode(NODE_IDENTIFIER, $1);
        ASTNode* constNode = createStrNode(NODE_INT_LITERAL, $3);
        $$ = createBinaryNode(NODE_GT, idNode, constNode);
    }
    | IDENTIFIER LE INTEGER_CONST
    {
        ASTNode* idNode = createStrNode(NODE_IDENTIFIER, $1);
        ASTNode* constNode = createStrNode(NODE_INT_LITERAL, $3);
        $$ = createBinaryNode(NODE_LE, idNode, constNode);
    }
    | IDENTIFIER LT INTEGER_CONST
    {
        ASTNode* idNode = createStrNode(NODE_IDENTIFIER, $1);
        ASTNode* constNode = createStrNode(NODE_INT_LITERAL, $3);
        $$ = createBinaryNode(NODE_LT, idNode, constNode);
    }
    | IDENTIFIER NE INTEGER_CONST
    {
        ASTNode* idNode = createStrNode(NODE_IDENTIFIER, $1);
        ASTNode* constNode = createStrNode(NODE_INT_LITERAL, $3);
        $$ = createBinaryNode(NODE_NE, idNode, constNode);
    }
    ;

expression_statement:
    expression TK_SEP
    {
        $$ = createBinaryNode(NODE_EXPR_STMT, $1, NULL);
    }
    | TK_SEP  /* Empty statement */
    {
        $$ = createNode(NODE_EXPR_STMT);
    }
    ;

print_statement:
    TK_PRINT LPAREN STRING_LITERAL optional_print_args RPAREN TK_SEP
    {
        ASTNode* formatNode = createStrNode(NODE_STRING_LITERAL, $3);
        $$ = createIONode(NODE_PRINT_STMT, formatNode, $4);
    }
    ;

optional_print_args:
    /* empty */
    {
        $$ = NULL;
    }
    | COMMA print_arg_list
    {
        $$ = $2;
    }
    ;

print_arg_list:
    expression
    {
        $$ = $1;
    }
    | print_arg_list COMMA expression
    {
        if ($1) {
            addToList($1, $3);
            $$ = $1;
        } else {
            $$ = $3;
        }
    }
    ;

scan_statement:
    TK_SCAN LPAREN STRING_LITERAL COMMA id_list RPAREN TK_SEP
    {
        ASTNode* formatNode = createStrNode(NODE_STRING_LITERAL, $3);
        $$ = createIONode(NODE_SCAN_STMT, formatNode, $5);
    }
    ;

id_list:
    IDENTIFIER
    {
        $$ = createStrNode(NODE_IDENTIFIER, $1);
    }
    | id_list COMMA IDENTIFIER
    {
        ASTNode* idNode = createStrNode(NODE_IDENTIFIER, $3);
        if ($1) {
            addToList($1, idNode);
            $$ = $1;
        } else {
            $$ = idNode;
        }
    }
    ;

compound_statement:
    TK_BLOCKBEGIN statement_list TK_END 
    {
        $$ = createBinaryNode(NODE_COMPOUND_STMT, $2, NULL);
    }
    ;

selection_statement:
    TK_IF ifexpr statement %prec IFX
    {
        $$ = createBinaryNode(NODE_IF_STMT, $2, $3);
    }
    | TK_IF ifexpr statement TK_ELSE statement
    {
        $$ = createTernaryNode(NODE_IF_ELSE_STMT, $2, $3, $5);
    }
    ;

ifexpr:
    INTEGER_CONST
    {
        $$ = createStrNode(NODE_INT_LITERAL, $1);
    }
    | IDENTIFIER
    {
        $$ = createStrNode(NODE_IDENTIFIER, $1);
    }
    | conditional_statement
    {
        $$ = $1;
    }
    ;

iteration_statement:
    TK_WHILE LPAREN expression RPAREN TK_DO statement 
    {
        $$ = createBinaryNode(NODE_WHILE_STMT, $3, $6);
    }
    | TK_WHILE expression TK_DO statement
    {
        $$ = createBinaryNode(NODE_WHILE_STMT, $2, $4);
    }
    |
    TK_WHILE LPAREN expression RPAREN statement 
    {
        $$ = createBinaryNode(NODE_WHILE_STMT, $3, $5);
    }
    | TK_WHILE expression statement
    {
        $$ = createBinaryNode(NODE_WHILE_STMT, $2, $3);
    }
    | TK_FOR LPAREN IDENTIFIER ASSIGN expression TK_TO expression optional_inc expression RPAREN TK_DO statement
    {
        ASTNode* idNode = createStrNode(NODE_IDENTIFIER, $3);
        ASTNode* initNode = createBinaryNode(NODE_ASSIGN, idNode, $5);
        $$ = createTernaryNode(NODE_FOR_STMT, initNode, $7, $12);
        
        /* Store the increment expression and step expression with the loop condition */
        if ($8) {
            $8->next = $9;
            $7->next = $8;
        } else {
            $7->next = $9;
        }
    }
    | TK_FOR IDENTIFIER ASSIGN expression TK_TO expression optional_inc expression TK_DO statement
    {
        ASTNode* idNode = createStrNode(NODE_IDENTIFIER, $2);
        ASTNode* initNode = createBinaryNode(NODE_ASSIGN, idNode, $4);
        $$ = createTernaryNode(NODE_FOR_STMT, initNode, $6, $10);
        
        /* Store the increment expression and step expression with the loop condition */
        if ($7) {
            $7->next = $8;
            $6->next = $7;
        } else {
            $6->next = $8;
        }
    }
    | TK_DO statement TK_WHILE LPAREN expression RPAREN TK_SEP
    {
        $$ = createBinaryNode(NODE_DO_WHILE_STMT, $2, $5);
    }
    ;

optional_inc:
    /* empty */
    {
        $$ = NULL;
    }
    | TK_INC expression
    {
        $$ = createBinaryNode(NODE_PRE_INC, $2, NULL);
    }
    | TK_DEC expression
    {
        $$ = createBinaryNode(NODE_PRE_DEC, $2, NULL);
    }
    ;

expression:
    assignment_expression
    {
        $$ = $1;
    }
    |
    conditional_statement{
        $$=$1;
    }
    ;

assignment_expression:
    equality_expression
    {
        $$ = $1;
    }
    | IDENTIFIER assignment_operator assignment_expression
    {
        ASTNode* idNode = createStrNode(NODE_IDENTIFIER, $1);
        $$ = createBinaryNode($2->type, idNode, $3);
        free($2); /* Free the temporary node */
    }
    ;

assignment_operator:
    ASSIGN
    {
        $$ = createNode(NODE_ASSIGN);
    }
    | PLUS_ASSIGN
    {
        $$ = createNode(NODE_PLUS_ASSIGN);
    }
    | MINUS_ASSIGN
    {
        $$ = createNode(NODE_MINUS_ASSIGN);
    }
    | MULT_ASSIGN
    {
        $$ = createNode(NODE_MULT_ASSIGN);
    }
    | DIV_ASSIGN
    {
        $$ = createNode(NODE_DIV_ASSIGN);
    }
    | MOD_ASSIGN
    {
        $$ = createNode(NODE_MOD_ASSIGN);
    }
    ;

equality_expression:
    relational_expression equality_expression_tail
    {
        if ($2) {
            /* The tail will have created a node with $1 as the left child */
            $$ = $2;
        } else {
            $$ = $1;
        }
    }
    ;

equality_expression_tail:
    /* empty */
    {
        $$ = NULL;
    }
    | EQ relational_expression equality_expression_tail
    {
        ASTNode* node = createBinaryNode(NODE_EQ, $2, NULL);
        
        if ($3) {
            /* Chain the expressions - current equality becomes left child of next operation */
            $3->data.children.left = node;
            $$ = $3;
        } else {
            $$ = node;
        }
    }
    | NE relational_expression equality_expression_tail
    {
        ASTNode* node = createBinaryNode(NODE_NE, $2, NULL);
        
        if ($3) {
            /* Chain the expressions - current equality becomes left child of next operation */
            $3->data.children.left = node;
            $$ = $3;
        } else {
            $$ = node;
        }
    }
    ;

relational_expression:
    additive_expression relational_expression_tail
    {
        if ($2) {
            /* The tail will have created a node with $1 as the left child */
            $$ = $2;
        } else {
            $$ = $1;
        }
    }
    ;

relational_expression_tail:
    /* empty */
    {
        $$ = NULL;
    }
    | LT additive_expression
    {
        $$ = createBinaryNode(NODE_LT, $2, NULL);
    }
    | GT additive_expression
    {
        $$ = createBinaryNode(NODE_GT, $2, NULL);
    }
    | LE additive_expression
    {
        $$ = createBinaryNode(NODE_LE, $2, NULL);
    }
    | GE additive_expression
    {
        $$ = createBinaryNode(NODE_GE, $2, NULL);
    }
    ;

additive_expression:
    multiplicative_expression additive_expression_tail
    {
        if ($2) {
            /* Set the multiplicative expression as the left child of the additive expression */
            $2->data.children.left = $1;
            $$ = $2;
        } else {
            $$ = $1;
        }
    }
    ;

additive_expression_tail:
    /* empty */
    {
        $$ = NULL;
    }
    | PLUS multiplicative_expression additive_expression_tail
    {
        ASTNode* node = createBinaryNode(NODE_ADD, NULL, $2);
        
        if ($3) {
            /* Chain the expressions */
            node->next = $3;
        }
        
        $$ = node;
    }
    | MINUS multiplicative_expression additive_expression_tail
    {
        ASTNode* node = createBinaryNode(NODE_SUB, NULL, $2);
        
        if ($3) {
            /* Chain the expressions */
            node->next = $3;
        }
        
        $$ = node;
    }
    ;

multiplicative_expression:
    unary_expression multiplicative_expression_tail
    {
        if ($2) {
            /* Set the unary expression as the left child of the multiplicative expression */
            $2->data.children.left = $1;
            $$ = $2;
        } else {
            $$ = $1;
        }
    }
    ;

multiplicative_expression_tail:
    /* empty */
    {
        $$ = NULL;
    }
    | MULT unary_expression multiplicative_expression_tail
    {
        ASTNode* node = createBinaryNode(NODE_MUL, NULL, $2);
        
        if ($3) {
            /* Chain the expressions */
            node->next = $3;
        }
        
        $$ = node;
    }
    | DIV unary_expression multiplicative_expression_tail
    {
        ASTNode* node = createBinaryNode(NODE_DIV, NULL, $2);
        
        if ($3) {
            /* Chain the expressions */
            node->next = $3;
        }
        
        $$ = node;
    }
    | MOD unary_expression multiplicative_expression_tail
    {
        ASTNode* node = createBinaryNode(NODE_MOD, NULL, $2);
        
        if ($3) {
            /* Chain the expressions */
            node->next = $3;
        }
        
        $$ = node;
    }
    ;

unary_expression:
    postfix_expression
    {
        $$ = $1;
    }
    | PLUS unary_expression %prec UNARY
    {
        $$ = createBinaryNode(NODE_UNARY_PLUS, $2, NULL);
    }
    | MINUS unary_expression %prec UNARY
    {
        $$ = createBinaryNode(NODE_UNARY_MINUS, $2, NULL);
    }
    | TK_INC unary_expression
    {
        $$ = createBinaryNode(NODE_PRE_INC, $2, NULL);
    }
    | TK_DEC unary_expression
    {
        $$ = createBinaryNode(NODE_PRE_DEC, $2, NULL);
    }
    ;

postfix_expression:
    primary_expression postfix_expression_tail
    {
        if ($2) {
            /* Apply the postfix operator to the primary expression */
            $2->data.children.left = $1;
            $$ = $2;
        } else {
            $$ = $1;
        }
    }
    ;

postfix_expression_tail:
    /* empty */
    {
        $$ = NULL;
    }
    | TK_INC
    {
        $$ = createNode(NODE_POST_INC);
    }
    | TK_DEC
    {
        $$ = createNode(NODE_POST_DEC);
    }
    ;

primary_expression:
    IDENTIFIER
    {
        $$ = createStrNode(NODE_IDENTIFIER, $1);
    }
    | INTEGER_CONST
    {
        $$ = createStrNode(NODE_INT_LITERAL, $1);
    }
    | CHAR_CONST
    {
        $$ = createStrNode(NODE_CHAR_LITERAL, $1);
    }
    | LPAREN expression RPAREN
    {
        $$ = $2;
    }
    ;

%%

void yyerror(const char *s) {
    syntax_errors++;
    if (!print_lexeme_token_pairs) {
        fprintf(stderr, "%s\n", s);
    }
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <input file> [--tokens]\n", argv[0]);
        return 1;
    }
    
    // Check if we should print tokens or AST
    if (argc > 2 && strcmp(argv[2], "--tokens") == 0) {
        print_lexeme_token_pairs = 1;
    } else {
        print_lexeme_token_pairs = 0;
    }
    
    yyin = fopen(argv[1], "r");
    if (!yyin) {
        perror("Error opening file");
        return 1;
    }
    
    // Parse the input
    yyparse();
    
    // Free the AST memory when we're done
    if (astRoot) {
        freeAST(astRoot);
    }
    
    fclose(yyin);
    return 0;
}
