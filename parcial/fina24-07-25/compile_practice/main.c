#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdarg.h>

#define OK		0
#define ERROR	1

#define TRUE 	1
#define FALSE 	0

#define BUFLEN	1024

void eprintf(const char *msg, ...)
{
	va_list ap;

	va_start(ap, msg);

	vfprintf(stderr, msg, ap);

	va_end(ap);
}

typedef enum {
	TOK_HEADER_START,
	TOK_HEADER_END,
	TOK_TAG_START,
	TOK_TAG_END,
	TOK_LITERAL,
	TOK_STRLIT,
	TOK_EOF,
} eTokenKind;

typedef struct {
	eTokenKind kind;
	const char *lexeme;
	unsigned n;
} tToken;

typedef struct {
	FILE *fp;
	char buf[BUFLEN];
	char *curr;
} tLexer;

void lexerNew(tLexer *lex, const char *path);
int _lexerGetline(tLexer *lex);
tToken lexerPeek(tLexer *lex);
tToken lexerNext(tLexer *lex);
void lexerDelete(tLexer *lex);

int expect(tLexer *lex, eTokenKind expects);
int expectLike(tLexer *lexer, eTokenKind expects, const char *like);
int accept(tLexer *lex, eTokenKind accepts);
int acceptLike(tLexer *lex, eTokenKind accepts, const char *like);

/*
	xml 		:= header tag*
	header 		:= <xml-header-start> attrib <xml-header-end>
	attrib 		:= <literal> '=' '"' <literal> '"'
	tag 		:= <xml-tag-start> tag-body <xml-tag-end> 
	tag-body 	:= <literal> | tag*
*/

int parseXML(tLexer *lex);
int parseHeader(tLexer *lex);
int parseAttrib(tLexer *lex);
int parseTag(tLexer *lex);
int parseTagBody(tLexer *lex);

int main(int argc, char **argv)
{
	FILE *fp;
	char buf[BUFLEN], *curr;
	
	if(argc != 2) {
		eprintf(
			"[ERROR]: Argument count is less than 2\n"
			"[USAGE]: %s [PATH]\n",
			argv[0]
		);
		return ERROR;
	}

	while(!feof(fp)) {
		if(!fgets(buf, BUFLEN, fp)) {
			eprintf("[ERROR]: fgets()\n");
			fclose(fp);
			return ERROR;
		}

		if(!(curr = strrchr(buf, '\n'))) {
			eprintf("[ERROR]: Line too long\n");
			fclose(fp);
			return ERROR;
		}

		*curr = '\0';
		curr = buf;

		while(*curr) {
			if(isspace(*curr)) {
				curr++;
				continue;
			}

			if(*curr == '<') {
				
			}

			if(isascii(*curr)) {
				
			}
		}
	}

	return OK;
}
