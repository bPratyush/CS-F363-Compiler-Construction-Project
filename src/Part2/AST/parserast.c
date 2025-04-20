#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parserast.h"


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