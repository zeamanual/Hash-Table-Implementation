#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include "hash table.h"
struct Binding{
    const char* key;
    int value;
    Binding_t* next;
};

struct HashTable{
    Binding_t* buckets[BUCKET_COUNT];
};
unsigned int hash(const char* key){
    int total = 0;
    for(int i = 0;i<strlen(key);i++){
        total =total + key[i];
    } 
    total= (total*6759)%BUCKET_COUNT;
      
    return total;
}
