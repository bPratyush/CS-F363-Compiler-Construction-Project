%{
    int while_parantheses_count = 0;
    char while_condition_buffer[1024];
    int while_condition_index = 0;

    int validate_identifier(const char *text) {
    const char *keywords[] = {
        "int","char","if","else","while","for","main","begin","end","print","scan",
        "program","VarDecl","inc","dec", NULL
    };
    int i;
    for (i = 0; keywords[i] != NULL; i++) {
        if (strcmp(text, keywords[i]) == 0) {
            printf("INVALID IDENTIFIER (keyword reserved): %s\n", text);
            return 0;
        }
    }
    if (text[0] < 'a' || text[0] > 'z') {
        printf("INVALID IDENTIFIER: %s\n", text);
        return 0;
    }
    {
        int underscore = 0;
        int j;
        for (j = 0; text[j] != '\0'; j++) {
            char c = text[j];
            if (c == '_') {
                underscore++;
                if (underscore > 1) {
                    printf("INVALID IDENTIFIER: %s\n", text);
                    return 0;
                }
            } else if (!(c >= 'a' && c <= 'z') && !(c >= '0' && c <= '9')) {
                printf("INVALID IDENTIFIER: %s\n", text);
                return 0;
            }
        }
    }
    return 1;
}

    void reset_while_stats(){
        memset(while_condition_buffer, 0, sizeof(while_condition_buffer));
        while_parantheses_count = 0;

    }

    int validate_relational_expression(char * condition){
        char id1[256],op[3],id2[256];
        if(sscanf(condition,"%s %s %s",id1,op,id2)==3){
            if(!validate_identifier(id1) || !validate_identifier(id2)){
                return 0;
            }
            if(!(strcmp(op,"=")||strcmp(op,"<>")||strcmp(op,">")||strcmp(op,"<")||strcmp(op,">=")||strcmp(op,"<="))){
                return 0;
            }
            return 1;
        }
        else if(sscanf(condition,"%s",id1)==1){
            return validate_identifier(id1);
        }
        return 0;
    }

    void check_while_condition(){
        while_condition_buffer[while_condition_index] = '\0';
        if(validate_relational_expression(while_condition_buffer)){
            printf("VALID CONDITION IN WHILE LOOP\n");
        }
        else{
            printf("INVALID CONDITION IN WHILE LOOP\n");
        }
    }
    
%}


%x WHILE
%x CONDITION
%%
"while" {
    printf("KEYWORD: %s\n",yytext);
    BEGIN(WHILE);
}
<WHILE>"(" {
 reset_while_stats();
 while_parantheses_count++;
 BEGIN(CONDITION);
}
<CONDITION>[\s]*[a-z][a-z0-9]*[\s]*((<|>|<=|>=|<>)[\s]*(([a-z][a-z0-9]*)|[0-9]*)[\s]*)? {
    printf("VALID CONDITION IDENTIFIED INSIDE WHILE LOOP: %s\n",yytext);
 }
<CONDITION>")\n" {
    while_parantheses_count--;
    if(while_parantheses_count!=0){
        printf("INVALID WHILE LOOP STATEMENT: MISSING MATCHING PARANTHESES\n");
        while_parantheses_count = 0;
    }
    BEGIN(WHILE);
}


<WHILE>"begin" {
    while_parantheses_count++;
}
<WHILE>"end;" {
    while_parantheses_count--;
    if(while_parantheses_count){
        printf("ERROR: you have entered end without a matching begin\n");
    }
    else{
        printf("CORRECT WHILE LOOP\n");
    }
    BEGIN(INITIAL);
}
%%

int main(int argc, char **argv) {
    yylex();
    return 0;
}