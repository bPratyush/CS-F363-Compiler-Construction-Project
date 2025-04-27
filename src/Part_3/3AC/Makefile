# Tools
FLEX = flex
BISON = bison
CC = gcc
CFLAGS = -g

# Files
LEX_FILE = threeac.l
YACC_FILE = threeac.y
# Generated files
Y_TAB_C = threeac.tab.c
Y_TAB_H = threeac.tab.h
LEX_C = lex.yy.c

# Default target
all: a.out

# Generate Bison parser
$(Y_TAB_C) $(Y_TAB_H): $(YACC_FILE)
	$(BISON) -d $(YACC_FILE)

# Generate Flex scanner
$(LEX_C): $(LEX_FILE) $(Y_TAB_H)
	$(FLEX) $(LEX_FILE)

# Build executable
a.out: $(Y_TAB_C) $(LEX_C)
	$(CC) $(LEX_C) $(Y_TAB_C) -o a.out

# Run
run: a.out
	./a.out

# Clean
clean:
	rm -f $(Y_TAB_C) $(Y_TAB_H) $(LEX_C) a.out

