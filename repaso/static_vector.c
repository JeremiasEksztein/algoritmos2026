#include "vector.h"

static size_t BSEARCH(const void* buf, const void* key, size_t count, size_t n, int (*Cmp)(const void* lhs, const void* rhs));

size_t BSEARCH(const void* buf, const void* key, size_t count, size_t n, int (*Cmp)(const void* lhs, const void* rhs))
{
	const char* base;
	const char* lo;
	const char* hi;
	const char* med;

	int diff;
	
	if(!buf || !key || count == 0 || n == 0 || !Cmp) {
		return SIZE_MAX;
	} 

	base = buf;
	lo = buf; 
	hi = base + (count - 1) * n;
	med = lo + ((hi - lo) / (n * 2)) * n;

	diff = 0;

	while(lo <= hi && (diff = Cmp(med, key)) != 0) {
		if(diff < 0) {
			hi = med - n;			
		} else if(diff > 0) {
			lo = med + n;
		}

		med = lo + ((hi - lo) / (n * 2)) * n;
	}

	if(lo > hi) {
		return SIZE_MAX;
	}

	return (med - base);
}

int array_debug(const Array* arr)
{
	if(!arr) {
		return ERR;
	}

	fprintf(stderr, "Array { .buf = %p, .index = %lu, .n = %lu }\n", arr->buf, arr->index, arr->n);

	return OK;	
}

void array_show(const Array* arr, void (*Show)(const void* elem))
{
	size_t i;
	
	if(!arr || !Show) {
		return;
	}

	for(i = 0; i < arr->index; i += arr->n) {
		Show(arr->buf + i);
	}

	printf("\n");
}

int array_create(Array* arr, size_t n)
{
	if(!arr || n <= 0 || n > STATIC_VECTOR_SIZE) {
		return ERR;
	} 	

	arr->index = 0;
	arr->n = n;
	memset(arr->buf, 0, STATIC_VECTOR_SIZE);

	return OK;
}

int array_is_full(const Array* arr)
{
	if(!arr) {
		return FALSE;
	}
	
	return ((STATIC_VECTOR_SIZE - arr->index) < arr->n) ? TRUE : FALSE;	
}

int array_is_empty(const Array* arr)
{
	if(!arr) {
		return TRUE;
	}
	
	return ((STATIC_VECTOR_SIZE - arr->index) < arr->n) ? FALSE : TRUE;
}

int array_ins_ord(Array* arr, const void* elem, int (*Cmp)(const void* lhs, const void* rhs))
{
	char* i;
	char* j;
	
	if(!arr || !elem || !Cmp) {
		return ERR;
	}	

	if((STATIC_VECTOR_SIZE - arr->index) < arr->n) {
		return ERR;
	}

	if(arr->index == 0) {
		memcpy(arr->buf, elem, arr->n);
		arr->index += arr->n;
		return OK;
	}

	i = arr->buf;
	j = arr->buf + STATIC_VECTOR_SIZE - 1;

	while(Cmp(i, elem) > 0 && i < j) {
		i += arr->n;
	}

	if(Cmp(i, elem) == 0 || i >= j) {
		return ERR;
	}

	memcpy(i + arr->n, i, arr->index - (i - arr->buf) + arr->n);
	memcpy(i, elem, arr->n);

	arr->index += arr->n;

	return OK;
}

int array_get_i(const Array* arr, size_t i, void* buf)
{
	const char* tmp;
	
	if(!arr || i > (STATIC_VECTOR_SIZE / arr->n) || !buf) {
		return ERR;
	}	

	tmp = arr->buf + i * arr->n;

	memcpy(buf, tmp, arr->n);

	return OK;
}

int array_rem(Array* arr, const void* key, int (*Cmp)(const void* lhs, const void* rhs))
{
	size_t i;
	char* j;
	
	if(!arr || !key || !Cmp) {
		return ERR;
	}	

	i = 0;
	j = arr->buf;

	if((i = BSEARCH(arr->buf, key, arr->index / arr->n, arr->n, Cmp)) == SIZE_MAX) {
		return ERR;
	}	

	memcpy(j + i, j + i + arr->n, arr->index - i + arr->n);

	arr->index -= arr->n;

	return OK;
}

void array_destroy(Array* arr)
{
	if(!arr) {
		return;
	}

	arr->index = 0;
	arr->n = 0;
	memset(arr->buf, 0, STATIC_VECTOR_SIZE);
}
