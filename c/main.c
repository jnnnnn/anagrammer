#include "hash.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 255

int cmpfunc(const void *a, const void *b) { return *(char *)a - *(char *)b; }

int main(void) {
    HashTable *sortedletters = sht_create();

    FILE *fp;
    char word[BUFFER_SIZE];
    char key[BUFFER_SIZE];
    fp = fopen("../enable1.txt", "r");
    int i = 3;
    while (fgets(word, BUFFER_SIZE, (FILE *)fp) && word[0] > 0) {
        size_t length = strnlen(word, BUFFER_SIZE - 1);
        word[--length] = '\0';
        memcpy(&key, &word, length + 1);
        qsort(key, length, sizeof(char), &cmpfunc);
        sht_insert(sortedletters, key, word);
    }
    fclose(fp);

    while (1) {
        printf("Enter some letters: ");
        fgets(word, BUFFER_SIZE, stdin);
        size_t length = strnlen(word, BUFFER_SIZE - 1);
        if (word[0] < 1 || length == 1) // empty string (including \n)
            continue;
        word[--length] = '\0'; // remove the \n
        qsort(word, length, sizeof(char), &cmpfunc);
        LookupResult result = sht_lookup(sortedletters, word);
        printf("Anagrams: ");
        if (result.count) {
            for (unsigned int i = 0; i < result.count; i++) {
                printf("%s ", result.values[i]);
            }
            printf("\n");
        } else {
            printf("None\n");
        }
    }

    sht_free(sortedletters);
    return 0;
}