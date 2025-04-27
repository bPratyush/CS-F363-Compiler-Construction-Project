%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
extern int yylex();
extern FILE *yyin;
extern int yylineno;
void yyerror(const char *s);
int print_lexeme_token_pairs = 0;
extern char* symbolTable[256];
extern int symbolCount;
extern int suppress_lexer_output;
int syntax_errors = 0;
int semantic_errors = 0;
int output_printed = 0;
int temp_count = 0;
int for_flag = -1;
char *if_dum;
char* newtemp() {
    char *temp = (char *)malloc(10);
    sprintf(temp, "t%d", temp_count++);
    return temp;
}
int label_count = 0;
void semantic_error(const char* msg) {
    semantic_errors++;
}
char* newlabel() {
    char *lbl = (char *)malloc(10);
    sprintf(lbl, "L%d", label_count++);
    return lbl;
}
void add_variable(const char* id) {
    int i;
    for(i = 0; i < symbolCount; i++){
        if(symbolTable[i] && strcmp(symbolTable[i], id) == 0)
            return;
    }
    symbolTable[symbolCount++] = strdup(id);
}
int is_declared(const char* id) {
    int i;
    for(i = 0; i < symbolCount; i++){
        if(symbolTable[i] && strcmp(symbolTable[i], id)==0)
            return 1;
    }
    return 0;
}
void print_result() {
    if(!output_printed) {
      //  printf("I am Here\n");
    //    if(syntax_errors==0 && semantic_errors==0)
        //    printf("Successfully Parsed !!!\n");
  //      else
      //      printf("Syntax Error !!!\n");
        output_printed = 1;
    }
}
typedef struct {
    char *L_else;
    char *L_end;
} LabelPair;

LabelPair label_stack[10];
int label_stack_ptr = -1;

void push_labels(char *L_else, char *L_end) {
    label_stack[++label_stack_ptr] = (LabelPair){L_else, L_end};
}

LabelPair pop_labels() {
    return label_stack[label_stack_ptr--];
}
char *F_var, *F_end, *F_inc;
char *F_Lstart, *F_Lend;
char *F_tmpcond;
char *W_Lstart, *W_Lend, *W_tmpcond;
char* L_else , *L_end;
%}

%union {
    char *str;
    int num;
}

%token<str> TK_BEGIN TK_END TK_PROGRAM TK_VARDECL TK_INT TK_CHAR TK_COLON TK_SEP
%token<str> TK_IF TK_ELSE TK_WHILE TK_FOR TK_DO TK_TO TK_INC TK_DEC
%token<str> TK_PRINT TK_SCAN TK_MAIN
%token<str> IDENTIFIER INTEGER_CONST CHAR_CONST STRING_LITERAL
%token<str> LPAREN RPAREN COMMA
%token<str> PLUS MINUS MULT DIV MOD
%token<str> EQ GT LT GE LE NE
%token<str> ASSIGN PLUS_ASSIGN MINUS_ASSIGN MULT_ASSIGN DIV_ASSIGN MOD_ASSIGN
%token<str> TK_BLOCKBEGIN
%token<str> OR AND NOT
%token<str> UNARY

%nonassoc IFX
%nonassoc TK_ELSE
%left OR
%left AND
%right NOT
%left EQ NE
%left LT GT LE GE
%left PLUS MINUS
%left MULT DIV MOD
%right UNARY
%start program

%type<str> expression assignment_expression equality_expression relational_expression additive_expression multiplicative_expression unary_expression primary_expression postfix_expression  ifexpr conditional_statement selection_statement compound_statement optional_inc assignment_operator postfix_expression_tail

%%
program:
    TK_BEGIN TK_PROGRAM TK_COLON program_body TK_END TK_PROGRAM
      { print_result(); }
  | error { yyerrok; print_result(); YYABORT; }
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
    TK_BEGIN TK_VARDECL TK_COLON var_decl_list TK_END TK_VARDECL { }
  | TK_BEGIN TK_VARDECL TK_COLON TK_END TK_VARDECL { }
  ;
var_decl_list:
    var_decl
  | var_decl_list var_decl
  | error { yyerrok; syntax_errors++; printf("Syntax Error !!!\n"); return 0; }
  ;
var_decl:
    LPAREN IDENTIFIER COMMA type RPAREN TK_SEP { add_variable($2); }
  ;
type:
    TK_INT { }
  | TK_CHAR { }
  | IDENTIFIER { yyerror("Invalid data type"); }
  ;
statement_list:
    statement { }
  | statement statement_list { }
  ;
statement:
    expression_statement { }
  | print_statement { }
  | scan_statement { }
  | compound_statement { }
  | selection_statement { }
  | iteration_statement { }
  | conditional_statement { }
  ;
conditional_statement:
    IDENTIFIER GE INTEGER_CONST {
         char*c = strcat($1 , $2);
         $$ = strcat(c , $3);
         if(!is_declared($1)){
            char err[100];
            snprintf(err, sizeof(err),"Variable '%s' not declared", $1);
            semantic_error(err);
         }
    }
  | IDENTIFIER EQ INTEGER_CONST {
         char*c = strcat($1 , $2);
         $$ = strcat(c , $3);
         if(!is_declared($1)){
            char err[100];
            snprintf(err, sizeof(err),"Variable '%s' not declared", $1);
            semantic_error(err);
         }
    }
  | IDENTIFIER GT INTEGER_CONST {
       //  printf("DEBUG: %s   GT\n" , $3);
         char*c = strcat($1 , $2);
         $$ = strcat(c , $3);
         if(!is_declared($1)){
            char err[100];
            snprintf(err, sizeof(err),"Variable '%s' not declared", $1);
            semantic_error(err);
         }
    }
  | IDENTIFIER LE INTEGER_CONST {
         char*c = strcat($1 , $2);
         $$ = strcat(c , $3);
         if(!is_declared($1)){
            char err[100];
            snprintf(err, sizeof(err),"Variable '%s' not declared", $1);
            semantic_error(err);
         }
    }
  | IDENTIFIER LT INTEGER_CONST {
         char*c = strcat($1 , $2);
         $$ = strcat(c , $3);
         if(!is_declared($1)){
            char err[100];
            snprintf(err, sizeof(err),"Variable '%s' not declared", $1);
            semantic_error(err);
         }
    }
  | IDENTIFIER NE INTEGER_CONST {
         char*c = strcat($1 , $2);
         $$ = strcat(c , $3);
         if(!is_declared($1)){
            char err[100];
            snprintf(err, sizeof(err),"Variable '%s' not declared", $1);
            semantic_error(err);
         }
    }
  ;
expression_statement:
    expression TK_SEP { }
  | TK_SEP { }
  ;
print_statement:
    TK_PRINT LPAREN STRING_LITERAL optional_print_args RPAREN TK_SEP { }
  ;
optional_print_args:
    { }
  | COMMA print_arg_list { }
  ;
print_arg_list:
    expression { }
  | print_arg_list COMMA expression { }
  ;
scan_statement:
    TK_SCAN LPAREN STRING_LITERAL COMMA id_list RPAREN TK_SEP { }
  ;
id_list:
    IDENTIFIER {
         if(!is_declared($1)){
            char err[100];
            snprintf(err, sizeof(err),"Variable '%s' not declared", $1);
            semantic_error(err);
         }
    }
  | id_list COMMA IDENTIFIER {
         if(!is_declared($3)){
            char err[100];
            snprintf(err, sizeof(err),"Variable '%s' not declared", $3);
            semantic_error(err);
         }
    }
  ;
compound_statement:
    TK_BLOCKBEGIN statement_list TK_END { }
  ;
selection_statement:
    TK_IF LPAREN expression RPAREN 
    {
        char *L_else = newlabel();
        char *L_end = newlabel();
        push_labels(L_else, L_end);

        printf("t1 := %s\n", $3);
        printf("if t1 == 0 goto %s\n", L_else);
    }
    compound_statement
    optional_else
;

optional_else:
    TK_ELSE 
    {
        LabelPair current = label_stack[label_stack_ptr];
        printf("goto %s\n", current.L_end);
        printf("%s:\n", current.L_else);
    }
    compound_statement
    {
        LabelPair current = pop_labels();
        printf("%s:\n", current.L_end);
        free(current.L_else);
        free(current.L_end);
    }
  |
    /* empty */
    {
        LabelPair current = pop_labels();
        printf("%s:\n", current.L_else);
        free(current.L_else);
        free(current.L_end);
    }
;

  
ifexpr:
    INTEGER_CONST { $$ = $1; }
  | IDENTIFIER {
         if(!is_declared($1)){
            char err[100];
            snprintf(err, sizeof(err),"Variable '%s' not declared", $1);
            semantic_error(err);
         }
         $$ = $1;
     }
  | conditional_statement { $$ = $1; }
  ;
  
iteration_statement:

  TK_WHILE LPAREN expression RPAREN TK_DO
  {
    
    W_Lstart = newlabel();
    W_Lend   = newlabel();
    W_tmpcond= newtemp();

    
    printf("%s:\n",             W_Lstart);
    printf("%s := %s\n",         W_tmpcond, $3);
    printf("if %s := 0 goto %s\n", W_tmpcond, W_Lend);
  }
  compound_statement
  {
   
    printf("goto %s\n", W_Lstart);
    printf("%s:\n",     W_Lend);
  }
  TK_SEP

  | 
    TK_WHILE expression TK_DO
  {
    W_Lstart = newlabel();
    W_Lend   = newlabel();
    W_tmpcond= newtemp();

    printf("%s:\n",             W_Lstart);
    printf("%s := %s\n",         W_tmpcond, $2);
    printf("if %s := 0 goto %s\n", W_tmpcond, W_Lend);
  }
  compound_statement
  {
    printf("goto %s\n", W_Lstart);
    printf("%s:\n",     W_Lend);
  }
  TK_SEP
  
  | 

TK_FOR LPAREN IDENTIFIER ASSIGN expression TK_TO expression optional_inc expression RPAREN TK_DO
{   //printf("%s %s %s %s %s %s %s %s %s\n" , $1 , $2 , $3 , $4 , $5 , $6 , $7 , $8 , $9); 
    F_var    = $3;              
    F_end    = $7;              
    F_inc    = $8 ? $9 : "1";   

    F_Lstart = newlabel();
    F_Lend   = newlabel();
    F_tmpcond= newtemp();

   
    printf("%s := %s\n", F_var, $5);

 
    printf("%s:\n",    F_Lstart);

    if (for_flag) {
      
      printf("%s := %s > %s\n", F_tmpcond, F_var, F_end);
    } else if(for_flag == 0) {
     
      printf("%s := %s < %s\n", F_tmpcond, F_var, F_end);
    }
    printf("if %s == 1 goto %s\n", F_tmpcond, F_Lend);
}
compound_statement
{
    if (for_flag) {
    
      printf("%s := %s + %s\n", F_var, F_var, F_inc);
    } else if(for_flag == 0) {
     
      printf("%s := %s - %s\n", F_var, F_var, F_inc);
    }
    printf("goto %s\n",     F_Lstart);
    printf("%s:\n",         F_Lend);
}
TK_SEP

|   
TK_FOR IDENTIFIER ASSIGN expression TK_TO expression optional_inc expression TK_DO
{   // printf("%s %s %s %s %s %s %s %s %s\n" , $1 , $2 , $3 , $4 , $5 , $6 , $7 , $8 , $9); 
    F_var    = $2;
    F_end    = $6;
    F_inc    = $7 ? $8 : "1";
    F_Lstart = newlabel();
    F_Lend   = newlabel();
    F_tmpcond= newtemp();


    printf("%s := %s\n", F_var, $4);

   
    printf("%s:\n",    F_Lstart);

    if (for_flag) {
    
      printf("%s := %s > %s\n", F_tmpcond, F_var, F_end);
    } else if(for_flag == 0) {
      
      printf("%s := %s < %s\n", F_tmpcond, F_var, F_end);
    }
    printf("if %s == 1 goto %s\n", F_tmpcond, F_Lend);
}
compound_statement
{
    if (for_flag) {
     
      printf("%s := %s + %s\n", F_var, F_var, F_inc);
    } else if(for_flag == 0) {
      
      printf("%s := %s - %s\n", F_var, F_var, F_inc);
    }
    printf("goto %s\n",     F_Lstart);
    printf("%s:\n",         F_Lend);
}
TK_SEP
;

 
optional_inc:
    { } 
  | TK_INC { $$ = $1;  }
  | TK_DEC { $$ = $1; }
  ;
expression:
    assignment_expression { $$ = $1; }
  | conditional_statement  { $$ = $1; }
  ;
assignment_expression:
    equality_expression { $$ = $1; }
  | IDENTIFIER assignment_operator assignment_expression {
         if(!is_declared($1)){
             char err[100];
             snprintf(err, sizeof(err),"Variable '%s' not declared", $1);
             semantic_error(err);
         }
         if($3 && $3[0]=='(') {
             int val, base;
             if(sscanf($3, "(%d,%d)", &val, &base)==2) {
                 printf("%s := %s\n", $1, $3);
             } else {
                 printf("%s := %s\n", $1, $3);
             }
         } else {
             printf("%s := %s\n", $1, $3);
         }
         $$ = $1;
     }
  ;
assignment_operator:
    ASSIGN
    { $$ = $1;
    }
    | PLUS_ASSIGN
    { $$ = $1;
    }
    | MINUS_ASSIGN
    { $$ = $1;
    }
    | MULT_ASSIGN
    { $$ = $1;
    }
    | DIV_ASSIGN
    { $$ = $1;
    }
    | MOD_ASSIGN
    { $$ = $1;
    }
    ;
equality_expression:
    relational_expression { $$ = $1; }
  ;
relational_expression:
    additive_expression { $$ = $1; }
  | additive_expression GT additive_expression {
         char *temp = newtemp();
         sprintf(temp, "%s > %s", $1, $3);
         $$ = temp;
     }
  | additive_expression LT additive_expression {
         char *temp = newtemp();
         sprintf(temp, "%s < %s", $1, $3);
         $$ = temp;
     }
  | additive_expression GE additive_expression {
         char *temp = newtemp();
         sprintf(temp, "%s >= %s", $1, $3);
         $$ = temp;
     }
  | additive_expression LE additive_expression {
         char *temp = newtemp();
         sprintf(temp, "%s <= %s", $1, $3);
         $$ = temp;
     }
  | additive_expression EQ additive_expression {
         char *temp = newtemp();
         sprintf(temp, "%s == %s", $1, $3);
         $$ = temp;
     }
  | additive_expression NE additive_expression {
         char *temp = newtemp();
         sprintf(temp, "%s != %s", $1, $3);
         $$ = temp;
     }
  ;
additive_expression:
    multiplicative_expression { $$ = $1; }
  | additive_expression PLUS multiplicative_expression {
         char *temp = newtemp();
         printf("%s := %s + %s\n", temp, $1, $3);
         $$ = temp;
     }
  | additive_expression MINUS multiplicative_expression {
         char *temp = newtemp();
         printf("%s := %s - %s\n", temp, $1, $3);
         $$ = temp;
     }
  ;
  
multiplicative_expression:
    unary_expression {  }
  | multiplicative_expression MULT unary_expression {
         char *temp = newtemp();
         printf("%s := %s * %s\n", temp, $1, $3);
         $$ = temp;
     }
  | multiplicative_expression DIV unary_expression {
         char *temp = newtemp();
         printf("%s := %s / %s\n", temp, $1, $3);
         $$ = temp;
     }
  | multiplicative_expression MOD unary_expression {
         char *temp = newtemp();
         printf("%s := %s %% %s\n", temp, $1, $3);
         $$ = temp;
     }
  ;
unary_expression:
    postfix_expression { $$ = $1; }
  | PLUS unary_expression %prec UNARY { $$ = $2; }
  | MINUS unary_expression %prec UNARY {
         char *temp = newtemp();
         printf("%s := 0 - %s\n", temp, $2);
         $$ = temp;
     }
  | TK_INC unary_expression { $$ = $2; }
  | TK_DEC unary_expression { $$ = $2; }
  ;
postfix_expression:
    primary_expression postfix_expression_tail { $$ = $1; }
  ;
postfix_expression_tail:
    {
    }
    | TK_INC   
    { for_flag = 1;
      //printf("I am in the %s for loop\n" ,  $1); 
    }
    | TK_DEC
    { for_flag = 0;
      //printf("I am in the %s for loop\n" ,  $1); 
    }
    ;
primary_expression:
    IDENTIFIER {
         if(!is_declared($1)){
             char err[100];
             snprintf(err, sizeof(err),"Variable '%s' not declared", $1);
             semantic_error(err);
         }
         $$ = $1;
     }
  | INTEGER_CONST { $$ = $1; }
  | CHAR_CONST { $$ = $1; }
  | LPAREN expression RPAREN { $$ = $2; }
  ;
%%
void yyerror(const char *s) { syntax_errors++; }
int main(int argc, char *argv[]) {
    if(argc != 2) {
         fprintf(stderr, "Usage: %s <input file>\n", argv[0]);
         return 1;
    }
    yyin = fopen(argv[1], "r");
    if(!yyin) { perror("Error opening file"); return 1; }
    print_lexeme_token_pairs = 0;
    output_printed = 0;
    syntax_errors = 0;
    semantic_errors = 0;
    temp_count = 0;
    label_count = 0;
    yyparse();
    fclose(yyin);
    return 0;
}
