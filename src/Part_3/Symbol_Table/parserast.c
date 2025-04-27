#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parserast.h"
#include "symbol_table.h"

ASTNode *createNode(NodeType type)
{
    ASTNode *node = (ASTNode *)malloc(sizeof(ASTNode));
    if (!node)
    {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    node->type = type;
    node->next = NULL;

    node->data.children.left = NULL;
    node->data.children.right = NULL;
    return node;
}

ASTNode *createStrNode(NodeType type, const char *value)
{
    ASTNode *node = createNode(type);
    node->data.strValue = strdup(value);
    return node;
}

ASTNode *createBinaryNode(NodeType type, ASTNode *left, ASTNode *right)
{
    ASTNode *node = createNode(type);
    node->data.children.left = left;
    node->data.children.right = right;
    return node;
}

ASTNode *createTernaryNode(NodeType type, ASTNode *first, ASTNode *second, ASTNode *third)
{
    ASTNode *node = createNode(type);
    node->data.ternary.first = first;
    node->data.ternary.second = second;
    node->data.ternary.third = third;
    return node;
}

ASTNode *createQuaternaryNode(NodeType type, ASTNode *first, ASTNode *second, ASTNode *third, ASTNode *fourth)
{
    ASTNode *node = createNode(type);
    node->data.quaternary.first = first;
    node->data.quaternary.second = second;
    node->data.quaternary.third = third;
    node->data.quaternary.fourth = fourth;
    return node;
}

void printList(ASTNode *list)
{
    ASTNode *current = list;
    while (current)
    {
        printf("%s -> ", current->data.strValue);
        current = current->next;
    }
    printf("NULL");
}

ASTNode *createIONode(NodeType type, ASTNode *format, ASTNode *args)
{
    ASTNode *node = createNode(type);
    node->data.io.format = format;
    node->data.io.args = args;
    return node;
}

void addToList(ASTNode *list, ASTNode *node)
{
    if (!list)
        return;

    ASTNode *current = list;
    while (current->next)
    {
        current = current->next;
    }
    current->next = node;
    node->next = NULL;
}

int octaltoint(int num)
{
    int decimal = 0, base = 1, rem;
    while (num > 0)
    {
        rem = num % 10;
        decimal = decimal + rem * base;
        num = num / 10;
        base = base * 8;
    }
    return decimal;
}

int inttooctal(int num)
{
    int decimal = 0, base = 1, rem;
    while (num > 0)
    {
        rem = num % 8;
        decimal = decimal + rem * base;
        num = num / 8;
        base = base * 10;
    }
    return decimal;
}

int inttobinary(int num)
{
    int decimal = 0, base = 1, rem;
    while (num > 0)
    {
        rem = num % 2;
        decimal = decimal + rem * base;
        num = num / 2;
        base = base * 10;
    }
    return decimal;
}

int binarytoint(int num)
{
    int decimal = 0, base = 1, rem;
    while (num > 0)
    {
        rem = num % 10;
        decimal = decimal + rem * base;
        num = num / 10;
        base = base * 2;
    }
    return decimal;
}

int valuetaker(ASTNode *node)
{
    if (!node)
        return 0;

    switch (node->type)
    {
    case NODE_INT_LITERAL:
    {
        char *str = node->data.strValue;
        char *comma = strchr(str, '(');
        if (comma)
        {
            comma++;
            char *end = strchr(comma, ',');
            if (end)
            {
                char value_str[32] = {0};
                int len = end - comma;
                if (len < 31)
                {
                    strncpy(value_str, comma, len);
                    value_str[len] = '\0';
                    return atoi(value_str);
                }
            }
        }
        return atoi(node->data.strValue);
    }
    case NODE_IDENTIFIER:
    {
        Symbol *sym = lookupSymbol(node->data.strValue);
        if (sym && sym->initialized)
        {
            char *str = sym->value;
            char *comma = strchr(str, '(');
            if (comma)
            {
                comma++;
                char *end = strchr(comma, ',');
                if (end)
                {
                    char value_str[32] = {0};
                    int len = end - comma;
                    if (len < 31)
                    {
                        strncpy(value_str, comma, len);
                        value_str[len] = '\0';
                        return atoi(value_str);
                    }
                }
            }
            return atoi(sym->value);
        }
        else
        {
            return 0;
        }
    }
    default:
        return 0;
    }
}

int basetaker(ASTNode *node)
{
    if (!node)
        return 0;

    switch (node->type)
    {
    case NODE_INT_LITERAL:
    {
        char *str = node->data.strValue;
        char *comma = strchr(str, ',');
        if (comma)
        {
            comma++;
            while (*comma == ' ')
                comma++;
            char *end = strchr(comma, ')');
            if (end)
            {
                char base_str[32] = {0};
                int len = end - comma;
                if (len < 31)
                {
                    strncpy(base_str, comma, len);
                    base_str[len] = '\0';
                    return atoi(base_str);
                }
            }
        }
        return 10;
    }
    case NODE_IDENTIFIER:
    {
        Symbol *sym = lookupSymbol(node->data.strValue);
        if (sym && sym->initialized)
        {
            char *str = sym->value;
            char *comma = strchr(str, ',');
            if (comma)
            {
                comma++;
                while (*comma == ' ')
                    comma++;

                char *end = strchr(comma, ')');
                if (end)
                {
                    char base_str[32] = {0};
                    int len = end - comma;
                    if (len < 31)
                    {
                        strncpy(base_str, comma, len);
                        base_str[len] = '\0';
                        return atoi(base_str);
                    }
                }
            }
            return 10;
        }
        else
        {
            return 0;
        }
    }
    default:
        return 0;
    }
}

void evaluate(ASTNode *node)
{
    if (!node)
        return;
    switch (node->type)
    {
    case NODE_PROGRAM:
        evaluate(node->data.children.left);
        break;

    case NODE_VARDECL_SECTION:
        evaluate(node->next);
        return;
        break;

    case NODE_MAIN_SECTION:
        evaluate(node->data.children.left);
        break;

    case NODE_STATEMENT_LIST:
        if (node->data.children.left)
        {
            evaluate(node->data.children.left);
        }
        break;

    case NODE_EXPR_STMT:
        evaluate(node->data.children.left);
        break;

    case NODE_ASSIGN:
        executeAssignment(node);
        break;

    case NODE_PRINT_STMT:
        break;

    case NODE_PLUS_ASSIGN:
    case NODE_MINUS_ASSIGN:
    case NODE_MULT_ASSIGN:
    case NODE_DIV_ASSIGN:
        evaluateExpression(node);
        break;

    case NODE_POST_DEC:
    case NODE_POST_INC:
    case NODE_PRE_DEC:
    case NODE_PRE_INC:
        evaluateExpression(node);
        break;

    case NODE_UNARY_MINUS:
    case NODE_UNARY_PLUS:
        evaluateExpression(node);
        break;
    case NODE_COMPOUND_STMT:
        if (node->data.children.left)
        {
            evaluate(node->data.children.left);
        }
        break;

    case NODE_IF_STMT:
    {
        ASTNode *condition = node->data.children.left;
        ASTNode *thenBlock = node->data.children.right;
        ASTNode *result = evaluateExpression(condition);
        if (!result)
        {
            printf("Runtime Error\n");
            exit(1);
        }
        if (valuetaker(result) != 0)
        {
            evaluate(thenBlock);
        }
    }
    break;

    case NODE_IF_ELSE_STMT:
    {
        ASTNode *condition = node->data.ternary.first;
        ASTNode *thenBlock = node->data.ternary.second;
        ASTNode *elseBlock = node->data.ternary.third;
        if (!condition)
        {
            printf("Runtime Error\n");
            exit(1);
        }
        ASTNode *result = evaluateExpression(condition);
        if (!result)
        {
            printf("Runtime Error\n");
            exit(1);
        }

        if (valuetaker(result) != 0)
        {
            if (!thenBlock)
            {
                printf("Runtime Error\n");
                exit(1);
            }
            evaluate(thenBlock);
        }
        else
        {
            if (!elseBlock)
            {
                printf("Runtime Error\n");
                exit(1);
            }
            else
            {
                ASTNode *current = elseBlock;
                while (current)
                {
                    current = current->next;
                }
                evaluate(elseBlock);
            }
        }
    }
    break;
    case NODE_WHILE_STMT:
    {
        ASTNode * condition = node->data.children.left;
        ASTNode * body = node->data.children.right;
        while (valuetaker(evaluateExpression(condition))!= 0)
        {
        evaluate(body);
        }
    }
    break;
    case NODE_FOR_STMT:
{
    ASTNode *initNode = node->data.ternary.first;     
    ASTNode *upperLimit = node->data.ternary.second;  
    ASTNode *body = node->data.ternary.third;         

    evaluate(initNode);
 
    ASTNode *lowerLimit = initNode->data.children.left;
    Symbol *loopVarSym = lookupSymbol(lowerLimit->data.strValue);
    if (!loopVarSym || !loopVarSym->initialized) {
        printf("Runtime Error\n");
        exit(1);
    }
    
    int lowerLimitVal = valuetaker(lowerLimit);
    int lowerLimitBase = basetaker(lowerLimit);
    if (lowerLimitBase == 8) {
        lowerLimitVal = octaltoint(lowerLimitVal);
    } else if (lowerLimitBase == 2) {
        lowerLimitVal = binarytoint(lowerLimitVal);
    }
    ASTNode *upperLimitLit = evaluateExpression(upperLimit);
    int upperLimitVal = valuetaker(upperLimitLit);
    int upperLimitBase = basetaker(upperLimitLit);
    if (upperLimitBase == 8) {
        upperLimitVal = octaltoint(upperLimitVal);
    } else if (upperLimitBase == 2) {
        upperLimitVal = binarytoint(upperLimitVal);
    }
    int stepVal = 1; 
    int stepBase = 10;
    ASTNode *stepExpr = NULL;
    if (upperLimit->next) {
        stepExpr = evaluateExpression(upperLimit->next->data.children.left);
        stepVal = valuetaker(stepExpr);
        stepBase = basetaker(stepExpr);
        if (stepBase == 8) {
            stepVal = octaltoint(stepVal);
        } else if (stepBase == 2) {
            stepVal = binarytoint(stepVal);
        }
    }

    if( (lowerLimitBase!= upperLimitBase) || (stepBase!=lowerLimitBase) || (stepBase!=upperLimitBase)){
        printf("Runtime Error\n");
        exit(1);
    }
    int i = lowerLimitVal;
    if(upperLimit->next->type==35){
    if(lowerLimitVal>upperLimitVal){
        printf("Runtime Error\n");
        exit(1);
    }
    while (i <= upperLimitVal) {
        evaluate(body);
        i += stepVal;
    }
}
else if(upperLimit->next->type==36){
    if(lowerLimitVal<upperLimitVal){
        printf("Runtime Error\n");
        exit(1);
    }
    while (i >= upperLimitVal) {
        evaluate(body);
        i -= stepVal;
    }
}

int fini = i;
if (stepBase == 8) {
    fini = inttooctal(fini);
} else if (stepBase == 2) {
    fini = inttobinary(fini);
} else if (stepBase == 10) {
    fini = i;
}
    if (loopVarSym) {
        char newValue[50];
        sprintf(newValue, "(%d,%d)", fini, lowerLimitBase);
        strcpy(loopVarSym->value, newValue);
        markInitialized(loopVarSym->name);
    }
}
break;
    default:
        printf("Runtime Error\n");
        exit(1);
    }
    if (node->next)
    {
        evaluate(node->next);
        
    }
}

void executeAssignment(ASTNode *node)
{
    if (!node)
        return;

    ASTNode *left = node->data.children.left;
    ASTNode *right = node->data.children.right;

    if (left->type != NODE_IDENTIFIER)
        return;

    ASTNode *temp = evaluateExpression(right);
    Symbol *sym = lookupSymbol(left->data.strValue);
    if (sym)
    {
        if (temp->type == NODE_CHAR_LITERAL) {
            char charValue = temp->data.strValue[1]; 
            sprintf(sym->value, "%c", charValue);
            markInitialized(sym->name);
        } else {
        sprintf(sym->value, "%s", temp->data.strValue);
        markInitialized(sym->name);
        }
    }
    else
    {
        printf("Runtime Error\n");
    }
}

char *converttostring(int num)
{
    char *str = (char *)malloc(20);
    if (str)
    {
        sprintf(str, "%d", num);
    }
    return str;
}

ASTNode *evaluateExpression(ASTNode *node)
{
    if (!node)
        return 0;

    switch (node->type)
    {
    case NODE_INT_LITERAL:
    {
        return node;
        break;
    }
    case NODE_CHAR_LITERAL:
{
    return node;  
    break;
}
    case NODE_IDENTIFIER:
    {
        Symbol *sym = lookupSymbol(node->data.strValue);
        if (sym && sym->initialized)
        {
            return node;
        }
        else
        {
            printf("Runtime Error\n");
            exit(1);
        }
        break;
    }

    case NODE_ADD:
    {  
        if ((basetaker(node->data.children.left) == basetaker(node->data.children.right)) && basetaker(node->data.children.left) == 10)
        {
            int val1 = valuetaker(evaluateExpression((node->data.children.left)));
            int val2 = valuetaker(evaluateExpression((node->data.children.right)));
            int result = val1 + val2;
            char result_str[50];
            sprintf(result_str, "(%d,10)", result);
            return createStrNode(NODE_INT_LITERAL, result_str);
        }
        else if ((basetaker(node->data.children.left) == basetaker(node->data.children.right)) && basetaker(node->data.children.left) == 8)
        {
            int val1 = valuetaker(evaluateExpression((node->data.children.left)));
            int val2 = valuetaker(evaluateExpression((node->data.children.right)));
            int octval1 = octaltoint(val1);
            int octval2 = octaltoint(val2);
            int result = octval1 + octval2;
            int octalresult = inttooctal(result);
            char result_str[50];
            sprintf(result_str, "(%d,8)", octalresult);
            return createStrNode(NODE_INT_LITERAL, result_str);
        }
        else if ((basetaker(node->data.children.left) == basetaker(node->data.children.right)) && basetaker(node->data.children.left) == 2)
        {
            int val1 = valuetaker(evaluateExpression((node->data.children.left)));
            int val2 = valuetaker(evaluateExpression((node->data.children.right)));
            int binval1 = binarytoint(val1);
            int binval2 = binarytoint(val2);
            int result = binval1 + binval2;
            int binaryresult = inttobinary(result);
            char result_str[50];
            sprintf(result_str, "(%d,2)", binaryresult);
            return createStrNode(NODE_INT_LITERAL, result_str);
        }
        else
        {
            printf("Runtime Error\n");
            exit(1);
        }
    }
    break;

    case NODE_SUB:
    {
        if ((basetaker(node->data.children.left) == basetaker(node->data.children.right)) && basetaker(node->data.children.left) == 10)
        {
            int val1 = valuetaker(evaluateExpression((node->data.children.left)));
            int val2 = valuetaker(evaluateExpression((node->data.children.right)));
            int result = val1 - val2;
            char result_str[50];
            sprintf(result_str, "(%d,10)", result);
            return createStrNode(NODE_INT_LITERAL, result_str);
        }
        else if ((basetaker(node->data.children.left) == basetaker(node->data.children.right)) && basetaker(node->data.children.left) == 8)
        {
            int val1 = valuetaker(evaluateExpression((node->data.children.left)));
            int val2 = valuetaker(evaluateExpression((node->data.children.right)));
            int octval1 = octaltoint(val1);
            int octval2 = octaltoint(val2);
            int result = octval1 - octval2;
            int octalresult = inttooctal(result);
            char result_str[50];
            sprintf(result_str, "(%d,8)", octalresult);
            return createStrNode(NODE_INT_LITERAL, result_str);
        }
        else if ((basetaker(node->data.children.left) == basetaker(node->data.children.right)) && basetaker(node->data.children.left) == 2)
        {
            int val1 = valuetaker(evaluateExpression((node->data.children.left)));
            int val2 = valuetaker(evaluateExpression((node->data.children.right)));
            int binval1 = binarytoint(val1);
            int binval2 = binarytoint(val2);
            int result = binval1 - binval2;
            int binaryresult = inttobinary(result);
            char result_str[50];
            sprintf(result_str, "(%d,2)", binaryresult);
            return createStrNode(NODE_INT_LITERAL, result_str);
        }
        else
        {
            printf("Runtime Error\n");
            exit(1);
        }
    }
    break;

    case NODE_MUL:
    {
        if ((basetaker(node->data.children.left) == basetaker(node->data.children.right)) && basetaker(node->data.children.left) == 10)
        {
            int val1 = valuetaker(evaluateExpression((node->data.children.left)));
            int val2 = valuetaker(evaluateExpression((node->data.children.right)));
            int result = val1 * val2;
            char result_str[50];
            sprintf(result_str, "(%d,10)", result);
            return createStrNode(NODE_INT_LITERAL, result_str);
        }
        else if ((basetaker(node->data.children.left) == basetaker(node->data.children.right)) && basetaker(node->data.children.left) == 8)
        {
            int val1 = valuetaker(evaluateExpression((node->data.children.left)));
            int val2 = valuetaker(evaluateExpression((node->data.children.right)));
            int octval1 = octaltoint(val1);
            int octval2 = octaltoint(val2);
            int result = octval1 * octval2;
            int octalresult = inttooctal(result);
            char result_str[50];
            sprintf(result_str, "(%d,8)", octalresult);
            return createStrNode(NODE_INT_LITERAL, result_str);
        }
        else if ((basetaker(node->data.children.left) == basetaker(node->data.children.right)) && basetaker(node->data.children.left) == 2)
        {
            int val1 = valuetaker(evaluateExpression((node->data.children.left)));
            int val2 = valuetaker(evaluateExpression((node->data.children.right)));
            int binval1 = binarytoint(val1);
            int binval2 = binarytoint(val2);
            int result = binval1 * binval2;
            int binaryresult = inttobinary(result);
            char result_str[50];
            sprintf(result_str, "(%d,2)", binaryresult);
            return createStrNode(NODE_INT_LITERAL, result_str);
        }
        else
        {
            printf("Runtime Error\n");
            exit(1);
        }
    }
    break;

    case NODE_DIV:
    {
        if (valuetaker(evaluateExpression(node->data.children.right)) == 0)
        {
            printf("Runtime Error\n");
            exit(1);
        }
        if ((basetaker(node->data.children.left) == basetaker(node->data.children.right)) && basetaker(node->data.children.left) == 10)
        {
            int val1 = valuetaker(evaluateExpression((node->data.children.left)));
            int val2 = valuetaker(evaluateExpression((node->data.children.right)));
            int result = val1 / val2;
            char result_str[50];
            sprintf(result_str, "(%d,10)", result);
            return createStrNode(NODE_INT_LITERAL, result_str);
        }
        else if ((basetaker(node->data.children.left) == basetaker(node->data.children.right)) && basetaker(node->data.children.left) == 8)
        {
            int val1 = valuetaker(evaluateExpression((node->data.children.left)));
            int val2 = valuetaker(evaluateExpression((node->data.children.right)));
            int octval1 = octaltoint(val1);
            int octval2 = octaltoint(val2);
            int result = octval1 / octval2;
            int octalresult = inttooctal(result);
            char result_str[50];
            sprintf(result_str, "(%d,8)", octalresult);
            return createStrNode(NODE_INT_LITERAL, result_str);
        }
        else if ((basetaker(node->data.children.left) == basetaker(node->data.children.right)) && basetaker(node->data.children.left) == 2)
        {
            int val1 = valuetaker(evaluateExpression((node->data.children.left)));
            int val2 = valuetaker(evaluateExpression((node->data.children.right)));
            int binval1 = binarytoint(val1);
            int binval2 = binarytoint(val2);
            int result = binval1 / binval2;
            int binaryresult = inttobinary(result);
            char result_str[50];
            sprintf(result_str, "(%d,2)", binaryresult);
            return createStrNode(NODE_INT_LITERAL, result_str);
        }
        else
        {
            printf("Runtime Error\n");
            exit(1);
        }
        break;
    }
    case NODE_MOD:
    {
        if (valuetaker(evaluateExpression(node->data.children.right)) == 0)
        {
            printf("Runtime Error\n");
            exit(1);
        }
        if ((basetaker(node->data.children.left) == basetaker(node->data.children.right)) && basetaker(node->data.children.left) == 10)
        {
            int val1 = valuetaker(evaluateExpression((node->data.children.left)));
            int val2 = valuetaker(evaluateExpression((node->data.children.right)));
            int result = val1 % val2;
            char result_str[50];
            sprintf(result_str, "(%d,10)", result);
            return createStrNode(NODE_INT_LITERAL, result_str);
        }
        else if ((basetaker(node->data.children.left) == basetaker(node->data.children.right)) && basetaker(node->data.children.left) == 8)
        {
            int val1 = valuetaker(evaluateExpression((node->data.children.left)));
            int val2 = valuetaker(evaluateExpression((node->data.children.right)));
            int octval1 = octaltoint(val1);
            int octval2 = octaltoint(val2);
            int result = octval1 % octval2;
            int octalresult = inttooctal(result);
            char result_str[50];
            sprintf(result_str, "(%d,8)", octalresult);
            return createStrNode(NODE_INT_LITERAL, result_str);
        }
        else if ((basetaker(node->data.children.left) == basetaker(node->data.children.right)) && basetaker(node->data.children.left) == 2)
        {
            int val1 = valuetaker(evaluateExpression((node->data.children.left)));
            int val2 = valuetaker(evaluateExpression((node->data.children.right)));
            int binval1 = binarytoint(val1);
            int binval2 = binarytoint(val2);
            int result = binval1 % binval2;
            int binaryresult = inttobinary(result);
            char result_str[50];
            sprintf(result_str, "(%d,2)", binaryresult);
            return createStrNode(NODE_INT_LITERAL, result_str);
        }
        else
        {
            printf("Runtime Error\n");
            exit(1);
        }
        break;
    }
    case NODE_EQ:
        if ((basetaker(node->data.children.left) == basetaker(node->data.children.right)) && basetaker(node->data.children.left) == 10)
        {
            int val1 = valuetaker(evaluateExpression((node->data.children.left)));
            int val2 = valuetaker(evaluateExpression((node->data.children.right)));
            return (val1 == val2) ? createStrNode(NODE_INT_LITERAL, "(1,10)") : createStrNode(NODE_INT_LITERAL, "(0,10)");
        }
        else if ((basetaker(node->data.children.left) == basetaker(node->data.children.right)) && basetaker(node->data.children.left) == 8)
        {
            int val1 = valuetaker(evaluateExpression((node->data.children.left)));
            int val2 = valuetaker(evaluateExpression((node->data.children.right)));
            int octval1 = octaltoint(val1);
            int octval2 = octaltoint(val2);
            return (octval1 == octval2) ? createStrNode(NODE_INT_LITERAL, "(1,8)") : createStrNode(NODE_INT_LITERAL, "(0,8)");
        }
        else if ((basetaker(node->data.children.left) == basetaker(node->data.children.right)) && basetaker(node->data.children.left) == 2)
        {
            int val1 = valuetaker(evaluateExpression((node->data.children.left)));
            int val2 = valuetaker(evaluateExpression((node->data.children.right)));
            int binval1 = binarytoint(val1);
            int binval2 = binarytoint(val2);
            return (binval1 == binval2) ? createStrNode(NODE_INT_LITERAL, "(1,2)") : createStrNode(NODE_INT_LITERAL, "(0,2)");
        }
        else
        {
            printf("Runtime Error\n");
            exit(1);
        }
        break;
    case NODE_NE:
        if ((basetaker(node->data.children.left) == basetaker(node->data.children.right)) && basetaker(node->data.children.left) == 10)
        {
            int val1 = valuetaker(evaluateExpression((node->data.children.left)));
            int val2 = valuetaker(evaluateExpression((node->data.children.right)));
            return (val1 != val2) ? createStrNode(NODE_INT_LITERAL, "(1,10)") : createStrNode(NODE_INT_LITERAL, "(0,10)");
        }
        else if ((basetaker(node->data.children.left) == basetaker(node->data.children.right)) && basetaker(node->data.children.left) == 8)
        {
            int val1 = valuetaker(evaluateExpression((node->data.children.left)));
            int val2 = valuetaker(evaluateExpression((node->data.children.right)));
            int octval1 = octaltoint(val1);
            int octval2 = octaltoint(val2);
            return (octval1 != octval2) ? createStrNode(NODE_INT_LITERAL, "(1,8)") : createStrNode(NODE_INT_LITERAL, "(0,8)");
        }
        else if ((basetaker(node->data.children.left) == basetaker(node->data.children.right)) && basetaker(node->data.children.left) == 2)
        {
            int val1 = valuetaker(evaluateExpression((node->data.children.left)));
            int val2 = valuetaker(evaluateExpression((node->data.children.right)));
            int binval1 = binarytoint(val1);
            int binval2 = binarytoint(val2);
            return (binval1 != binval2) ? createStrNode(NODE_INT_LITERAL, "(1,2)") : createStrNode(NODE_INT_LITERAL, "(0,2)");
        }
        else
        {
            printf("Runtime Error\n");
            exit(1);
        }
        break;
    case NODE_LT:
        if ((basetaker(node->data.children.left) == basetaker(node->data.children.right)) && basetaker(node->data.children.left) == 10)
        {
            int val1 = valuetaker(evaluateExpression((node->data.children.left)));
            int val2 = valuetaker(evaluateExpression((node->data.children.right)));
            return (val1 < val2) ? createStrNode(NODE_INT_LITERAL, "(1,10)") : createStrNode(NODE_INT_LITERAL, "(0,10)");
        }
        else if ((basetaker(node->data.children.left) == basetaker(node->data.children.right)) && basetaker(node->data.children.left) == 8)
        {
            int val1 = valuetaker(evaluateExpression((node->data.children.left)));
            int val2 = valuetaker(evaluateExpression((node->data.children.right)));
            int octval1 = octaltoint(val1);
            int octval2 = octaltoint(val2);
            return (octval1 < octval2) ? createStrNode(NODE_INT_LITERAL, "(1,8)") : createStrNode(NODE_INT_LITERAL, "(0,8)");
        }
        else if ((basetaker(node->data.children.left) == basetaker(node->data.children.right)) && basetaker(node->data.children.left) == 2)
        {
            int val1 = valuetaker(evaluateExpression((node->data.children.left)));
            int val2 = valuetaker(evaluateExpression((node->data.children.right)));
            int binval1 = binarytoint(val1);
            int binval2 = binarytoint(val2);
            return (binval1 < binval2) ? createStrNode(NODE_INT_LITERAL, "(1,2)") : createStrNode(NODE_INT_LITERAL, "(0,2)");
        }
        else
        {
            printf("Runtime Error\n");
            exit(1);
        }
        break;
    case NODE_GT:
        if ((basetaker(node->data.children.left) == basetaker(node->data.children.right)) && basetaker(node->data.children.left) == 10)
        {
            int val1 = valuetaker(evaluateExpression((node->data.children.left)));
            int val2 = valuetaker(evaluateExpression((node->data.children.right)));
            return (val1 > val2) ? createStrNode(NODE_INT_LITERAL, "(1,10)") : createStrNode(NODE_INT_LITERAL, "(0,10)");
        }
        else if ((basetaker(node->data.children.left) == basetaker(node->data.children.right)) && basetaker(node->data.children.left) == 8)
        {
            int val1 = valuetaker(evaluateExpression((node->data.children.left)));
            int val2 = valuetaker(evaluateExpression((node->data.children.right)));
            int octval1 = octaltoint(val1);
            int octval2 = octaltoint(val2);
            return (octval1 > octval2) ? createStrNode(NODE_INT_LITERAL, "(1,8)") : createStrNode(NODE_INT_LITERAL, "(0,8)");
        }
        else if ((basetaker(node->data.children.left) == basetaker(node->data.children.right)) && basetaker(node->data.children.left) == 2)
        {
            int val1 = valuetaker(evaluateExpression((node->data.children.left)));
            int val2 = valuetaker(evaluateExpression((node->data.children.right)));
            int binval1 = binarytoint(val1);
            int binval2 = binarytoint(val2);
            return (binval1 > binval2) ? createStrNode(NODE_INT_LITERAL, "(1,2)") : createStrNode(NODE_INT_LITERAL, "(0,2)");
        }
        else
        {
            printf("Runtime Error\n");
            exit(1);
        }
        break;
    case NODE_LE:
        if ((basetaker(node->data.children.left) == basetaker(node->data.children.right)) && basetaker(node->data.children.left) == 10)
        {
            int val1 = valuetaker(evaluateExpression((node->data.children.left)));
            int val2 = valuetaker(evaluateExpression((node->data.children.right)));
            return (val1 <= val2) ? createStrNode(NODE_INT_LITERAL, "(1,10)") : createStrNode(NODE_INT_LITERAL, "(0,10)");
        }
        else if ((basetaker(node->data.children.left) == basetaker(node->data.children.right)) && basetaker(node->data.children.left) == 8)
        {
            int val1 = valuetaker(evaluateExpression((node->data.children.left)));
            int val2 = valuetaker(evaluateExpression((node->data.children.right)));
            int octval1 = octaltoint(val1);
            int octval2 = octaltoint(val2);
            return (octval1 <= octval2) ? createStrNode(NODE_INT_LITERAL, "(1,8)") : createStrNode(NODE_INT_LITERAL, "(0,8)");
        }
        else if ((basetaker(node->data.children.left) == basetaker(node->data.children.right)) && basetaker(node->data.children.left) == 2)
        {
            int val1 = valuetaker(evaluateExpression((node->data.children.left)));
            int val2 = valuetaker(evaluateExpression((node->data.children.right)));
            int binval1 = binarytoint(val1);
            int binval2 = binarytoint(val2);
            return (binval1 <= binval2) ? createStrNode(NODE_INT_LITERAL, "(1,2)") : createStrNode(NODE_INT_LITERAL, "(0,2)");
        }
        else
        {
            printf("Runtime Error\n");
            exit(1);
        }
        break;
    case NODE_GE:
        if ((basetaker(node->data.children.left) == basetaker(node->data.children.right)) && basetaker(node->data.children.left) == 10)
        {
            int val1 = valuetaker(evaluateExpression((node->data.children.left)));
            int val2 = valuetaker(evaluateExpression((node->data.children.right)));
            return (val1 >= val2) ? createStrNode(NODE_INT_LITERAL, "(1,10)") : createStrNode(NODE_INT_LITERAL, "(0,10)");
        }
        else if ((basetaker(node->data.children.left) == basetaker(node->data.children.right)) && basetaker(node->data.children.left) == 8)
        {
            int val1 = valuetaker(evaluateExpression((node->data.children.left)));
            int val2 = valuetaker(evaluateExpression((node->data.children.right)));
            int octval1 = octaltoint(val1);
            int octval2 = octaltoint(val2);
            return (octval1 >= octval2) ? createStrNode(NODE_INT_LITERAL, "(1,8)") : createStrNode(NODE_INT_LITERAL, "(0,8)");
        }
        else if ((basetaker(node->data.children.left) == basetaker(node->data.children.right)) && basetaker(node->data.children.left) == 2)
        {
            int val1 = valuetaker(evaluateExpression((node->data.children.left)));
            int val2 = valuetaker(evaluateExpression((node->data.children.right)));
            int binval1 = binarytoint(val1);
            int binval2 = binarytoint(val2);
            return (binval1 >= binval2) ? createStrNode(NODE_INT_LITERAL, "(1,2)") : createStrNode(NODE_INT_LITERAL, "(0,2)");
        }
        else
        {
            printf("Runtime Error\n");
            exit(1);
        }
        break;
    case NODE_POST_INC:
    case NODE_POST_DEC:
        if (node->data.children.left->type == NODE_IDENTIFIER)
        {
            Symbol *sym = lookupSymbol(node->data.children.left->data.strValue);
            if (sym && sym->initialized)
            {
                if (basetaker(node->data.children.left) == 10)
                {
                    int value = valuetaker(evaluateExpression(node->data.children.left));
                    if (node->type == NODE_POST_INC)
                    {
                        value++;
                    }
                    else
                    {
                        value--;
                    }
                    sprintf(sym->value, "(%d,10)", value);
                    return createStrNode(NODE_INT_LITERAL, sym->value);
                }
                else if (basetaker(node->data.children.left) == 8)
                {
                    int value = valuetaker(evaluateExpression(node->data.children.left));
                    int octval = octaltoint(value);
                    if (node->type == NODE_POST_INC)
                    {
                        octval++;
                    }
                    else
                    {
                        octval--;
                    }
                    int octresult = inttooctal(octval);
                    sprintf(sym->value, "(%d,8)", octresult);
                    return createStrNode(NODE_INT_LITERAL, sym->value);
                }
                else if (basetaker(node->data.children.left) == 2)
                {
                    int value = valuetaker(evaluateExpression(node->data.children.left));
                    int octval = binarytoint(value);
                    if (node->type == NODE_POST_INC)
                    {
                        octval++;
                    }
                    else
                    {
                        octval--;
                    }
                    int octresult = inttobinary(octval);
                    sprintf(sym->value, "(%d,2)", octresult);
                    return createStrNode(NODE_INT_LITERAL, sym->value);
                }
            }
            else
            {
                printf("Runtime Error\n");
                exit(1);
            }
        }
        break;
    case NODE_PLUS_ASSIGN:
        if (node->data.children.left->type == NODE_IDENTIFIER)
        {
            Symbol *sym = lookupSymbol(node->data.children.left->data.strValue);
            if (sym && sym->initialized)
            {
                if ((basetaker(node->data.children.left) == 10) && (basetaker(node->data.children.right)) == 10)
                {
                    int value = valuetaker(evaluateExpression(node->data.children.left));
                    int addValue = valuetaker(evaluateExpression(node->data.children.right));
                    value += addValue;
                    sprintf(sym->value, "(%d,10)", value);
                    return createStrNode(NODE_INT_LITERAL, sym->value);
                }
                else if ((basetaker(node->data.children.left) == 2) && (basetaker(node->data.children.right)) == 2)
                {
                    int val1 = valuetaker(evaluateExpression(node->data.children.left));
                    int val2 = valuetaker(evaluateExpression(node->data.children.right));
                    int binval1 = binarytoint(val1);
                    int binval2 = binarytoint(val2);
                    int result = binval1 + binval2;
                    int binaryresult = inttobinary(result);
                    sprintf(sym->value, "(%d,2)", binaryresult);
                    return createStrNode(NODE_INT_LITERAL, sym->value);
                }
                else if ((basetaker(node->data.children.left) == 8) && (basetaker(node->data.children.right)) == 8)
                {
                    int val1 = valuetaker(evaluateExpression(node->data.children.left));
                    int val2 = valuetaker(evaluateExpression(node->data.children.right));
                    int binval1 = octaltoint(val1);
                    int binval2 = octaltoint(val2);
                    int result = binval1 + binval2;
                    int binaryresult = inttooctal(result);
                    sprintf(sym->value, "(%d,8)", binaryresult);
                    return createStrNode(NODE_INT_LITERAL, sym->value);
                }
            }
            else
            {
                printf("Runtime Error\n");
                exit(1);
            }
        }
        break;
    case NODE_MINUS_ASSIGN:
        if (node->data.children.left->type == NODE_IDENTIFIER)
        {
            Symbol *sym = lookupSymbol(node->data.children.left->data.strValue);
            if (sym && sym->initialized)
            {
                if ((basetaker(node->data.children.left) == 10) && (basetaker(node->data.children.right)) == 10)
                {
                    int value = valuetaker(evaluateExpression(node->data.children.left));
                    int addValue = valuetaker(evaluateExpression(node->data.children.right));
                    value -= addValue;
                    sprintf(sym->value, "(%d,10)", value);
                    return createStrNode(NODE_INT_LITERAL, sym->value);
                }
                else if ((basetaker(node->data.children.left) == 2) && (basetaker(node->data.children.right)) == 2)
                {
                    int val1 = valuetaker(evaluateExpression(node->data.children.left));
                    int val2 = valuetaker(evaluateExpression(node->data.children.right));
                    int binval1 = binarytoint(val1);
                    int binval2 = binarytoint(val2);
                    int result = binval1 - binval2;
                    int binaryresult = inttobinary(result);
                    sprintf(sym->value, "(%d,2)", binaryresult);
                    return createStrNode(NODE_INT_LITERAL, sym->value);
                }
                else if ((basetaker(node->data.children.left) == 8) && (basetaker(node->data.children.right)) == 8)
                {
                    int val1 = valuetaker(evaluateExpression(node->data.children.left));
                    int val2 = valuetaker(evaluateExpression(node->data.children.right));
                    int binval1 = octaltoint(val1);
                    int binval2 = octaltoint(val2);
                    int result = binval1 - binval2;
                    int binaryresult = inttooctal(result);
                    sprintf(sym->value, "(%d,8)", binaryresult);
                    return createStrNode(NODE_INT_LITERAL, sym->value);
                }
            }
            else
            {
                printf("Runtime Error\n");
                exit(1);
            }
        }
        break;
    case NODE_MULT_ASSIGN:
        if (node->data.children.left->type == NODE_IDENTIFIER)
        {
            Symbol *sym = lookupSymbol(node->data.children.left->data.strValue);
            if (sym && sym->initialized)
            {
                if ((basetaker(node->data.children.left) == 10) && (basetaker(node->data.children.right)) == 10)
                {
                    int value = valuetaker(evaluateExpression(node->data.children.left));
                    int addValue = valuetaker(evaluateExpression(node->data.children.right));
                    value *= addValue;
                    sprintf(sym->value, "(%d,10)", value);
                    return createStrNode(NODE_INT_LITERAL, sym->value);
                }
                else if ((basetaker(node->data.children.left) == 2) && (basetaker(node->data.children.right)) == 2)
                {
                    int val1 = valuetaker(evaluateExpression(node->data.children.left));
                    int val2 = valuetaker(evaluateExpression(node->data.children.right));
                    int binval1 = binarytoint(val1);
                    int binval2 = binarytoint(val2);
                    int result = binval1 * binval2;
                    int binaryresult = inttobinary(result);
                    sprintf(sym->value, "(%d,2)", binaryresult);
                    return createStrNode(NODE_INT_LITERAL, sym->value);
                }
                else if ((basetaker(node->data.children.left) == 8) && (basetaker(node->data.children.right)) == 8)
                {
                    int val1 = valuetaker(evaluateExpression(node->data.children.left));
                    int val2 = valuetaker(evaluateExpression(node->data.children.right));
                    int binval1 = octaltoint(val1);
                    int binval2 = octaltoint(val2);
                    int result = binval1 * binval2;
                    int binaryresult = inttooctal(result);
                    sprintf(sym->value, "(%d,8)", binaryresult);
                    return createStrNode(NODE_INT_LITERAL, sym->value);
                }
            }
            else
            {
                printf("Runtime Error\n");
                exit(1);
            }
        }
        break;
    case NODE_DIV_ASSIGN:
        if (valuetaker(evaluateExpression(node->data.children.right)) == 0)
        {
            printf("Runtime Error\n");
            exit(1);
        }
        if (node->data.children.left->type == NODE_IDENTIFIER)
        {
            Symbol *sym = lookupSymbol(node->data.children.left->data.strValue);
            if (sym && sym->initialized)
            {
                if ((basetaker(node->data.children.left) == 10) && (basetaker(node->data.children.right)) == 10)
                {
                    int value = valuetaker(evaluateExpression(node->data.children.left));
                    int addValue = valuetaker(evaluateExpression(node->data.children.right));
                    value /= addValue;
                    sprintf(sym->value, "(%d,10)", value);
                    return createStrNode(NODE_INT_LITERAL, sym->value);
                }
                else if ((basetaker(node->data.children.left) == 2) && (basetaker(node->data.children.right)) == 2)
                {
                    int val1 = valuetaker(evaluateExpression(node->data.children.left));
                    int val2 = valuetaker(evaluateExpression(node->data.children.right));
                    int binval1 = binarytoint(val1);
                    int binval2 = binarytoint(val2);
                    int result = binval1 / binval2;
                    int binaryresult = inttobinary(result);
                    sprintf(sym->value, "(%d,2)", binaryresult);
                    return createStrNode(NODE_INT_LITERAL, sym->value);
                }
                else if ((basetaker(node->data.children.left) == 8) && (basetaker(node->data.children.right)) == 8)
                {
                    int val1 = valuetaker(evaluateExpression(node->data.children.left));
                    int val2 = valuetaker(evaluateExpression(node->data.children.right));
                    int binval1 = octaltoint(val1);
                    int binval2 = octaltoint(val2);
                    int result = binval1 / binval2;
                    int binaryresult = inttooctal(result);
                    sprintf(sym->value, "(%d,8)", binaryresult);
                    return createStrNode(NODE_INT_LITERAL, sym->value);
                }
            }
            else
            {
                printf("Runtime Error\n");
                exit(1);
            }
        }
        break;
    case NODE_PRE_INC:
    case NODE_PRE_DEC:
        if (node->data.children.left->type == NODE_IDENTIFIER)
        {
            Symbol *sym = lookupSymbol(node->data.children.left->data.strValue);
            if (sym && sym->initialized)
            {
                if (basetaker(node->data.children.left) == 10)
                {
                    int value = valuetaker(evaluateExpression(node->data.children.left));
                    if (node->type == NODE_PRE_INC)
                    {
                        value++;
                    }
                    else
                    {
                        value--;
                    }
                    sprintf(sym->value, "(%d,10)", value);
                    return createStrNode(NODE_INT_LITERAL, sym->value);
                }
                else if (basetaker(node->data.children.left) == 8)
                {
                    int value = valuetaker(evaluateExpression(node->data.children.left));
                    int octval = octaltoint(value);
                    if (node->type == NODE_PRE_INC)
                    {
                        octval++;
                    }
                    else
                    {
                        octval--;
                    }
                    int octresult = inttooctal(octval);
                    sprintf(sym->value, "(%d,8)", octresult);
                    return createStrNode(NODE_INT_LITERAL, sym->value);
                }
                else if (basetaker(node->data.children.left) == 2)
                {
                    int value = valuetaker(evaluateExpression(node->data.children.left));
                    int octval = binarytoint(value);
                    if (node->type == NODE_PRE_INC)
                    {
                        octval++;
                    }
                    else
                    {
                        octval--;
                    }
                    int octresult = inttobinary(octval);
                    sprintf(sym->value, "(%d,2)", octresult);
                    return createStrNode(NODE_INT_LITERAL, sym->value);
                }
            }
            else
            {
                printf("Runtime Error\n");
                exit(1);
            }
        }
        else if(node->data.children.left->type == NODE_INT_LITERAL){
            if (node->type == NODE_PRE_INC)
            {
                int value = valuetaker(evaluateExpression(node->data.children.left));
                value++;
                sprintf(node->data.children.left->data.strValue, "(%d,10)", value);
                return createStrNode(NODE_INT_LITERAL, node->data.children.left->data.strValue);
            }
            else
            {
                int value = valuetaker(evaluateExpression(node->data.children.left));
                value--;
                sprintf(node->data.children.left->data.strValue, "(%d,10)", value);
                return createStrNode(NODE_INT_LITERAL, node->data.children.left->data.strValue);
            }
        }
        break;
    case NODE_UNARY_PLUS:
    case NODE_UNARY_MINUS:
        if (node->data.children.left->type == NODE_IDENTIFIER)
        {
            Symbol *sym = lookupSymbol(node->data.children.left->data.strValue);
            if (sym && sym->initialized)
            {
                if (basetaker(node->data.children.left) == 10)
                {
                    int value = valuetaker(evaluateExpression(node->data.children.left));
                    if (node->type == NODE_UNARY_PLUS)
                    {
                        value = value;
                    }
                    else
                    {
                        value = -value;
                    }
                    sprintf(sym->value, "(%d,10)", value);
                    return createStrNode(NODE_INT_LITERAL, sym->value);
                }
                else if (basetaker(node->data.children.left) == 8)
                {
                    printf("Runtime Error\n");
                    exit(1);
                }
                else if (basetaker(node->data.children.left) == 2)
                {
                    printf("Runtime Error\n");
                    exit(1);
                }
            }
            else
            {
                printf("Runtime Error\n");
                exit(1);
            }
        }
        break;
    default:
        return NULL;
    }
    return NULL;
}

const char *getNodeTypeName(NodeType type)
{
    switch (type)
    {
    case NODE_PROGRAM:
        return "";
    case NODE_VARDECL_SECTION:
        return "";
    case NODE_MAIN_SECTION:
        return "";
    case NODE_STATEMENT_LIST:
        return "";
    case NODE_VARDECL:
        return "";
    case NODE_TYPE_INT:
        return "int";
    case NODE_TYPE_CHAR:
        return "char";
    case NODE_COMPOUND_STMT:
        return "";
    case NODE_IF_STMT:
        return "if";
    case NODE_IF_ELSE_STMT:
        return "if-else";
    case NODE_WHILE_STMT:
        return "while";
    case NODE_FOR_STMT:
        return "for";
    case NODE_DO_WHILE_STMT:
        return "do-while";
    case NODE_PRINT_STMT:
        return "print";
    case NODE_SCAN_STMT:
        return "scan";
    case NODE_EXPR_STMT:
        return "";
    case NODE_ASSIGN:
        return ":=";
    case NODE_PLUS_ASSIGN:
        return "+=";
    case NODE_MINUS_ASSIGN:
        return "-=";
    case NODE_MULT_ASSIGN:
        return "*=";
    case NODE_DIV_ASSIGN:
        return "/=";
    case NODE_MOD_ASSIGN:
        return "%=";
    case NODE_EQ:
        return "=";
    case NODE_NE:
        return "<>";
    case NODE_LT:
        return "<";
    case NODE_GT:
        return ">";
    case NODE_LE:
        return "<=";
    case NODE_GE:
        return ">=";
    case NODE_ADD:
        return "+";
    case NODE_SUB:
        return "-";
    case NODE_MUL:
        return "*";
    case NODE_DIV:
        return "/";
    case NODE_MOD:
        return "%";
    case NODE_UNARY_PLUS:
        return "";
    case NODE_UNARY_MINUS:
        return "";
    case NODE_PRE_INC:
        return "";
    case NODE_PRE_DEC:
        return "";
    case NODE_POST_INC:
        return "";
    case NODE_POST_DEC:
        return "";
    case NODE_IDENTIFIER:
        return "";
    case NODE_INT_LITERAL:
        return "";
    case NODE_CHAR_LITERAL:
        return "";
    case NODE_STRING_LITERAL:
        return "";
    default:
        return "UNKNOWN";
    }
}

void printAST(ASTNode *node, int indent)
{
    if (!node)
    {
        printf("()");
        return;
    }

    printf("(");

    const char *typeName = getNodeTypeName(node->type);

    if (strlen(typeName) > 0)
    {
        printf("%s", typeName);
    }

    switch (node->type)
    {
    case NODE_IDENTIFIER:
    case NODE_INT_LITERAL:
    case NODE_CHAR_LITERAL:
    case NODE_STRING_LITERAL:
        printf("%s", node->data.strValue);
        break;
    default:
        break;
    }

    switch (node->type)
    {
    case NODE_PROGRAM:
    case NODE_VARDECL_SECTION:
    case NODE_MAIN_SECTION:
    case NODE_STATEMENT_LIST:
    case NODE_COMPOUND_STMT:

        if (node->data.children.left)
        {
            printf(" ");
            printAST(node->data.children.left, indent + 1);
        }
        break;

    case NODE_IF_STMT:
        if (node->data.children.left)
        {
            printf(" ");
            printAST(node->data.children.left, indent + 1);
        }
        if (node->data.children.right)
        {
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

        if (node->data.children.left)
        {
            printf(" ");
            printAST(node->data.children.left, indent + 1);
        }
        if (node->data.children.right)
        {
            printf(" ");
            printAST(node->data.children.right, indent + 1);
        }
        break;

    case NODE_IF_ELSE_STMT:
        if (node->data.ternary.first)
        {
            printf(" ");
            printAST(node->data.ternary.first, indent + 1);
        }
        if (node->data.ternary.second)
        {
            printf(" ");
            printAST(node->data.ternary.second, indent + 1);
        }
        if (node->data.ternary.third)
        {
            printf(" ");
            printAST(node->data.ternary.third, indent + 1);
        }
        break;

    case NODE_FOR_STMT:
    case NODE_DO_WHILE_STMT:

        if (node->data.ternary.first)
        {
            printf(" ");
            printAST(node->data.ternary.first, indent + 1);
        }
        if (node->data.ternary.second)
        {
            printf(" ");
            printAST(node->data.ternary.second, indent + 1);
        }
        if (node->data.ternary.third)
        {
            printf(" ");
            printAST(node->data.ternary.third, indent + 1);
        }
        break;

    case NODE_SCAN_STMT:
    case NODE_PRINT_STMT:
        if (node->data.io.format)
        {
            printf(" ");
            printAST(node->data.io.format, indent + 1);
        }
        if (node->data.io.args)
        {
            printf(" ");
            ASTNode *current = node->data.io.args;
            printf("(args ");
            if (current)
            {
                printAST(current, indent + 2);
                current = current->next;
                if (current)
                    printf(" ");
            }
            printf(")");
        }
        break;
    default:
        break;
    }

    printf(")");

    if (node->next)
    {
        printf(" ");
        printAST(node->next, indent);
    }
}

void freeAST(ASTNode *node)
{
    if (!node)
        return;

    switch (node->type)
    {
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
    ASTNode *next = node->next;
    free(node);
    
    freeAST(next);
}
