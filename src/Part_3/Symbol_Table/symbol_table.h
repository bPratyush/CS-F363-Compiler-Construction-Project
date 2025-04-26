#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

typedef struct Symbol {
    char name[50];
    char type[10];
    char value[50];
    int initialized;
    struct Symbol* next;
} Symbol;

void insertSymbol(char* name, char* type);
int isdeclared( char* name);
int isInitialized( char* name);
void markInitialized( char* name);
void printSymbolTable();
Symbol*lookupSymbol(char* name);
void insertSymbol(char* name, char* type);
int isdeclared(char* name);
int isInitialized(char* name);
void markInitialized(char* name);
void printSymbolTable();
void updatetypeinsymboltable(int base, Symbol* temp);
int printypeinsymboltable(char* str);
#endif
