#ifndef SO_TP2_HASHMAP_H
#define SO_TP2_HASHMAP_H


#define INITIAL_SIZE (256)
#define MAX_CHAIN_LENGTH (8)

#define MAP_MISSING -3  /* No such element */
#define MAP_FULL -2 	/* Hashmap is full */
#define MAP_OMEM -1 	/* Out of Memory */
#define MAP_OK 0 	/* OK */


typedef void *any_t;
typedef int (*PFany)(any_t, any_t);
typedef any_t map_t;


typedef struct _hashmapElement{
    char* key;
    int inUse;
    any_t data;
} hashmapElement;

typedef struct _hashmap_map{
    int tableSize;
    int size;
    hashmapElement *data;
} hashmapMap;

map_t newHashMap();
unsigned long crc32(const unsigned char *s, unsigned int len);
unsigned int hashmapHashInt(hashmapMap* m, char* keystring);
int hashmapHash(map_t in, char* key);
int hashmapRehash(map_t in);
int hashmapPut(map_t in, char* key, any_t value);
int hashmapGet(map_t in, char* key, any_t *arg);
int hashmapIterate(map_t in, PFany f, any_t item);
int hashmapRemove(map_t in, char* key);
void hashmapFree(map_t in);
int hashmapLength(map_t in);

#endif //SO_TP2_HASHMAP_H
