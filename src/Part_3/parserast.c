#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parserast.h"
#include "symbol_table.h"

ASTNode* createNode(NodeType type) {
    ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));
    if (!node) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    node->type = type;
    node->next = NULL;

    node->data.children.left = NULL;
    node->data.children.right = NULL;
    return node;
}


ASTNode* createStrNode(NodeType type, const char* value) {
    ASTNode* node = createNode(type);
    node->data.strValue = strdup(value);
    return node;
}


ASTNode* createBinaryNode(NodeType type, ASTNode* left, ASTNode* right) {
    ASTNode* node = createNode(type);
    node->data.children.left = left;
    node->data.children.right = right;
    return node;
}


ASTNode* createTernaryNode(NodeType type, ASTNode* first, ASTNode* second, ASTNode* third) {
    ASTNode* node = createNode(type);
    node->data.ternary.first = first;
    node->data.ternary.second = second;
    node->data.ternary.third = third;
    return node;
}

ASTNode* createQuaternaryNode(NodeType type, ASTNode* first, ASTNode* second, ASTNode* third, ASTNode* fourth) {
    ASTNode* node = createNode(type);
    node->data.quaternary.first = first;
    node->data.quaternary.second = second;
    node->data.quaternary.third = third;
    node->data.quaternary.fourth = fourth;
    return node;
}


void printList(ASTNode* list) {
    ASTNode* current = list;
    while (current) {
        printf("%s -> ", current->data.strValue);
        current = current->next;
    }
    printf("NULL\n");
}


ASTNode* createIONode(NodeType type, ASTNode* format, ASTNode* args) {
    ASTNode* node = createNode(type);
    node->data.io.format = format;
    node->data.io.args = args;
    return node;
}


void addToList(ASTNode* list, ASTNode* node) {
    if (!list) return;
    
    ASTNode* current = list;
    while (current->next) {
        current = current->next;
    }
    current->next = node;
    node->next=NULL;
}

int valuetaker(ASTNode* node) {
    if (!node) return 0;

    switch (node->type) {
        case NODE_INT_LITERAL: {
            
            char* str = node->data.strValue;
            char* comma = strchr(str, '(');
            if (comma) {
                comma++;
                char* end = strchr(comma, ',');
                if (end) {
                    char value_str[32] = {0};
                    int len = end - comma;
                    if (len < 31) {
                        strncpy(value_str, comma, len);
                        value_str[len] = '\0';
                        return atoi(value_str);
                    }
                }
            }
            return atoi(node->data.strValue);
        }
        case NODE_IDENTIFIER: {
            Symbol* sym = lookupSymbol(node->data.strValue);
            if (sym && sym->initialized) {
                return atoi(sym->value);
            } else {
                printf("Runtime Error: Variable '%s' not initialized\n", node->data.strValue);
                return 0;
            }
        }
        default:
            return 0;
    }
}

int basetaker(ASTNode* node) {
    if (!node) return 0;

    switch (node->type) {
        case NODE_INT_LITERAL: {
            char* str = node->data.strValue;
            char* comma = strchr(str, ',');
            if (comma) {
                comma++;
                while (*comma == ' ') comma++;
                char* end = strchr(comma, ')');
                if (end) {
                    char base_str[32] = {0};
                    int len = end - comma;
                    if (len < 31) {
                        strncpy(base_str, comma, len);
                        base_str[len] = '\0';
                        return atoi(base_str);
                    }
                }
            }
            return 10; 
        }
        case NODE_IDENTIFIER: {
            Symbol* sym = lookupSymbol(node->data.strValue);
            if (sym && sym->initialized) {
                char* str = sym->value;
                char* comma = strchr(str, ',');
                if (comma) {
                    comma++;
                    while (*comma == ' ') comma++;
                    
                    char* end = strchr(comma, ')');
                    if (end) {
                        char base_str[32] = {0};
                        int len = end - comma;
                        if (len < 31) {
                            strncpy(base_str, comma, len);
                            base_str[len] = '\0';
                            return atoi(base_str);
                        }
                    }
                }
                return 10; 
            } else {
                printf("Runtime Error: Variable '%s' not initialized\n", node->data.strValue);
                return 0;
            }
        }
        default:
            return 0;
    }
}


void evaluate(ASTNode* node) {
    if (!node) return;

    switch (node->type) {
        case NODE_PROGRAM:
            // Evaluate the program body
            evaluate(node->data.children.left);
            break;
            
        case NODE_VARDECL_SECTION:
            // Skip variable declarations as they're already processed
            // Move to the next section (main section)
            evaluate(node->next);
            break;
            
        case NODE_MAIN_SECTION:
            // Evaluate the main section (statement list)
            evaluate(node->data.children.left);
            break;
            
        case NODE_STATEMENT_LIST:
            // Process current statement
            if (node->data.children.left) {
                evaluate(node->data.children.left);
            }
            
            break;

        case NODE_EXPR_STMT:
            // Evaluate the expression
            evaluate(node->data.children.left);
            break;

        case NODE_ASSIGN:
            // Execute the assignment
            executeAssignment(node);
            break;

        case NODE_PRINT_STMT:
            // Execute the print statement
            executePrint(node);
            break;
        
        default:
            printf("Unhandled node type: %d\n", node->type);
            break;
    }
    if (node->next) {
        evaluate(node->next);
    }
}

void executeAssignment(ASTNode* node) {
    if (!node) return;
    
    ASTNode* left = node->data.children.left;
    ASTNode* right = node->data.children.right;

    if (left->type != NODE_IDENTIFIER) return;

    ASTNode* temp = evaluateExpression(right);
    Symbol* sym = lookupSymbol(left->data.strValue);
    if (sym) {
        sprintf(sym->value, "%s", temp->data.strValue);
        markInitialized(sym->name);
    } else {
        printf("Semantic Error: Variable '%s' not declared\n", left->data.strValue);
    }
}

char* converttostring(int num){
    char* str = (char*)malloc(20);
    if (str) {
        sprintf(str, "%d", num);
    }
    return str;
}

int octaltoint(int num){
    int decimal = 0, base = 1, rem;
    while (num > 0) {
        rem = num % 10;
        decimal = decimal + rem * base;
        num = num / 10;
        base = base * 8;
    }
    return decimal;
}

int inttooctal(int num){
    int decimal = 0, base = 1, rem;
    while (num > 0) {
        rem = num % 8;
        decimal = decimal + rem * base;
        num = num / 8;
        base = base * 10;
    }
    return decimal;
}

int inttobinary(int num){
    int decimal = 0, base = 1, rem;
    while (num > 0) {
        rem = num % 2;
        decimal = decimal + rem * base;
        num = num / 2;
        base = base * 10;
    }
    return decimal;
}

int binarytoint(int num){
    int decimal = 0, base = 1, rem;
    while (num > 0) {
        rem = num % 10;
        decimal = decimal + rem * base;
        num = num / 10;
        base = base * 2;
    }
    return decimal;
}

ASTNode* evaluateExpression(ASTNode* node) {
    if (!node) return 0;

    switch (node->type) {
        case NODE_INT_LITERAL: {
                return node;
                break;
        }

        case NODE_IDENTIFIER: {
            Symbol* sym = lookupSymbol(node->data.strValue);
            if (sym && sym->initialized) {
                return node;
            } else {
                printf("Runtime Error: Variable '%s' not initialized\n", node->data.strValue);
                return NULL;
            }
            break;
        }

        case NODE_ADD:
        {
            printf("%d", valuetaker(node->data.children.left));
            if((basetaker(node->data.children.left) == basetaker(node->data.children.right)) && basetaker(node->data.children.left) == 10){
                int val1 = valuetaker(evaluateExpression((node->data.children.left)));
                int val2 = valuetaker(evaluateExpression((node->data.children.right)));
                int result = val1 + val2;
                char result_str[50];
                sprintf(result_str, "(%d,10)", result);
                return createStrNode(NODE_INT_LITERAL, result_str);
            }
            else if((basetaker(node->data.children.left) == basetaker(node->data.children.right)) && basetaker(node->data.children.left) == 8){
                int val1 = valuetaker(evaluateExpression((node->data.children.left)));
                int val2 = valuetaker(evaluateExpression((node->data.children.right)));
                int octval1= octaltoint(val1);
                int octval2= octaltoint(val2);
                int result = octval1 + octval2;
                int octalresult = inttooctal(result);
                char result_str[50];
                sprintf(result_str, "(%d,8)", octalresult);
                return createStrNode(NODE_INT_LITERAL, result_str);
            }
            else if((basetaker(node->data.children.left) == basetaker(node->data.children.right)) && basetaker(node->data.children.left) == 2){
                int val1 = valuetaker(evaluateExpression((node->data.children.left)));
                int val2 = valuetaker(evaluateExpression((node->data.children.right)));
                int binval1= binarytoint(val1);
                int binval2= binarytoint(val2);
                int result = binval1 + binval2;
                int binaryresult = inttobinary(result);
                char result_str[50];
                sprintf(result_str, "(%d,2)", binaryresult);
                return createStrNode(NODE_INT_LITERAL, result_str);
            }
            else{
                printf("Runtime Error: Type Mismatch\n");
                return 0;
            }
        }
        break;

        case NODE_SUB:
        {
            if((basetaker(node->data.children.left) == basetaker(node->data.children.right)) && basetaker(node->data.children.left) == 10){
                int val1 = valuetaker(evaluateExpression((node->data.children.left)));
                int val2 = valuetaker(evaluateExpression((node->data.children.right)));
                int result = val1 - val2;
                char result_str[50];
                sprintf(result_str, "(%d,10)", result);
                return createStrNode(NODE_INT_LITERAL, result_str);
            }
            else if((basetaker(node->data.children.left) == basetaker(node->data.children.right)) && basetaker(node->data.children.left) == 8){
                int val1 = valuetaker(evaluateExpression((node->data.children.left)));
                int val2 = valuetaker(evaluateExpression((node->data.children.right)));
                int octval1= octaltoint(val1);
                int octval2= octaltoint(val2);
                int result = octval1 - octval2;
                int octalresult = inttooctal(result);
                char result_str[50];
                sprintf(result_str, "(%d,8)", octalresult);
                return createStrNode(NODE_INT_LITERAL, result_str);
            }
            else if((basetaker(node->data.children.left) == basetaker(node->data.children.right)) && basetaker(node->data.children.left) == 2){
                int val1 = valuetaker(evaluateExpression((node->data.children.left)));
                int val2 = valuetaker(evaluateExpression((node->data.children.right)));
                int binval1= binarytoint(val1);
                int binval2= binarytoint(val2);
                int result = binval1 - binval2;
                int binaryresult = inttobinary(result);
                char result_str[50];
                sprintf(result_str, "(%d,2)", binaryresult);
                return createStrNode(NODE_INT_LITERAL, result_str);
            }
            else{
                printf("Runtime Error: Type Mismatch\n");
                return 0;
            }
        }
        break; 

        case NODE_MUL:
        {
            if((basetaker(node->data.children.left) == basetaker(node->data.children.right)) && basetaker(node->data.children.left) == 10){
                int val1 = valuetaker(evaluateExpression((node->data.children.left)));
                int val2 = valuetaker(evaluateExpression((node->data.children.right)));
                int result = val1 * val2;
                char result_str[50];
                sprintf(result_str, "(%d,10)", result);
                return createStrNode(NODE_INT_LITERAL, result_str);
            }
            else if((basetaker(node->data.children.left) == basetaker(node->data.children.right)) && basetaker(node->data.children.left) == 8){
                int val1 = valuetaker(evaluateExpression((node->data.children.left)));
                int val2 = valuetaker(evaluateExpression((node->data.children.right)));
                int octval1= octaltoint(val1);
                int octval2= octaltoint(val2);
                int result = octval1 * octval2;
                int octalresult = inttooctal(result);
                char result_str[50];
                sprintf(result_str, "(%d,8)", octalresult);
                return createStrNode(NODE_INT_LITERAL, result_str);
            }
            else if((basetaker(node->data.children.left) == basetaker(node->data.children.right)) && basetaker(node->data.children.left) == 2){
                int val1 = valuetaker(evaluateExpression((node->data.children.left)));
                int val2 = valuetaker(evaluateExpression((node->data.children.right)));
                int binval1= binarytoint(val1);
                int binval2= binarytoint(val2);
                int result = binval1 * binval2;
                int binaryresult = inttobinary(result);
                char result_str[50];
                sprintf(result_str, "(%d,2)", binaryresult);
                return createStrNode(NODE_INT_LITERAL, result_str);
            }
            else{
                printf("Runtime Error: Type Mismatch\n");
                return 0;
            }
        }
        break;

        case NODE_DIV: {
            if(valuetaker(evaluateExpression(node->data.children.right ))==0){
                printf("Runtime Error: Division by zero\n");
                return 0;
            } 
                if((basetaker(node->data.children.left) == basetaker(node->data.children.right)) && basetaker(node->data.children.left) == 10){
                    int val1 = valuetaker(evaluateExpression((node->data.children.left)));
                    int val2 = valuetaker(evaluateExpression((node->data.children.right)));
                    int result = val1 / val2;
                    char result_str[50];
                    sprintf(result_str, "(%d,10)", result);
                    return createStrNode(NODE_INT_LITERAL, result_str);
                }
                else if((basetaker(node->data.children.left) == basetaker(node->data.children.right)) && basetaker(node->data.children.left) == 8){
                    int val1 = valuetaker(evaluateExpression((node->data.children.left)));
                    int val2 = valuetaker(evaluateExpression((node->data.children.right)));
                    int octval1= octaltoint(val1);
                    int octval2= octaltoint(val2);
                    int result = octval1 / octval2;
                    int octalresult = inttooctal(result);
                    char result_str[50];
                    sprintf(result_str, "(%d,8)", octalresult);
                    return createStrNode(NODE_INT_LITERAL, result_str);
                }
                else if((basetaker(node->data.children.left) == basetaker(node->data.children.right)) && basetaker(node->data.children.left) == 2){
                    int val1 = valuetaker(evaluateExpression((node->data.children.left)));
                    int val2 = valuetaker(evaluateExpression((node->data.children.right)));
                    int binval1= binarytoint(val1);
                    int binval2= binarytoint(val2);
                    int result = binval1 / binval2;
                    int binaryresult = inttobinary(result);
                    char result_str[50];
                    sprintf(result_str, "(%d,2)", binaryresult);
                    return createStrNode(NODE_INT_LITERAL, result_str);
                }
                else{
                    printf("Runtime Error: Type Mismatch\n");
                    return 0;
                }
            }
            break;

        default:
            return 0;
    }
}

void executePrint(ASTNode* node) {
    if (!node) return;
    
    ASTNode* format = node->data.io.format;
    ASTNode* args = node->data.io.args;

    printf("%s ", format->data.strValue);

    while (args) {
        if (args->type == NODE_IDENTIFIER) {
            Symbol* sym = lookupSymbol(args->data.strValue);
            if (sym && sym->initialized) {
                printf("%s ", sym->value);
            } else {
                printf("?");
            }
        } else if (args->type == NODE_INT_LITERAL) {
            printf("%s ", args->data.strValue);
        } else {
            printf("%s ", evaluateExpression(args)->data.strValue);
        }

        args = args->next;
    }

    printf("\n");
}

const char* getNodeTypeName(NodeType type) {
    switch (type) {
        case NODE_PROGRAM: return "";
        case NODE_VARDECL_SECTION: return "";
        case NODE_MAIN_SECTION: return "";
        case NODE_STATEMENT_LIST: return "";
        case NODE_VARDECL: return "";
        case NODE_TYPE_INT: return "int";
        case NODE_TYPE_CHAR: return "char";
        case NODE_COMPOUND_STMT: return "";
        case NODE_IF_STMT: return "if";
        case NODE_IF_ELSE_STMT: return "if-else";
        case NODE_WHILE_STMT: return "while";
        case NODE_FOR_STMT: return "for";
        case NODE_DO_WHILE_STMT: return "do-while";
        case NODE_PRINT_STMT: return "print";
        case NODE_SCAN_STMT: return "scan";
        case NODE_EXPR_STMT: return "";
        case NODE_ASSIGN: return ":=";
        case NODE_PLUS_ASSIGN: return "+=";
        case NODE_MINUS_ASSIGN: return "-=";
        case NODE_MULT_ASSIGN: return "*=";
        case NODE_DIV_ASSIGN: return "/=";
        case NODE_MOD_ASSIGN: return "%=";
        case NODE_EQ: return "=";
        case NODE_NE: return "<>";
        case NODE_LT: return "<";
        case NODE_GT: return ">";
        case NODE_LE: return "<=";
        case NODE_GE: return ">=";
        case NODE_ADD: return "+";
        case NODE_SUB: return "-";
        case NODE_MUL: return "*";
        case NODE_DIV: return "/";
        case NODE_MOD: return "%";
        case NODE_UNARY_PLUS: return "";
        case NODE_UNARY_MINUS: return "";
        case NODE_PRE_INC: return "";
        case NODE_PRE_DEC: return "";
        case NODE_POST_INC: return "";
        case NODE_POST_DEC: return "";
        case NODE_IDENTIFIER: return "";
        case NODE_INT_LITERAL: return "";
        case NODE_CHAR_LITERAL: return "";
        case NODE_STRING_LITERAL: return "";
        default: return "UNKNOWN";
    }
}


void printAST(ASTNode* node, int indent) {
    if (!node) {
        printf("()");
        return;
    }
    
    printf("(");
    

    const char* typeName = getNodeTypeName(node->type);
    
    if (strlen(typeName) > 0) {
        printf("%s", typeName);
    }
    

    switch (node->type) {
        case NODE_IDENTIFIER:
        case NODE_INT_LITERAL:
        case NODE_CHAR_LITERAL:
        case NODE_STRING_LITERAL:
            printf("%s", node->data.strValue);
            break;
        default:
            break;
    }
    

    switch (node->type) {
        case NODE_PROGRAM:
        case NODE_VARDECL_SECTION:
        case NODE_MAIN_SECTION:
        case NODE_STATEMENT_LIST:
        case NODE_COMPOUND_STMT:

            if (node->data.children.left) {
                printf(" ");
                printAST(node->data.children.left, indent + 1);
            }
            break;
            
        case NODE_IF_STMT:
            if (node->data.children.left) {
                printf(" ");
                printAST(node->data.children.left, indent + 1);
            }
            if (node->data.children.right) {
                printf(" ");
                printAST(node->data.children.right, indent + 1);
            }
            break;
        
        case NODE_WHILE_STMT:
        case NODE_EXPR_STMT:
        case NODE_VARDECL:
        case NODE_ASSIGN:
        case NODE_PLUS_ASSIGN:
        case NODE_MINUS_ASSIGN:
        case NODE_MULT_ASSIGN:
        case NODE_DIV_ASSIGN:
        case NODE_MOD_ASSIGN:
        case NODE_EQ:
        case NODE_NE:
        case NODE_LT:
        case NODE_GT:
        case NODE_LE:
        case NODE_GE:
        case NODE_ADD:
        case NODE_SUB:
        case NODE_MUL:
        case NODE_DIV:
        case NODE_MOD:
        case NODE_UNARY_PLUS:
        case NODE_UNARY_MINUS:
        case NODE_PRE_INC:
        case NODE_PRE_DEC:
        case NODE_POST_INC:
        case NODE_POST_DEC:

            if (node->data.children.left) {
                printf(" ");
                printAST(node->data.children.left, indent + 1);
            }
            if (node->data.children.right) {
                printf(" ");
                printAST(node->data.children.right, indent + 1);
            }
            break;
            
        case NODE_IF_ELSE_STMT:
            if (node->data.ternary.first) {
                printf(" ");
                printAST(node->data.ternary.first, indent + 1);
            }
            if (node->data.ternary.second) {
                printf(" ");
                printAST(node->data.ternary.second, indent + 1);
            }
            if (node->data.ternary.third) {
                printf(" ");
                printAST(node->data.ternary.third, indent + 1);
            }
            break;
             
        case NODE_FOR_STMT:
        case NODE_DO_WHILE_STMT:

            if (node->data.ternary.first) {
                printf(" ");
                printAST(node->data.ternary.first, indent + 1);
            }
            if (node->data.ternary.second) {
                printf(" ");
                printAST(node->data.ternary.second, indent + 1);
            }
            if (node->data.ternary.third) {
                printf(" ");
                printAST(node->data.ternary.third, indent + 1);
            }
            break;
            
            case NODE_SCAN_STMT:
            case NODE_PRINT_STMT:
                if (node->data.io.format) {
                    printf(" ");
                    printAST(node->data.io.format, indent + 1);
                }
                if (node->data.io.args) {
                    printf(" ");
                    ASTNode* current = node->data.io.args;
                    printf("(args ");
                    if (current) {
                        printAST(current, indent + 2);
                        current = current->next;
                        if (current) printf(" ");
                    }
                    printf(")");
                }
                break;
        default:
            break;
    }
    
    printf(")");
    
    if (node->next) {
        printf(" ");
        printAST(node->next, indent);
    }
}

void freeAST(ASTNode* node) {
    if (!node) return;
    
    switch (node->type) {
        case NODE_IDENTIFIER:
        case NODE_INT_LITERAL:
        case NODE_CHAR_LITERAL:
        case NODE_STRING_LITERAL:
            free(node->data.strValue);
            break;
            
        case NODE_PROGRAM:
        case NODE_VARDECL_SECTION:
        case NODE_MAIN_SECTION:
        case NODE_STATEMENT_LIST:
        case NODE_COMPOUND_STMT:
        case NODE_IF_STMT:
        case NODE_WHILE_STMT:
        case NODE_EXPR_STMT:
        case NODE_VARDECL:
        case NODE_ASSIGN:
        case NODE_PLUS_ASSIGN:
        case NODE_MINUS_ASSIGN:
        case NODE_MULT_ASSIGN:
        case NODE_DIV_ASSIGN:
        case NODE_MOD_ASSIGN:
        case NODE_EQ:
        case NODE_NE:
        case NODE_LT:
        case NODE_GT:
        case NODE_LE:
        case NODE_GE:
        case NODE_ADD:
        case NODE_SUB:
        case NODE_MUL:
        case NODE_DIV:
        case NODE_MOD:
        case NODE_UNARY_PLUS:
        case NODE_UNARY_MINUS:
        case NODE_PRE_INC:
        case NODE_PRE_DEC:
        case NODE_POST_INC:
        case NODE_POST_DEC:
            freeAST(node->data.children.left);
            freeAST(node->data.children.right);
            break;
            
        case NODE_IF_ELSE_STMT:
        case NODE_FOR_STMT:
        case NODE_DO_WHILE_STMT:
            freeAST(node->data.ternary.first);
            freeAST(node->data.ternary.second);
            freeAST(node->data.ternary.third);
            break;
            
        case NODE_PRINT_STMT:
        case NODE_SCAN_STMT:
            freeAST(node->data.io.format);
            freeAST(node->data.io.args);
            break;
    }
    
    ASTNode* next = node->next;
    
    free(node);
    
    freeAST(next);
}

