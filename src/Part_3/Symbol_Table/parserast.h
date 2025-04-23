#ifndef PARSER4_H
#define PARSER4_H

typedef enum {
    /* Program structure nodes */
    NODE_PROGRAM,
    NODE_VARDECL_SECTION,
    NODE_MAIN_SECTION,
    NODE_STATEMENT_LIST,
    
    /* Declaration nodes */
    NODE_VARDECL,
    NODE_TYPE_INT,
    NODE_TYPE_CHAR,
    
    /* Statement nodes */
    NODE_COMPOUND_STMT,
    NODE_IF_STMT,
    NODE_IF_ELSE_STMT,
    NODE_WHILE_STMT,
    NODE_FOR_STMT,
    NODE_DO_WHILE_STMT,
    NODE_PRINT_STMT,
    NODE_SCAN_STMT,
    NODE_EXPR_STMT,
    
    /* Expression nodes */
    NODE_ASSIGN,
    NODE_PLUS_ASSIGN,
    NODE_MINUS_ASSIGN,
    NODE_MULT_ASSIGN,
    NODE_DIV_ASSIGN,
    NODE_MOD_ASSIGN,
    
    /* Binary operation nodes */
    NODE_EQ,
    NODE_NE,
    NODE_LT,
    NODE_GT,
    NODE_LE,
    NODE_GE,
    NODE_ADD,
    NODE_SUB,
    NODE_MUL,
    NODE_DIV,
    NODE_MOD,
    
    /* Unary operation nodes */
    NODE_UNARY_PLUS,
    NODE_UNARY_MINUS,
    NODE_PRE_INC,
    NODE_PRE_DEC,
    NODE_POST_INC,
    NODE_POST_DEC,
    
    /* Terminal nodes */
    NODE_IDENTIFIER,
    NODE_INT_LITERAL,
    NODE_CHAR_LITERAL,
    NODE_STRING_LITERAL
} NodeType;

/* AST node structure */
typedef struct ASTNode {
    NodeType type;
    union {
        char* strValue;           /* For identifiers and literals */
        struct {                  /* For nodes with children */
            struct ASTNode* left;
            struct ASTNode* right;
        } children;
        struct {                  /* For nodes with more than two children */
            struct ASTNode* first;
            struct ASTNode* second;
            struct ASTNode* third;
        } ternary;
        struct {                  /* For nodes with more than two children */
            struct ASTNode* first;
            struct ASTNode* second;
            struct ASTNode* third;
            struct ASTNode * fourth;
        } quaternary;
        
        struct {                  /* For print/scan statements with multiple args */
            struct ASTNode* format;
            struct ASTNode* args;
        } io;
    } data;
    struct ASTNode* next;         /* For linked lists of nodes */
} ASTNode;

/* AST manipulation functions */
ASTNode* createNode(NodeType type);
ASTNode* createStrNode(NodeType type, const char* value);
ASTNode* createBinaryNode(NodeType type, ASTNode* left, ASTNode* right);
ASTNode* createTernaryNode(NodeType type, ASTNode* first, ASTNode* second, ASTNode* third);
ASTNode* createQuaternaryNode(NodeType type, ASTNode* first, ASTNode* second, ASTNode* third,ASTNode * fourth);
ASTNode* createIONode(NodeType type, ASTNode* format, ASTNode* args);
void addToList(ASTNode* list, ASTNode* node);
void printAST(ASTNode* node, int indent);
void freeAST(ASTNode* node);
void evaluate(ASTNode* node);
void executeAssignment(ASTNode* node);
ASTNode* evaluateExpression(ASTNode* node);
void executePrint(ASTNode* node);
#endif /* PARSER2_H */