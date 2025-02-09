#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/frontend/lexer.h"
#define NEXT_CHAR(lexer) lexer->c = lexer->buffer[++lexer->idx]

int single_chars[] = {
    ['('] = TOK_LPAR,
    [')'] = TOK_RPAR,
    ['{'] = TOK_LBRAC,
    ['}'] = TOK_RBRAC,
    [';'] = TOK_SEMI,
    ['*'] = TOK_STAR,
    ['+'] = TOK_PLUS,
    ['/'] = TOK_DIV,
    ['%'] = TOK_MOD,
    ['='] = TOK_EQ};

void lexer_init_hashmap(lexer_t *lexer)
{
    lexer->hashmap_keyword = hashmap_create(30, 5);
    char *keywords_list[] = {"if", "else", "fn", "for", "while", "var", "return"};
    for (int i = 0; i < 7; i++)
    {
        hashmap_insert(lexer->hashmap_keyword, keywords_list[i], (void *)TOK_IF + i);
    }
}

lexer_t *lexer_create(char *filename, char *buffer)
{
    lexer_t *lexer = (lexer_t *)malloc(sizeof(lexer_t));
    lexer->pos.filename = filename;
    lexer->pos.col = 1;
    lexer->pos.row = 1;
    lexer->idx = 0;
    lexer->buffer = buffer;
    lexer->tk_list = list_create();

    lexer_init_hashmap(lexer);

    return lexer;
}

token_t *lexer_create_token(lexer_t *lexer, int type, int start, int lenght, int row, int col)
{
    token_t *token = (token_t *)malloc(sizeof(token_t));
    token->type = type;
    token->pos.filename = lexer->pos.filename;
    token->pos.col = col;
    token->pos.row = row;
    token->text = lexer->buffer + start;
    token->text_len = lenght;
    list_add(lexer->tk_list, token);

    return token;
}

int lexer_lex_keywords(lexer_t *lexer, char *start, char *end)
{
    char kw[end - start + 1];
    strncpy(kw, start, end - start);
    kw[end - start] = 0;
    return (int)hashmap_search(lexer->hashmap_keyword, kw);
}

int lexer_step(lexer_t *lexer)
{

    switch (lexer->c)
    {

    case '\0':

        return 0;
        break;
    case ' ':
    case '\t':
        lexer->pos.col++;
        NEXT_CHAR(lexer);
        break;
    case '\n':
        lexer->pos.col = 1;
        lexer->pos.row++;
        NEXT_CHAR(lexer);
        break;
    case '\r':
        lexer->pos.col = 1;

        break;
    case 'a' ... 'z':
    case 'A' ... 'Z':
    case '_':
    {
        int start = lexer->idx;
        int col = lexer->pos.col;
        int row = lexer->pos.row;
        char *cstart = lexer->buffer + lexer->idx;
        while (
            lexer->c >= 'a' && lexer->c <= 'z' || lexer->c >= 'A' && lexer->c <= 'Z' || lexer->c >= '0' && lexer->c <= '9' || lexer->c == '_')
        {
            lexer->pos.col++;
            NEXT_CHAR(lexer);
        }

        int kw = lexer_lex_keywords(lexer, cstart, lexer->buffer + lexer->idx);
        lexer_create_token(lexer, (kw > 0 ? kw : TOK_ID), start, lexer->idx - start, row, col);
        break;
    }

    case '0' ... '9':
    {
        int start = lexer->idx;
        int col = lexer->pos.col;
        int row = lexer->pos.row;

        while (lexer->c >= '0' && lexer->c <= '9')
        {
            lexer->pos.col++;
            NEXT_CHAR(lexer);
        }
        lexer_create_token(lexer, TOK_NUM, start, lexer->idx - start, row, col);
        break;
    }
    case '"':
        NEXT_CHAR(lexer);
        int start = lexer->idx;
        int col = lexer->pos.col;
        int row = lexer->pos.row;

        while (lexer->c != '"')
        {
            lexer->pos.col++;
            NEXT_CHAR(lexer);
        }
        lexer->pos.col++;
        NEXT_CHAR(lexer);
        lexer_create_token(lexer, TOK_STRING, start, lexer->idx - start, row, col);
        break;
    case '-':
    {
        int start = lexer->idx;
        int row = lexer->pos.row;
        int col = lexer->pos.col;
        if (lexer->buffer[lexer->idx + 1] == '>')
        {
            NEXT_CHAR(lexer);
            NEXT_CHAR(lexer);
            lexer->pos.col += 2;
            lexer_create_token(lexer, TOK_ARROW, start, lexer->idx - start, row, col);
            break;
        }
        lexer->pos.col++;
        NEXT_CHAR(lexer);
        lexer_create_token(lexer, TOK_MINUS, start, lexer->idx - start, row, col);
        break;
    }
    case '}':
    case '+':
    case '/':
    case '*':
    case '%':
    case '(':
    case ')':
    case '{':
    case ';':
    case '=':
    {
        int start = lexer->idx;
        int row = lexer->pos.row;
        int col = lexer->pos.col;
        int type = single_chars[lexer->c];
        NEXT_CHAR(lexer);

        lexer->pos.col++;
        lexer_create_token(lexer, type, start, lexer->idx - start, row, col);
        break;
    }

    default:
        printf("Unexpected character at %d:%d.\n", lexer->pos.row, lexer->pos.col);
        return 0;
        break;
    }
}

void lexer_lex(lexer_t *lexer)
{
    lexer->c = lexer->buffer[lexer->idx];
    while (lexer_step(lexer) != 0)
        ;
}