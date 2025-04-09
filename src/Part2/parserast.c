#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parserast.h"

/* Create a simple AST node */
ASTNode* createNode(NodeType type) {
    ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));
    if (!node) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    node->type = type;
    node->next = NULL;
    /* Initialize all fields to NULL */
    node->data.children.left = NULL;
    node->data.children.right = NULL;
    return node;
}

/* Create a node with string value (for identifiers and literals) */
ASTNode* createStrNode(NodeType type, const char* value) {
    ASTNode* node = createNode(type);
    node->data.strValue = strdup(value);
    return node;
}

/* Create a binary operation node */
ASTNode* createBinaryNode(NodeType type, ASTNode* left, ASTNode* right) {
    ASTNode* node = createNode(type);
    node->data.children.left = left;
    node->data.children.right = right;
    return node;
}

/* Create a ternary operation node */
ASTNode* createTernaryNode(NodeType type, ASTNode* first, ASTNode* second, ASTNode* third) {
    ASTNode* node = createNode(type);
    node->data.ternary.first = first;
    node->data.ternary.second = second;
    node->data.ternary.third = third;
    return node;
}

ASTNode* createQuaternaryNode(NodeType type, ASTNode* first, ASTNode* second, ASTNode* third,ASTNode * fourth) {
    ASTNode* node = createNode(type);
    node->data.quaternary.first = first;
    node->data.quaternary.second = second;
    node->data.quaternary.third = third;
    node->data.quaternary.fourth = fourth;
    return node;
}

//Create a function to print linked list
void printList(ASTNode* list) {
    ASTNode* current = list;
    while (current) {
        printf("%s -> ", current->data.strValue);
        current = current->next;
    }
    printf("NULL\n");
}

/* Create a node for print/scan operations */
ASTNode* createIONode(NodeType type, ASTNode* format, ASTNode* args) {
    ASTNode* node = createNode(type);
    node->data.io.format = format;
    node->data.io.args = args;
    return node;
}

/* Add a node to a list of nodes */
void addToList(ASTNode* list, ASTNode* node) {
    if (!list) return;
    
    ASTNode* current = list;
    while (current->next) {
        current = current->next;
    }
    current->next = node;
}

/* Get a string representation of node type */
const char* getNodeTypeName(NodeType type) {
    switch (type) {
        case NODE_PROGRAM: return "PROGRAM";
        case NODE_VARDECL_SECTION: return "VARDECL_SECTION";
        case NODE_MAIN_SECTION: return "MAIN_SECTION";
        case NODE_STATEMENT_LIST: return "STATEMENT_LIST";
        case NODE_VARDECL: return "VARDECL";
        case NODE_TYPE_INT: return "TYPE_INT";
        case NODE_TYPE_CHAR: return "TYPE_CHAR";
        case NODE_COMPOUND_STMT: return "COMPOUND_STMT";
        case NODE_IF_STMT: return "IF_STMT";
        case NODE_IF_ELSE_STMT: return "IF_ELSE_STMT";
        case NODE_WHILE_STMT: return "WHILE_STMT";
        case NODE_FOR_STMT: return "FOR_STMT";
        case NODE_DO_WHILE_STMT: return "DO_WHILE_STMT";
        case NODE_PRINT_STMT: return "PRINT_STMT";
        case NODE_SCAN_STMT: return "SCAN_STMT";
        case NODE_EXPR_STMT: return "EXPR_STMT";
        case NODE_ASSIGN: return "ASSIGN";
        case NODE_PLUS_ASSIGN: return "PLUS_ASSIGN";
        case NODE_MINUS_ASSIGN: return "MINUS_ASSIGN";
        case NODE_MULT_ASSIGN: return "MULT_ASSIGN";
        case NODE_DIV_ASSIGN: return "DIV_ASSIGN";
        case NODE_MOD_ASSIGN: return "MOD_ASSIGN";
        case NODE_EQ: return "EQ";
        case NODE_NE: return "NE";
        case NODE_LT: return "LT";
        case NODE_GT: return "GT";
        case NODE_LE: return "LE";
        case NODE_GE: return "GE";
        case NODE_ADD: return "ADD";
        case NODE_SUB: return "SUB";
        case NODE_MUL: return "MUL";
        case NODE_DIV: return "DIV";
        case NODE_MOD: return "MOD";
        case NODE_UNARY_PLUS: return "UNARY_PLUS";
        case NODE_UNARY_MINUS: return "UNARY_MINUS";
        case NODE_PRE_INC: return "PRE_INC";
        case NODE_PRE_DEC: return "PRE_DEC";
        case NODE_POST_INC: return "POST_INC";
        case NODE_POST_DEC: return "POST_DEC";
        case NODE_IDENTIFIER: return "IDENTIFIER";
        case NODE_INT_LITERAL: return "INT_LITERAL";
        case NODE_CHAR_LITERAL: return "CHAR_LITERAL";
        case NODE_STRING_LITERAL: return "STRING_LITERAL";
        default: return "UNKNOWN";
    }
}

/* Print spaces for indentation */
void printIndent(int indent) {
    for (int i = 0; i < indent; i++) {
        printf("  ");
    }
}

/* Print the AST recursively */
void printAST(ASTNode* node, int indent) {
    if (!node) return;
    
    printIndent(indent);
    printf("%s", getNodeTypeName(node->type));
    
    switch (node->type) {
        case NODE_IDENTIFIER:
        case NODE_INT_LITERAL:
        case NODE_CHAR_LITERAL:
        case NODE_STRING_LITERAL:
            printf(": %s", node->data.strValue);
            break;
        default:
            break;
    }
    printf("\n");
    
    /* Print children based on node type */
    switch (node->type) {
        case NODE_PROGRAM:
        case NODE_VARDECL_SECTION:
        case NODE_MAIN_SECTION:
        case NODE_STATEMENT_LIST:
        case NODE_COMPOUND_STMT:
            /* Print linked list of children */
            if (node->data.children.left) {
                printAST(node->data.children.left, indent + 1);
            }
            break;
            
        case NODE_IF_STMT:
            printIndent(indent + 1);
            printf("CONDITION\n");
            printAST(node->data.children.left, indent + 2);
            printIndent(indent + 1);
            printf("IF BLOCK\n");
            printAST(node->data.children.right, indent + 2);
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
            /* Print binary nodes */
            if (node->data.children.left) {
                printAST(node->data.children.left, indent + 1);
            }
            if (node->data.children.right) {
                printAST(node->data.children.right, indent + 1);
            }
            break;
            
            

        case NODE_IF_ELSE_STMT:
            printIndent(indent + 1);
            printf("CONDITION\n");
            printAST(node->data.ternary.first, indent + 2);
            printIndent(indent + 1);
            printf("IF BLOCK\n");
            printAST(node->data.ternary.second, indent + 2);
            printIndent(indent + 1);
            printf("ELSE BLOCK\n");
            printAST(node->data.ternary.third, indent + 2);
            break;
             
        case NODE_FOR_STMT:
        case NODE_DO_WHILE_STMT:
            /* Print ternary nodes */
            if (node->data.ternary.first) {
                printAST(node->data.ternary.first, indent + 1);
            }
            if (node->data.ternary.second) {
                printAST(node->data.ternary.second, indent + 1);
            }
            if (node->data.ternary.third) {
                printAST(node->data.ternary.third, indent + 1);
            }
            break;
            
        case NODE_PRINT_STMT:
        case NODE_SCAN_STMT:
            /* Print IO nodes */
            if (node->data.io.format) {
                printIndent(indent + 1);
                printf("FORMAT:\n");
                printAST(node->data.io.format, indent + 2);
            }
            if (node->data.io.args) {
                printIndent(indent + 1);
                printf("ARGS:\n");
                
                /* Print argument list */
                ASTNode* current = node->data.io.args;
                if (current) {
                    printAST(current, indent + 2);
                }
            }
            break;
            
        default:
            break;
    }
    
    /* Print next node in the list */
    if (node->next) {
        printAST(node->next, indent);
    }
}

/* Free the AST memory */
void freeAST(ASTNode* node) {
    if (!node) return;
    
    /* First, free children based on node type */
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
    
    /* Free next node in the list */
    ASTNode* next = node->next;
    
    /* Free the current node */
    free(node);
    
    /* Free the rest of the list */
    freeAST(next);
}