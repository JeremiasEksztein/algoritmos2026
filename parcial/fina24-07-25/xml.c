#include "xml.h"

typedef enum {
	TOK_HEADER_START,
	TOK_HEADER_END,
	TOK_LITERAL,
	TOK_EQ,
	TOK_TAG_START,
	TOK_TAG_END,
	TOK_EOF,
	TOK_ERR
} eTokenKind;

typedef struct {
	eTokenKind kind;
	const char *lexeme;
	unsigned len;
} tToken;

typedef struct {
	char line[1024];
	char *curr;
	tToken lastToken;
	int lastTokenSet;
} tLexer;

int parseXML(tLexer *lex);
int parseHeaderr

int validateXML(const char *path)
{
	FILE *fp;
	int ret = TRUE;
	tLexer lex;
	
	fp = fopen(path, "rt");

	if(!fp) {
		return FALSE;
	}

	lexerNew(&lex, fp);

	ret = parseXML(&lex);

	fclose(fp);

	return ret;
}

