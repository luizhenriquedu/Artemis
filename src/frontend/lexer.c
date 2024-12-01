#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lexer.h"
#include "../include/frontend/lexer.h"
#define NEXT_CHAR(lexer) lexer->c = lexer->buffer[++lexer->idx]

int single_chars[] = {
    ['('] = TOK_LPAR,
    [')'] = TOK_RPAR,
    ['{'] = TOK_LBRAC,
    ['}'] = TOK_RBRAC,
    [';'] = TOK_SEMI,
};

lexer_t *lexer_create(char *filename, char *buffer)
{
    lexer_t *lexer = (lexer_t *)malloc(sizeof(lexer_t));
    lexer->pos.filename = filename;
    lexer->pos.col = 1;
    lexer->pos.row = 1;
    lexer->idx = 0;
    lexer->buffer = buffer;
    lexer->tk_list = list_create();

    return lexer;
}

void lexer_create_token(lexer_t *lexer, int type, int start, int lenght, int row, int col)
{
    token_t *token = (token_t *)malloc(sizeof(token_t));
    token->type = type;
    token->pos.filename = lexer->pos.filename;
    token->pos.col = col;
    token->pos.row = row;
    token->text = lexer->buffer + start;
    token->text_len = lenght;
}