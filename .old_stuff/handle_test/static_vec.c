#include "vec.h"

typedef struct {
	char buf[256];
	size_t i;
	size_t n;
} Array;

static size_t BSEARCH(const void* buf, size_t count, size_t n, const void* key, Cmp cmp_func);

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
	Array* arr;
	
	if(!vec || n <= 0 || n == SIZE_MAX) {
		return ERR;
	}

	arr = calloc(1, sizeof(Array));

	if(!arr) {
		vec->impl = NULL;
		return ERR;
	}

	arr->n = n;
		
	vec->impl = arr;

	return OK;
}

void vec_debug(Vec* vec)
{
	Array* arr;
	
	if(!vec || !vec->impl) {
		return;
	}

	arr = vec->impl;

	fprintf(stderr, "Vec { .buf = %p, .i = %lu, .n = %lu }\n", arr->buf, arr->i, arr->n);
}

void vec_show(Vec* vec, Show show_func)
{
	Array* arr;
	size_t i;
	
	if(!vec || !vec->impl || !show_func) {
		return;
	}

	arr = vec->impl;

	for(i = 0; i < arr->i; i++) {
		show_func(arr->buf + i * arr->n);
	}

	fprintf(stderr, "\n");
}

int vec_insert(Vec* vec, void* elem, Cmp cmp_func)
{
	Array* arr;
	char* i;
	char* j;
	
	if(!vec || !vec->impl || !elem || !cmp_func) {
		return ERR;
	}

	arr = vec->impl;

	if((256 - arr->i * arr->n) < arr->n) {
		return ERR;
	}

	if(arr->i == 0) {
		memcpy(arr->buf, elem, arr->n);
		arr->i++;
		return OK;
	}

	i = arr->buf;
	j = arr->buf + 256 * arr->n;

	while(cmp_func(i, elem) > 0 && i < j) {
		i += arr->n;
	}

	if(cmp_func(i, elem) == 0 || i >= j) {
		return ERR;
	}

	memcpy(i + arr->n, i, arr->i * arr->n - (i - arr->buf) + arr->n);
	memcpy(i, elem, arr->n);

	arr->i++;

	return OK;
}

int vec_fetch(Vec* vec, size_t i, void* buf)
{
	Array* arr;
	const char* tmp;

	if(!vec || !vec->impl || i == 0 || !buf) {
		return ERR;
	}

	arr = vec->impl;
	tmp = arr->buf + i * arr->n;

	memcpy(buf, tmp, arr->n);

	return OK;
}

size_t vec_bsearch(Vec* vec, void* key, Cmp cmp_func)
{
	Array* arr;

	arr = vec->impl;

	return BSEARCH(arr->buf, arr->i, arr->n, key, cmp_func);
}

int vec_remove(Vec* vec, void* key, Cmp cmp_func)
{
	Array* arr;
	size_t i;
	char* j;

	if(!vec || !vec->impl || !key || !cmp_func) {
		return ERR;
	}

	arr = vec->impl;
	i = 0;
	j = arr->buf;

	if((i = BSEARCH(arr->buf, arr->i, arr->n, key, cmp_func)) == SIZE_MAX) {
		return ERR;
	}

	memcpy(j + i * arr->n, j + i * arr->n + arr->n, (arr->i - i) * arr->n + arr->n);

	arr->i--;

	return OK;
}

int vec_is_full(Vec* vec)
{
	Array* arr;
	arr = vec->impl;
	return ((256 - arr->i * arr->n) < arr->n) ? TRUE : FALSE; 
}

int vec_is_empty(Vec* vec)
{
	Array* arr;
	arr = vec->impl;
	return ((256 - arr->i * arr->n) < arr->n) ? FALSE : TRUE; 	
}

void vec_destroy(Vec* vec)
{
	if(!vec) {
		return;
	} 
	if(!vec->impl) {
		return;
	}
	
	free(vec->impl);
	vec->impl = NULL;
}
