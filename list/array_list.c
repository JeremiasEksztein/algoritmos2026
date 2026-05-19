#include "list.h"

int arraylist_new(ArrayList *list);
int arraylist_with_cap(ArrayList *list, size_t cap);

size_t arraylist_len(const ArrayList *list);
int arraylist_is_empty(const ArrayList *list);
int arraylist_is_full(const ArrayList *list, size_t n);

int arraylist_set(ArrayList *list, size_t i, const void *elem, size_t n);
int arraylist_get(const ArrayList *list, size_t i, void *buf, size_t n);

int arraylist_addlo(ArrayList *list, const void *elem, size_t n);
int arraylist_addhi(ArrayList *list, const void *elem, size_t n);
int arraylist_add(ArrayList *list, size_t i, const void *elem, size_t n);

int arraylist_remlo(ArrayList *list, void *buf, size_t n);
int arraylist_remhi(ArrayList *list, void *buf, size_t n);
int arraylist_rem(ArrayList *list, size_t i, void *buf, size_t n);

int arraylist_add_ordered(ArrayList *list, const void *buf, size_t n, cmp_fn cmp);
int arraylist_rem_ordered(ArrayList *list, void *buf, size_t n, cmp_fn cmp);

int arraylist_add_unique(ArrayList *list, const void *buf, size_t n, cmp_fn cmp, unique_fn unique, void *user);
int arraylist_rem_unique(ArrayList *list, void *buf, size_t n, cmp_fn cmp, unique_fn unique, void *user);

int arraylist_sort(ArrayList *list, cmp_fn cmp);
int arraylist_search(const ArrayList *list, const void *key, cmp_fn cmp);

int arraylist_copy(ArrayList *dst, ArrayList *src);
int arraylist_concat(ArrayList *dst, ArrayList *src);
int arraylist_concatv(ArrayList *dst, ...);

int arraylist_map(ArrayList *dst, ArrayList *src, map_fn map, void* user);
int arraylist_filter(ArrayList *dst, ArrayList *src, filter_fn filter, void *user);
int arraylist_reduce(void *reduction, ArrayList *src, reduce_fn reduce, void *user);
int arraylist_foreach(ArrayList *list, foreach_fn foreach, void *user);

int arraylist_into_iter(ArrayList *list, Iterator *iter);

void arraylist_destroy(ArrayList *list);
