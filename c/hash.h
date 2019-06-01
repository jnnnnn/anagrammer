typedef struct HashTable_s HashTable;

HashTable *sht_create();
void sht_free(HashTable *table);
void sht_insert(HashTable *table, char *key, char *value);

typedef struct {
    unsigned int count;
    char **values;
} LookupResult;

LookupResult sht_lookup(HashTable *table, char *key);

void sht_dump(HashTable *table);