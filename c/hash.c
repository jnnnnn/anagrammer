// String Hash Table (sht) maps a key string to a list of value strings.

#include <stdlib.h>
#include <string.h>

#include "hash.h"

// hash table sizes are generally supposed to be prime numbers to avoid harmonic
// hash collisions but this code is intended for teaching purposes so I consider
// searching for primes to be unnecessary additional complexity
#define INITIAL_SIZE 17

typedef struct {
    char **values; // e.g. ['arches', 'chaser', 'search']
    size_t count;  // e.g. 3
    char *key;     // e.g. 'acehrs'
} Bucket;

struct HashTable_s {
    Bucket *buckets;
    size_t count; // How many buckets are in the table, e.g. 1
    size_t size;  // How much space is in the table, e.g. INITIAL_SIZE
};

typedef struct HashTable_s HashTable;

HashTable *sht_create() {
    HashTable *table = (HashTable *)malloc(sizeof(HashTable));
    table->buckets = malloc(sizeof(Bucket) * INITIAL_SIZE);
    memset(table->buckets, 0, sizeof(Bucket) * INITIAL_SIZE);
    table->count = 0;
    table->size = INITIAL_SIZE;
    return table;
}

// from https://stackoverflow.com/a/7666577/412529 -- djb2 by Dan Bernstein
unsigned long hash(char *str) {
    unsigned long hash = 5381;
    while (*str)
        hash = ((hash << 5) + hash) + *str++; /* hash * 33 + c */
    return hash;
}

// Dynamically resize the hash table by iterating through the buckets and (if
// set) adding each bucket to a new internal array of a different size
void sht_rehash(HashTable *table, size_t newSize) {
    Bucket *newbuckets = malloc(sizeof(Bucket) * newSize);
    memset(newbuckets, 0, sizeof(Bucket) * newSize);
    for (size_t i = 0; i < table->size; i++) {
        Bucket *bucket = &table->buckets[i];
        if (bucket->key) {
            newbuckets[hash(bucket->key) % newSize] = *bucket;
        }
    }
    free(table->buckets);
    table->buckets = newbuckets;
    table->size = newSize;
}

Bucket *sht_find_bucket(HashTable *table, char *key) {
    unsigned long i = hash(key) % table->size;
    while (table->buckets[i].key != NULL) {
        if (strcmp(table->buckets[i].key, key) == 0) {
            return &table->buckets[i];
        }
        i = (i + 1) % table->size;
    }
    return NULL;
}

char *copy_string(char *s) {
    size_t length = strlen(s);
    char *copy = malloc(length + 1); // + 1 for the null terminator \0
    memcpy(copy, s, length + 1);     // copy all bytes including null terminator
    return copy;
}

Bucket *sht_newbucket(HashTable *table, char *key) {
    // make sure there will be some empty buckets
    if (table->count > 0.8 * table->size) {
        sht_rehash(table, table->size * 2);
    }

    // iterate until we find an empty bucket
    unsigned long i = hash(key) % table->size;
    while (table->buckets[i].key != NULL) {
        i = (i + 1) % table->size;
    }

    // create an entry at the empty bucket we found
    Bucket *entry = &table->buckets[i];
    // we need to copy key because we don't own it, but table needs to own the
    // key inside it (otherwise something external would need to manage
    // ownership of all the keys)
    entry->key = copy_string(key);
    table->count++;
    return entry;
}

void sht_insert(HashTable *table, char *key, char *value) {
    Bucket *bucket = sht_find_bucket(table, key);
    if (!bucket)
        bucket = sht_newbucket(table, key);
    size_t index = bucket->count;
    if (index == 0) {
        bucket->count = 1;
        bucket->values = malloc(sizeof(char **));
    } else {
        bucket->count++;
        bucket->values =
            realloc(bucket->values, sizeof(char **) * bucket->count);
    }
    bucket->values[index] = copy_string(value);
}

// the array and strings in this return value are still owned by the table
LookupResult sht_lookup(HashTable *table, char *key) {
    Bucket *bucket = sht_find_bucket(table, key);
    LookupResult result;
    if (bucket) {
        result.count = bucket->count;
        result.values = bucket->values;
    } else {
        result.count = 0;
        result.values = NULL;
    }
    return result;
}

void sht_free(HashTable *table) {
    for (size_t i = 0; i < table->size; i++) {
        Bucket *bucket = &table->buckets[i];
        if (bucket) {
            for (size_t j = 0; j < bucket->count; j++) {
                free(bucket->values[j]);
            }
            free(bucket->values);
            free(bucket->key);
        }
    }
    free(table->buckets);
    free(table);
}

void sht_dump(HashTable *table) {
    printf("Table has %lld buckets.\n", table->count);
    for (size_t i = 0; i < table->size; i++) {
        Bucket *bucket = &table->buckets[i];
        if (bucket) {
            printf("bucket %lld (key %8s) has %lld values: ", i, bucket->key,
                   bucket->count);
            for (size_t j = 0; j < bucket->count; j++) {
                printf("%s ", bucket->values[j]);
            }
            printf("\n");
        }
    }
}