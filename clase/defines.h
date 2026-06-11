#ifndef DEFINES_H
#define DEFINES_H

#define MAX(x, y) ((x) > (y) ? (x) : (y))
#define MIN(x, y) ((x) > (y) ? (y) : (x))

typedef int (*cmp_fn)(const void *, const void *);
typedef void (*print_fn)(const void *);
typedef void (*visit_fn)(void *, void *);

#endif
