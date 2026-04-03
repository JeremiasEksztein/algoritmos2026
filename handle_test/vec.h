#ifndef VEC_H
#define VEC_H

#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

#define OK 0
#define ERR 1

#define TRUE 1
#define FALSE 0

typedef int (*Cmp)(const void* lhs, const void* rhs);
typedef void (*Show)(const void* elem);

typedef struct {
	void* impl;
} Vec;

int vec_new(Vec* vec, size_t n);

void vec_debug(Vec* vec);

void vec_show(Vec* vec, Show show_func);

int vec_insert(Vec* vec, void* elem, Cmp cmp_func);

int vec_fetch(Vec* vec, size_t n, void* buf);

size_t vec_bsearch(Vec* vec, void* key, Cmp cmp_func);

int vec_remove(Vec* vec, void* key, Cmp cmp_func);

int vec_is_full(Vec* vec);

int vec_is_empty(Vec* vec);

void vec_destroy(Vec* vec);

#endif /* VEC_H */
