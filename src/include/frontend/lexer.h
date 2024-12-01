#pragma once
#include "list.h"
enum
{
    TOK_EOF = 0,

    TOK_ID,

    TOK_STRING,
    TOK_FLOAT,
    TOK_NUM,
    TOK_CHAR,

    TOK_LPAR,
    TOK_RPAR,
    TOK_LBRAC,
    TOK_RBRAC,
    TOK_LSQBR,
    TOK_RSQBR,

    TOK_SEMI,
    TOK_COLON,

    TOKEN_COMMA,

    TOK_PLUS,
    TOK_MINUS,
    TOK_STAR,
    TOK_MOD,
    TOK_DIV,

    TOK_HAT,
    TOK_NOT,

    TOK_EQ,
    TOK_EQEQ,
    TOK_GT,
    TOK_GTEQ,
    TOK_LT,
    TOK_LTEQ,
    TOK_EXCL,
    TOK_EXCLEQ,
    TOK_AMPER,
    TOK_DBAMPER,
    TOK_PIPE,
    TOK_DBPIPE,
    TOK_AT,

    TOK_DOT,
    TOK_3DOT,

    TOK_IF,
    TOK_ELSE,
    TOK_WHILE,
    TOK_FOR,
    TOK_FN,
    TOK_VAR,
    TOK_RET,
    TOK_ARROW,
};

typedef struct
{
    char *filename;
    int col;
    int row;
} position_t;

typedef struct
{
    int type;
    char *text;
    int text_len;
    position_t pos;
} token_t;

typedef struct
{
    position_t pos;
    char *buffer;
    char c;
    int idx;
    list_t *tk_list;
} lexer_t;

lexer_t *lexer_create(char *filename, char *buffer);
void lexer_lex(lexer_t *lexer);