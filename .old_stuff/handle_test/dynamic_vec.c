#include "vec.h"

typedef struct {
	char* buf;
	size_t i;
	size_t n;
	size_t cap;
} Vector;

#define GROW_FACTOR 0.75

static int RESIZE(Vector* vec);
static size_t BSEARCH(const void* buf, size_t count, size_t n, const void* key, Cmp cmp_func);

int RESIZE(Vector* vec)
{
	char* tmp;
	if(!vec) {
		return ERR;
	}

	tmp = realloc(vec->buf, vec->cap * vec->n * 2);

	if(!tmp) {
		return ERR;
	}

	vec->buf = tmp;
	vec->cap *= 2;

	return OK;
}

size_t BSEARCH(const void* buf, size_t count, size_t n, const void* key, Cmp cmp_func)
{
	const char* base;
	const char* lo;
	const char* hi;
	const char* med;
	int diff;

	if(!buf || count == 0 || n == 0 || !key || !cmp_func) {
		return SIZE_MAX;
	}

	base = buf;
	lo = base;
	hi = base + (count - 1) * n;
	med = lo + ((hi - lo) / (2 * n)) * n;

	while(lo <= hi && (diff = cmp_func(med, key)) != 0) {
		if(diff > 0) {
			lo = med + n;
		} else {
			hi = med - n;
		}

		med = lo + ((hi - lo) / (2 * n)) * n;
	}

	if(lo > hi) {
		return SIZE_MAX;
	} 

	return ((med - base) / n);
}

int vec_new(Vec* vec, size_t n)
{
	Vector* v;
	
	if(!vec || n <= 0 || n == SIZE_MAX) {
		return ERR;
	}

	v = calloc(1, sizeof(Vector));

	if(!v) {
		vec->impl = NULL;
		return ERR;
	}

	v->buf = malloc(sizeof(n) * 10);

	if(!v->buf) {
		free(v);
		vec->impl = NULL;
		return ERR;
	}

	v->i = 0;
	v->n = n;
	v->cap = 10;
		
	vec->impl = v;

	return OK;
}

void vec_debug(Vec* vec)
{
	Vector* v;
	
	if(!vec || !vec->impl) {
		return;
	}

	v = vec->impl;

	fprintf(stderr, "Vec { .buf = %p, .i = %lu, .n = %lu, .cap = %lu }\n", v->buf, v->i, v->n, v->cap);
}

void vec_show(Vec* vec, Show show_func)
{
	Vector* v;
	size_t i;
	
	if(!vec || !vec->impl || !show_func) {
		return;
	}

	v = vec->impl;

	for(i = 0; i < v->i; i++) {
		show_func(v->buf + i * v->n);
	}

	fprintf(stderr, "\n");
}

int vec_insert(Vec* vec, void* elem, Cmp cmp_func)
{
	Vector* v;
	char* i;
	char* j;
	
	if(!vec || !vec->impl || !elem || !cmp_func) {
		return ERR;
	}

	v = vec->impl;

	if((v->cap - v->i) * v->n < v->n) {
		if(RESIZE(v)) {
			return ERR;
		}
	}

	if(v->i == 0) {
		memcpy(v->buf, elem, v->n);
		v->i++;
		return OK;
	}

	i = v->buf;
	j = v->buf + 256 * v->n;

	while(cmp_func(i, elem) > 0 && i < j) {
		i += v->n;
	}

	if(cmp_func(i, elem) == 0 || i >= j) {
		return ERR;
	}

	memcpy(i + v->n, i, v->i * v->n - (i - v->buf) + v->n);
	memcpy(i, elem, v->n);

	v->i++;

	return OK;
}

int vec_fetch(Vec* vec, size_t i, void* buf)
{
	Vector* v;
	const char* tmp;

	if(!vec || !vec->impl || i == 0 || !buf) {
		return ERR;
	}

	v = vec->impl;
	tmp = v->buf + i * v->n;

	memcpy(buf, tmp, v->n);
	
	return OK;
}

size_t vec_bsearch(Vec* vec, void* key, Cmp cmp_func)
{
	Vector* v;

	v = vec->impl;

	return BSEARCH(v->buf, v->i, v->n, key, cmp_func);
}

int vec_remove(Vec* vec, void* key, Cmp cmp_func)
{
	Vector* v;
	size_t i;
	char* j;

	if(!vec || !vec->impl || !key || !cmp_func) {
		return ERR;
	}

	v = vec->impl;
	i = 0;
	j = v->buf;

	if((i = BSEARCH(v->buf, v->i, v->n, key, cmp_func)) == SIZE_MAX) {
		return ERR;
	}

	memcpy(j + i * v->n, j + i * v->n + v->n, (v->i - i) * v->n + v->n);

	v->i--;

	return OK;
}

int vec_is_full(Vec* vec)
{
	Vector* v;
	v = vec->impl;
	return ((256 - v->i * v->n) < v->n) ? TRUE : FALSE; 
}

int vec_is_empty(Vec* vec)
{
	Vector* v;
	v = vec->impl;
	return ((256 - v->i * v->n) < v->n) ? FALSE : TRUE; 	
}

void vec_destroy(Vec* vec)
{
	Vector* v;
	if(!vec) {
		return;
	} 
	if(!vec->impl) {
		return;
	}

	v = vec->impl;

	free(v->buf);
	free(v);
	vec->impl = NULL;
}
