#include <stdbool.h>
#define BUCKET_COUNT 1024

struct Binding;
struct HashTable;

typedef struct HashTable HashTable_t;
typedef struct Binding Binding_t;

unsigned int hash(const char* key);
HashTable_t* create();
bool add( HashTable_t * table, const char* key, int value);
void delete_table( HashTable_t* table);
bool remove( HashTable_t* table, const char* key);
Binding_t* find(HashTable_t* table, const char* key);

