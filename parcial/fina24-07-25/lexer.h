#ifndef LEXER_H
#define LEXER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <ctype.h>

#define BUFLEN 1024

typedef enum {
	TOK_END,
	TOK_ERR,
	TOK_HDR_START,
	TOK_TAG_START,
	TOK_TAG_END,
	TOK_RBRACK,
	TOK_LITERAL
} tTokenKind;

typedef struct {
	tTokenKind kind;
	const char *lexeme;
	size_t len;
} tToken;

typedef struct {
	FILE *fp;
	char buf[BUFLEN];
	char *curr;
} tLexer;

void lexerNew(tLexer *lex, const char *path);

tToken lexerNext(tLexer *lex);

tToken lexerPeek(const tLexer *lex);

void lexerDelete(tLexer *lex);

#endif
