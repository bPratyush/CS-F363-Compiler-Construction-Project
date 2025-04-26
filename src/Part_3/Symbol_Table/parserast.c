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
        // evaluate(node->next);
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
        ASTNode *condition = node->data.children.left;
        ASTNode *body = node->data.children.right;
        while (valuetaker(evaluateExpression(condition)) != 0)
        {
            evaluate(body);
        }
    }
    break;
    case NODE_FOR_STMT:
    {
        ASTNode *initNode = node->data.ternary.first;
        ASTNode *upperLimit = node->data.ternary.second->data.children.left;
        ASTNode *body = node->data.ternary.third;
        evaluate(initNode);
        ASTNode *lowerLimit = initNode->data.children.left;
        int lowerLimitVal = valuetaker(lowerLimit);
        int lowerLimitBase = basetaker(lowerLimit);
        // ASTNode * upperLimitLit = evaluateExpression(upperLimit);
        int upperLimitVal = valuetaker(upperLimit);
        int upperLimitBase = basetaker(upperLimit);
        // int upperLimitVal = valuetaker(evaluateExpression(upperLimit));
        // printf("%d\n",lowerLimitVal);
        if (lowerLimitBase == 8)
        {
            lowerLimitVal = octaltoint(lowerLimitVal);
        }
        else if (lowerLimitBase == 2)
        {
            lowerLimitVal = binarytoint(lowerLimitVal);
        }
        if (upperLimitBase == 8)
        {
            upperLimitVal = octaltoint(upperLimitVal);
        }
        else if (upperLimitBase == 2)
        {
            upperLimitVal = binarytoint(upperLimitVal);
        }
        // ASTNode *stepExpr = NULL;
        // if (upperLimit->next) {

        // if (upperLimit->next->next)
        //     stepExpr = upperLimit->next->next;
        // else
        //     stepExpr = upperLimit->next;
        // }

        // int stepVal = 1;
        // int stepBase;
        // if (stepExpr) {
        // ASTNode *stepLit = evaluateExpression(stepExpr);
        // stepVal   = valuetaker(stepLit);
        // stepBase  = basetaker(stepLit);
        // if (stepBase == 8)  stepVal = octaltoint(stepVal);
        // if (stepBase == 2)  stepVal = binarytoint(stepVal);

        // }
        // // printf("%d %d\n",lowerLimitVal,upperLimitVal);
        // // // lowerLimitVal = 0;
        // // // upperLimitVal = 1;
        // // printf("%d\n",stepVal);
        while (lowerLimitVal <= upperLimitVal)
        {
            evaluate(body);
            lowerLimitVal++;
        }
    }
    break;
        //     case NODE_FOR_STMT: {
        //     ASTNode *initNode  = node->data.ternary.first;
        //     ASTNode *upperExpr = node->data.ternary.second;
        //     ASTNode *body      = node->data.ternary.third;

        //     // 1) execute initializer (e.g. a := (10,8))
        //     evaluate(initNode);

        //     // 2) get the current 'a' from the symbol table as a literal
        //     ASTNode *lowerId   = initNode->data.children.left;
        //     ASTNode *lowerLit  = evaluateExpression(lowerId);
        //     int      lowerRaw  = valuetaker(lowerLit);
        //     int      lowerBase = basetaker(lowerLit);
        //     if (lowerBase == 8)  lowerRaw = octaltoint(lowerRaw);
        //     else if (lowerBase == 2)  lowerRaw = binarytoint(lowerRaw);

        //     // 3) fold the upper‐bound expression fully
        //     ASTNode *upperLit  = evaluateExpression(upperExpr);
        //     int      upperRaw  = valuetaker(upperLit);
        //     int      upperBase = basetaker(upperLit);
        //     if (upperBase == 8)  upperRaw = octaltoint(upperRaw);
        //     else if (upperBase == 2)  upperRaw = binarytoint(upperRaw);

        //     // 4) loop with default step = 1
        //     while (lowerRaw <= upperRaw) {
        //         evaluate(body);
        //         lowerRaw++;
        //     }
        // } break;
    case NODE_PRINT_STMT:
    {
        const char *formatString = node->data.io.format->data.strValue;
        ASTNode *currentArg = node->data.io.args;
        for (const char *c = formatString; *c; ++c)
        {
            if (*c == '@')
            {
                if (currentArg)
                {
                    ASTNode *valueNode = evaluateExpression(currentArg);
                    int value = valuetaker(valueNode);
                    printf("%d", value);
                    currentArg = currentArg->next;
                }
                else
                {
                    printf("@");
                }
            }
            else
            {
                putchar(*c);
            }
        }
        putchar('\n');
    }
    break;
  case NODE_SCAN_STMT:
{
    const char *prompt     = node->data.io.format->data.strValue;
    ASTNode    *currentArg = node->data.io.args;

    for (const char *ch = prompt; *ch; ++ch) {
        if (*ch == '@' && currentArg) {
            // flush any printed text before blocking
            fflush(stdout);

            int value;
            if (scanf("%d", &value) != 1) {
                fprintf(stderr, "Runtime Error: expected an integer\n");
                exit(1);
            }

            // store as "(value,10)", then mark initialized
            Symbol *sym = lookupSymbol(currentArg->data.strValue);
            if (!sym) {
                fprintf(stderr, "Runtime Error: '%s' not declared\n",
                        currentArg->data.strValue);
                exit(1);
            }
            int base = 10;
            // printf("%s\n",sym->type);
            if(strcmp(sym->type,"oct_int")==0){
                base = 8;
            }
            if(strcmp(sym->type,"bin_int")==0){
                base = 2;
            }
            int stored = value;
            if(base==8){
                stored = inttooctal(value);
            }
            else if(base==2){
                stored = inttobinary(value);
            }
            snprintf(sym->value, sizeof sym->value, "(%d,%d)", stored,base);
            markInitialized(sym->name);

            // move on to the next variable
            currentArg = currentArg->next;
        }
        // else if (*ch != '@') {
        //     // echo everything else (spaces, text, punctuation…)
        //     putchar(*ch);
        // }
        
    }
    putchar('\n');
}
break;
    default:
        printf("Runtime Error\n");
        exit(1);
    }
if (node->next) {
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
        sprintf(sym->value, "%s", temp->data.strValue);
        markInitialized(sym->name);
    }
    else
    {
        printf("Runtime Error\n");
    }
    int base = printypeinsymboltable(sym->value);
    updatetypeinsymboltable(base, sym);
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
