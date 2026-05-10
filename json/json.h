#ifndef JSON_H
#define JSON_H

#include <stddef.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

enum JsonValueKind {
    JSON_VAL_NULL,
    JSON_VAL_STRING,
    JSON_VAL_NUM,
    JSON_VAL_ARRAY,
    JSON_VAL_OBJECT,
    JSON_VAL_BOOLEAN,
};

struct JsonArray;
struct JsonObject;
struct JsonString;

struct JsonValue {
    enum JsonValueKind kind;
    union {
		struct JsonString *str;
		
		double num;    

		struct JsonArray *arr; 

		struct JsonObject *obj;   

        int boolean;
    } val;
};

struct JsonValue *json_parse(const char *src, char *errbuf);

int json_stringify(struct JsonValue *val, char *dst, char *errbuf);

#endif
