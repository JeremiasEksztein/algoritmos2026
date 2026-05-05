#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "vec.h"

typedef struct {
	unsigned id;
	const char name[24];
	const char surn[24];
	unsigned age;
	const char pob[32];
} Person;

int person_read_entry(const char* line, void* buf)
{
	const char* i;

	i = buf;

	if(!strrchr(i, "\0")) {
		return ERR;
	}
}

int person_cmp(const void* lhs, const void* rhs)
{
	return *(const int*)lhs - *(const int*)rhs;
}

void person_show(const void* elem)
{
	const Person* pers;

	pers = elem;

	fprintf(stderr, "Person { \
		id: %u, \
		name: %s, \
 		surn: %s, \
		age: %u, \
		pob: %s \
	}\n", pers->id, pers->name, pers->surn, pers->age, pers->pob);
}

extern int load_from_text(Vec* vec, const char* path, size_t n, int (*read_entry)(const char* line, void* buf));

extern int load_from_bin(Vec* vec, const char* path);

int main(void)
{
	Vec vec;

	load_from_text(&vec, "test.txt", sizeof(Person), person_read_entry);

	vec_debug(&vec);
	vec_show(&vec, person_show);

	vec_destroy(&vec);
	
	return 0;
}

int load_from_text(Vec* vec, const char* path, size_t n, int (*read_line)(const char* line, void* buf))
{
	FILE* fp;
	char line_buf[256];
	void* bin_buf;
	
	if(!vec || !path) {
		return ERR;
	}

	fp = fopen(path, "rt");

	if(!fp) {
		return ERR;
	}

	if(vec_new(vec, n)) {
		fclose(fp);
		return ERR;
	}

	bin_buf = malloc(n);

	if(!bin_buf) {
		fclose(fp);
		vec_destroy(vec);
		return ERR;
	}

	while(feof(fp)) {
		fgets(line_buf, 256, fp);
		if(read_line(line_buf, bin_buf)) {
			fclose(fp);
			vec_destroy(vec);
			free(bin_buf);
			return ERR;
		}	
		vec_insert(vec, bin_buf, person_cmp);
	}

	fclose(fp);
	free(bin_buf);

	return OK;
}
