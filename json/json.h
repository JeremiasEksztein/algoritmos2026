#ifndef JSON_H
#define JSON_H

#include <stddef.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

struct JsonValue {
    enum JsonValueKind {
        JSON_VAL_NULL,
        JSON_VAL_STRING,
        JSON_VAL_NUM,
        JSON_VAL_ARRAY,
        JSON_VAL_OBJECT,
        JSON_VAL_BOOLEAN,
    } kind;
    
    union {
        struct json_string {
            const char *buf;
        } str;
        
        struct json_num {
            enum JsonNumRepr {
                JSON_NUM_REPR_I32,
                JSON_NUM_REPR_I64,
                JSON_NUM_REPR_F32,
                JSON_NUM_REPR_F64,
            } repr;
            unsigned char buf[8];
        } num;
        
        struct json_array {
            size_t len;
            struct JsonValue *arr;
        } arr;
        
        struct json_object {
            size_t n;
            const char *keys;
            struct JsonValue *values;
        } obj;
        
        int boolean;
    };
};

struct JsonValue *json_parse(const char *src, int opt);

int json_stringify(struct JsonValue *val, char *buf, int opt);

#endif
