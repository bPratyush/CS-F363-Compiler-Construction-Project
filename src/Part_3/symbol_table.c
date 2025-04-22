#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "symbol_table.h"

Symbol* symbolTable2 = NULL;

void insertSymbol( char* name, char* type) {
    if (isdeclared(name)) return;
    Symbol* sym = (Symbol*)malloc(sizeof(Symbol));
    if (!sym) {
        printf("Error: Memory allocation failed for symbol %s\n", name);
        return;
    }

    memset(sym->name, 0, sizeof(sym->name));
    memset(sym->type, 0, sizeof(sym->type));
    memset(sym->value, 0, sizeof(sym->value));
    strncpy(sym->name, name, sizeof(sym->name) - 1);
    
    if (type != NULL && type[0] != '\0') {
        strncpy(sym->type, type, sizeof(sym->type) - 1);
    } else {
        strcpy(sym->type, "unknown");
    }
    
    sym->initialized = 0;
    sym->next = NULL;
    
    if (symbolTable2 == NULL) {
        symbolTable2 = sym;
    } else {
        Symbol* temp = symbolTable2;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = sym;
    }
}

Symbol* lookupSymbol( char* name) {
    Symbol* temp = symbolTable2;
    while (temp != NULL) {
        if (strcmp(temp->name, name) == 0)
            return temp;
        temp = temp->next;
    }
    return NULL;
}

int isdeclared( char* name) {
    return lookupSymbol(name) != NULL;
}

int isInitialized( char* name) {
    Symbol* sym = lookupSymbol(name);
    return sym && sym->initialized;
}

void markInitialized(char* name) {
    Symbol* sym = lookupSymbol(name);
    if (sym) sym->initialized = 1;
}

int printypeinsymboltable(char* str){
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
            return -1; 
}

void updatetypeinsymboltable(int base, Symbol* temp){
    if(base==10){
        strncpy(temp->type, "deci_int", 10);
        temp->type[sizeof(temp->type) - 1] = '\0'; 
    }
    else if(base==8){
        strncpy(temp->type, "oct_int", 10);
        temp->type[sizeof(temp->type) - 1] = '\0'; 
    }
    else if(base==2){
        strncpy(temp->type, "bin_int", 10);
        temp->type[sizeof(temp->type) - 1] = '\0'; 
    }
    else{
        strncpy(temp->type, "char", 10);
        temp->type[sizeof(temp->type) - 1] = '\0'; 
    }
}

void printSymbolTable() {
    printf("\n--- Symbol Table ---\n");
    Symbol* temp = symbolTable2;
    while (temp != NULL) {
        int base = printypeinsymboltable(temp->value);
        updatetypeinsymboltable(base, temp);
        printf("Name: %s, Type: %s, Initialized: %s, Value: %s\n",
               temp->name, temp->type, temp->initialized ? "Yes" : "No", temp->initialized ? temp->value : "NULL");
        temp = temp->next;
    }
}
