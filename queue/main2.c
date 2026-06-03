#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stddef.h>

#define MIN(x, y) ((x) < (y) ? (x) : (y))

typedef struct sNode tNode;
struct sNode {
    tNode *next;
    size_t n;
    void *buf;
};

typedef struct {
    tNode *front,*back;
} tLinkedQueue;

void linkedqueue_new(tLinkedQueue *q)
{
    if(!q) {
        return;
    }
    
    q->front = NULL;
    q->back = NULL;
}

int linkedqueue_add(tLinkedQueue *q, const void *elem, size_t n)
{
    tNode *tmp;
    
    if(!q || !elem) {
        return 1;
    }
    
    tmp = malloc(sizeof(tNode));
    
    if(!tmp) {
        return 1;
    }
    
    tmp->buf = malloc(n);
    
    if(!tmp->buf) {
        free(tmp);
        return 1;
    }
    
    tmp->n = n;
    tmp->next = NULL;
    memcpy(tmp->buf, elem, n);
    
    if(!q->front) {
        q->front = tmp;
    } else {
        q->back->next = tmp;
    }
    
    q->back = tmp;
    
    return 0;
}

int linkedqueue_rem(tLinkedQueue *q, void *buf, size_t n)
{
    tNode *tmp;
    
    if(!q || !buf) {
        return 1;
    }
    
    if(!q->front) {
        return 1;
    } else {
        memcpy(buf, q->front->buf, MIN(q->front->n, n));
        tmp = q->front;
        q->front = q->front->next;
        if(!q->front) {
            q->back = NULL;
        }
        
        free(tmp->buf);
        free(tmp);
    }
    
    return 0;
}

int linkedqueue_first(const tLinkedQueue *q, void *buf, size_t n)
{
    if(!q || !buf) {
        return 1;
    }
    
    if(!q->front || !q->back) {
        return 1;
    } else {
        memcpy(buf, q->front->buf, MIN(q->front->n, n));
    }
    
    return 0;    
}

int linkedqueue_is_empty(const tLinkedQueue *q)
{
    if(!q || q->front) {
        return 0;
    }
    
    return 1;
}

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
int linkedqueue_is_full(const tLinkedQueue *q, size_t n)
{
    return 0;
}
#pragma GCC diagnostic pop

void linkedqueue_destroy(tLinkedQueue *q)
{
    tNode *tmp;
    
    if(!q) {
        return;
    }

    while(q->front) {
        tmp = q->front;
        q->front = q->front->next;
        free(tmp->buf);
        free(tmp);
    }
    
    q->front = NULL;
    q->back = NULL;
}

typedef struct {
    int cod_prod;
    int cant;
} tEntry;

int main(int argc, char **argv)
{
    FILE *wholesale, *retail, *movs, *tmp;
    int limit, sum;
    tEntry curr, prev;
    tLinkedQueue q;
    
    if(argc != 2) {
        fprintf(stderr, "Err: have to input limit for splitting\n");
        return 1;
    }

    sscanf(argv[1], "%d", &limit);

    movs = fopen("movimientos.dat", "rb");
    
    if(!movs) {
        fprintf(stderr, "Err: have no movimientos.dat\n");
        return 1;
    }
    
    wholesale = fopen("mayorista.dat", "wb");
    
    if(!wholesale) {
        fclose(movs);
        return 1;
    }
    
    retail = fopen("minorista.dat", "wb");
    
    if(!retail) {
        fclose(wholesale);
        fclose(movs);
        return 1;
    }
    
    linkedqueue_new(&q);
    
    fread(&curr, sizeof(tEntry), 1, movs);
    while(!feof(movs)) {
        memcpy(&prev, &curr, sizeof(tEntry));
        sum = 0;
        
        while(!feof(movs) && prev.cod_prod == curr.cod_prod)  {
            sum += curr.cant;
            linkedqueue_add(&q, &curr, sizeof(tEntry));
            fread(&curr, sizeof(tEntry), 1, movs);
        }
        
        tmp = (sum >= limit) 
                    ? wholesale
                    : retail;
        
        while(!linkedqueue_is_empty(&q)) {
            linkedqueue_rem(&q, &prev, sizeof(tEntry));
            fwrite(&prev, sizeof(tEntry), 1, tmp);
        }
    }
    
    fclose(retail);
    fclose(wholesale);
    fclose(movs);
    
    linkedqueue_destroy(&q);
    
    return 0;
}