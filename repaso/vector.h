#ifndef VECTOR_H
#define VECTOR_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <stdint.h>

#define OK 0
#define ERR 1

#define TRUE 1
#define FALSE 0

typedef struct {
	void* impl;
} Vec;



/* Static vector */

#ifdef STATIC_TEST

#define STATIC_VECTOR_SIZE 256

#define OK 0
#define ERR 1

#define TRUE 1
#define FALSE 0

typedef struct {
	char buf[STATIC_VECTOR_SIZE];
	size_t index;
	size_t n;
} Array;

extern int array_debug(const Array* arr);
extern void array_show(const Array* arr, void (*Show)(const void* elem));

extern int array_create(Array* arr, size_t n);
extern int array_is_full(const Array* arr);
extern int array_is_empty(const Array* arr);
extern int array_ins_ord(Array* arr, const void* elem, int (*Cmp)(const void* lhs, const void* rhs));
extern int array_get_i(const Array* arr, size_t i, void* buf);
extern int array_rem(Array* arr, const void* key, int (*Cmp)(const void* lhs, const void* rhs));
extern void array_destroy(Array* arr);

#endif

#ifdef DYNAMIC_TEST

/* Dynamic vector */

typedef struct {
	void* buf;
	size_t index;
	size_t n;
	size_t cap;
} Vector;

extern int vector_debug(const Array* arr);
extern void vector_show(const Array* arr, void (*Show)(const void* elem));

extern int vector_create(Vector* vec, size_t n);
extern int vector_is_full(Vector* vec);
extern int vector_is_empty(Vector* vec);
extern int vector_ins_ord(Vector* vec, void* elem, int (*Cmp)(const void* lhs, const void* rhs));
extern int vector_get_i(Vector* vec, size_t i, void* buf);
extern int vector_rem(Vector* vec, void* key, int (*Cmp)(const void* lhs, const void* rhs));
extern void array_destroy(Vector* vec);

#endif

#endif /* VECTOR_H */
