#include "json.h"

enum TokenKind {
    TOK_EOF = -1, /* EOF */
    TOK_INVALID = 0,
    TOK_NUM, /* Number literal */
    TOK_STR, /* String literal */
    TOK_TRUE, /* "true" */
    TOK_FALSE, /* "false" */ 
    TOK_NULL,  /* "null" */
    TOK_LBRACK, /* [ */
    TOK_RBRACK, /* ] */
    TOK_LCURLY, /* { */
    TOK_RCURLY, /* } */
    TOK_QUOTE, /* " */
    TOK_COMMA, /* , */
    TOK_COLON, /* : */
};

struct Token {
    enum TokenKind kind;    
    const char *lexeme;
    size_t len;
};

struct JsonLexer {
    const char *src;
    const char *pos;
    size_t col;
    size_t line;
};


struct JsonArray {
	size_t n;
	void *buf;
};

struct Node {
	struct Node *l, *r;
	const char *key;
	void *buf;
};

struct JsonObject {
	struct Node *tree;
	size_t n;
};

struct JsonString {
	size_t len;
	const char *str;
};

#define ISASCIIWS(ch) ( \
	(ch) == '\n' || \
	(ch) == '\t' || \
	(ch) == '\f' || \
	(ch) == '\b' \
)

#define ISASCIIDIGIT(ch) ( \
	(ch) >= '0' || \
	(ch) <= '9' \
)

#define ISHEX(ch) ( \
	((ch) >= 'a' && \
	(ch) <= 'f') || \
	((ch) >= 'A' && \
	(ch) <= 'f') || \
	((ch) >= '0' && \
	(ch) <= '9') \
)

#define ISUNICODECONTROL(ch) ( \
	( \
		(ch) >= 0x0 && \
		(ch) <= 0x1f \
	) || \
	(ch) == 0x7f || \
	( \
		(ch) >= 0x80 && \
		(ch) <= 0x9f \
	) \
)

int ISUNICODECHARLIT(const char *str)
{
	int s;
	
	if(*str == 'u') {
		str++;
		s = 0; 
		while(ISHEX(*str) && s != 4) {
			s++;
			str++;
		}
	}

	return (s == 4) ? 1 : 0;
}

#define ISASCIIESCAPE(ch) ( \
	(ch) == '\n' || \
	(ch) == '\f' || \
	(ch) == '\t' || \
	(ch) == '\b' || \
	(ch) == '\r' || \
	(ch) == '\"' || \
	(ch) == '\\' || \
	(ch) == '/'     \
)

#define ISASCIIPUNCT(ch) ( \
	(ch) == '}' || \
	(ch) == '}' || \
	(ch) == '[' || \
	(ch) == ']' || \
	(ch) == ':' || \
	(ch) == ','  \
)
	
#define MAKE_TOKEN(k, s, l) (struct Token) { \
	.kind = (k), \
	.lexeme = (s), \
	.len = (l) \
}

static struct Token lexer_next(struct JsonLexer *lexer)
{
	const char *tok_s;
	struct Token tok;

	while(*lexer->pos) {
		if(ISASCIIWS(*lexer->pos)) {
			lexer->pos++;
			continue;
		}

		if(strcmp(lexer->pos, "true") == 0) {
			tok_s = lexer->pos;
			lexer->pos += 4;

			tok = MAKE_TOKEN(TOK_TRUE, "true", 4);
	
			return tok;
		}

		if(strcmp(lexer->pos, "false") == 0) {
			tok_s = lexer->pos;
			lexer->pos += 5;

			tok = MAKE_TOKEN(TOK_FALSE, "false", 5);

			return tok;
		}

		if(strcmp(lexer->pos, "null") == 0) {
			tok_s = lexer->pos;
			lexer->pos += 4;

			tok = MAKE_TOKEN(TOK_NULL, "null", 4);

			return tok;
		}

		if(*lexer->pos == '\"') {
			tok_s = lexer->pos;

			while(*lexer->pos != '\"' && !ISUNICODECONTROL(*lexer->pos) && *lexer->pos) {
				lexer->pos++;

				if(*lexer->pos == '\\') {
					lexer->pos++;
					if(!ISASCIIESCAPE(*lexer->pos) || !ISUNICODECHARLIT(lexer->pos)) {
						tok = MAKE_TOKEN(TOK_INVALID, tok_s, lexer->pos - tok_s);
						return tok;
					}
				}
				
			}

			if(!*lexer->pos) {
				tok = MAKE_TOKEN(TOK_INVALID, tok_s, lexer->pos - tok_s);
				return tok;
			}

			tok = MAKE_TOKEN(TOK_STR, tok_s, lexer->pos - tok_s);

			return tok;						
		}

		if(*lexer->pos == '-' || ISASCIIDIGIT(*lexer->pos)) {
			tok_s = lexer->pos;
			lexer->pos++;

			while(ISASCIIDIGIT(*lexer->pos) && *lexer->pos) {
				lexer->pos++;
			}

			if(*lexer->pos == '.') {
				lexer->pos++;
				while(ISASCIIDIGIT(*lexer->pos) && *lexer->pos) {
					lexer->pos++;
				}

				if(*(lexer->pos - 1) == '.') {
					tok = MAKE_TOKEN(TOK_INVALID, tok_s, lexer->pos - tok_s);
					return tok;
				}
			}

			if(*lexer->pos == 'e' || *lexer->pos == 'E') {
				lexer->pos++;
				if(*lexer->pos == '+' || *lexer->pos == '-') {
					lexer->pos++;
				}

				while(ISASCIIDIGIT(*lexer->pos) && *lexer->pos) {
					lexer->pos++;
				}

				if(*(lexer->pos - 1) == 'e' || *(lexer->pos - 1) == 'E'
				|| *(lexer->pos - 1) == '+' || *(lexer->pos - 1) == '-') {
					tok = MAKE_TOKEN(TOK_INVALID, tok_s, lexer->pos - tok_s);
					return tok;
				}
			}

			tok = MAKE_TOKEN(TOK_NUM, tok_s, lexer->pos - tok_s);

			return tok;
		}

		if(ISASCIIPUNCT(*lexer->pos)) {
			tok_s = lexer->pos;
			lexer->pos++;

			switch(*tok_s) {
				case '{': tok = MAKE_TOKEN(TOK_LCURLY, tok_s, 1);
				case '}': tok = MAKE_TOKEN(TOK_RCURLY, tok_s, 1);
				case '[': tok = MAKE_TOKEN(TOK_LBRACK, tok_s, 1);
				case ']': tok = MAKE_TOKEN(TOK_RBRACK, tok_s, 1);
				case ',': tok = MAKE_TOKEN(TOK_COMMA, tok_s, 1);
				case ':': tok = MAKE_TOKEN(TOK_COLON, tok_s, 1);
			}

			return tok;
		}
	
		tok = MAKE_TOKEN(TOK_INVALID, lexer->pos, 1);
		return tok;
	}

	tok = MAKE_TOKEN(TOK_EOF, "", 0);

	return tok;
}

static struct Token lexer_peek(struct JsonLexer *lexer)
{
	struct JsonLexer saved;
	saved = *lexer;
	return lexer_next(&saved);
}

static int token_equals(struct Token tok, enum TokenKind kind)
{
	if(tok.kind == kind) {
		return 1;
	}

	return 0;
}

/*
    json := value?
    
    value :=  object            
    		| array
            | string
            | number
            | "false"
            | "true"
            | "null" ;
            
    object := "{" member | ( member ",")* "}"
    
    member := string ":" value 
        
*/

static struct JsonValue *parse_json(struct JsonLexer *lexer);

static struct JsonValue *parse_value(struct JsonLexer *lexer);

static struct JsonValue *parse_object(struct JsonLexer *lexer);

static struct JsonValue *parse_array(struct JsonLexer *lexer);

static struct JsonValue *parse_string(struct JsonLexer *lexer);

static struct JsonValue *parse_number(struct JsonLexer *lexer);

static struct JsonValue *make_number(struct Token tok)
{
	struct JsonValue *new;

	new = malloc(sizeof(struct JsonValue));

	if(!new) {
		return NULL;
	}	

	new->kind = JSON_VAL_NUM;

	
}

static struct JsonValue *make_string(struct Token tok)
{
	struct JsonValue *new;

	new = malloc(sizeof(struct JsonValue));
	if(!new) {
		return NULL;
	}

	new->kind = JSON_VAL_STRING;
	new->val.str = malloc(sizeof(struct JsonString));

	if(!new->val.str) {
		free(new);
		return NULL;
	}

	new->val.str->len = tok.len;
	new->val.str->str = strndup(tok.lexeme, tok.len);

	if(!new->val.str->len) {
		free(new->val.str);
		free(new);
		return NULL;
	}

	return new;
}

static struct JsonValue *make_boolean(struct Token tok)
{
	struct JsonValue *new;

	new = malloc(sizeof(struct JsonValue));
	if(!new) {
		return NULL;
	}

	new->kind = JSON_VAL_BOOLEAN;
	new->val.num = (*(tok.lexeme) == 't') ? 1 : 0;

	return new;		
}

static struct JsonValue *make_null(void)
{
	struct JsonValue *new;

	new = malloc(sizeof(struct JsonValue));
	if(!new) {
		return NULL;
	}

	new->kind = JSON_VAL_NULL;
	new->val.num = 0;

	return new;		
}

static struct JsonValue *make_object(struct Token tok)
{
	
}

static struct JsonValue *add_member(struct JsonValue *obj, struct Token tok);
static struct JsonValue *make_array(struct Token tok);
static struct JsonValue *add_elem(struct JsonValue *arr, struct Token tok);

static struct JsonValue *parse_json(struct JsonLexer *lexer)
{
	struct JsonValue *value;

	value = parse_value(lexer);
	
	return value;
}

static struct JsonValue *parse_value(struct JsonLexer *lexer)
{
	struct JsonValue *value;
	struct Token tok;

	tok = lexer_peek(lexer);

	switch(tok.kind) {
		case TOK_NUM:
			value = make_number(lexer_next(lexer));
			break;
		case TOK_STR:
			value = make_string(lexer_next(lexer));
			break;
		case TOK_LCURLY:
			value = parse_object(lexer);
			break;
		case TOK_LBRACK:
			value = parse_array(lexer);
			break;
		case TOK_TRUE:
			value = make_boolean(lexer_next(lexer));
			break;
		case TOK_FALSE:
			value = make_boolean(lexer_next(lexer));
			break;
		case TOK_NULL:
			value = make_null();
			lexer_next(lexer);
			break;
		default:	return NULL;	
	}

	return value;
}

static struct JsonValue *parse_object(struct JsonLexer *lexer)
{
	struct JsonValue *value;
	struct Token tok;

	value = make_object();
	tok = lexer_peek(lexer);

	while(tok.kind != TOK_RCURLY) {
		add_member(value, parse_string(lexer), parse_value(lexer));
	}

	return value;
}

static struct JsonValue *parse_array(struct JsonLexer *lexer)
{
	struct JsonValue *value;
	struct Token tok;

	value = make_array();
	tok = lexer_next(lexer);

	while(tok.kind != TOK_RBRACK) {
		add_elem(value, parse_value(lexer));
	}

	return value;	
}

static struct JsonValue *parse_string(struct JsonLexer *lexer)
{
	struct JsonValue *value;

	value = make_string(lexer_next(lexer));

	return value;
}

static struct JsonValue *parse_number(struct JsonLexer *lexer)
{
	struct JsonValue *value;

	value = make_number(lexer_next(lexer));

	return value;
}

struct JsonValue *json_parse(const char *src, int opt)
{
    struct JsonValue *json;
    struct JsonLexer lexer;
    
    if(!src) {
        return NULL;
    }
    
    lexer.src = src;
    lexer.pos = src;
    
    json = parse_json(&lexer);
    
    return json;
}

int json_stringify(struct JsonValue *val, char *buf, int opt);

