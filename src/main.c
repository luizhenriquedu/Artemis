#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "include/frontend/lexer.h"

char *open_file(char *name);

char *tok_types[] = {
    "TOK_EOF",

    "TOK_ID",

    "TOK_STRING",
    "TOK_FLOAT",
    "TOK_NUM",
    "TOK_CHAR",

    "TOK_LPAR",
    "TOK_RPAR",
    "TOK_LBRAC",
    "TOK_RBRAC",
    "TOK_LSQBR",
    "TOK_RSQBR ",

    "TOK_SEMI",
    "TOK_COLON ",

    "TOKEN_COMMA ",

    "TOK_PLUS",
    "TOK_MINUS",
    "TOK_STAR",
    "TOK_MOD",
    "TOK_DIV ",

    "TOK_HAT",
    "TOK_NOT ",

    "TOK_EQ",
    "TOK_EQEQ",
    "TOK_GT",
    "TOK_GTEQ",
    "TOK_LT",
    "TOK_LTEQ",
    "TOK_EXCL",
    "TOK_EXCLEQ",
    "TOK_AMPER",
    "TOK_DBAMPER",
    "TOK_PIPE",
    "TOK_DBPIPE",
    "TOK_AT ",

    "TOK_DOT",
    "TOK_3DOT ",

    "TOK_IF",
    "TOK_ELSE",

    "TOK_FN",
    "TOK_FOR",
    "TOK_WHILE",
    "TOK_VAR",
    "TOK_RET",
    "TOK_ARROW",
};

int main(int argc, char **argv)
{

    char *buffer = open_file(argv[1]);
    lexer_t *lexer = lexer_create(argv[1], buffer);
    lexer_lex(lexer);
    for (list_item_t *item = lexer->tk_list->head->next;
         item != lexer->tk_list->head; item = item->next)
    {
        token_t *tok = (token_t *)item->data;
        printf("%s - %.*s\n", tok_types[tok->type], tok->text_len, tok->text);
    }

    return 0;
}

char *open_file(char *name)
{
    FILE *file = fopen(name, "r");
    if (!file)
        return NULL;
    fseek(file, 0, SEEK_END);
    size_t size = ftell(file);
    fseek(file, 0, SEEK_SET);
    char *buffer = (char *)malloc(size + 1);
    fread(buffer, size, 1, file);
    buffer[size] = 0;
    fclose(file);
    return buffer;
}
