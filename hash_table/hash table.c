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
HashTable_t* create(){
    HashTable_t *hash_table= (HashTable_t*)malloc(sizeof(HashTable_t));
    return hash_table;

}
bool add( HashTable_t * table, const char* key, int value){
    Binding_t *binding_ptr = (Binding_t*)malloc(sizeof(Binding_t));
    binding_ptr->key=key;
    binding_ptr->value=value;
    binding_ptr->next=NULL;
    int hash_value =hash(key);
    if(table->buckets[hash_value]==NULL){
         table->buckets[hash_value]=binding_ptr;
         return true;
    }else{
        Binding_t * temp=table->buckets[hash_value];
        if(temp->key==key){
            temp=binding_ptr;
            return false;
        }else{
            while ( temp->next!=NULL )
            {
                temp=temp->next;
                if(temp->key==key){
                    temp=binding_ptr;
                    return false;
                }
            }
            temp->next=binding_ptr;
            return true;
        } 
    } 
}
void delete_table( HashTable_t* table){
    for (int i = 0;i < BUCKET_COUNT;i++){
        free(table->buckets[i]);
        table->buckets[i]=NULL;
    }
    free(table);
}
bool remove( HashTable_t* table, const char* key){
    int hash_value = hash(key);
    if(table->buckets[hash_value]!=NULL){
        if(table->buckets[hash_value]->key==key){
            free(table->buckets[hash_value]);
            table->buckets[hash_value]=NULL;
            return true;
        }
        else if(table->buckets[hash_value]->next!=NULL){
            Binding_t *prvevious =(Binding_t*) malloc(sizeof(Binding_t));
            Binding_t *temp = table->buckets[hash_value]->next;
            while (temp!=NULL)
            {
                if((temp->key)==key){
                    prvevious->next=temp->next;
                    free(temp);
                    return true;
                }else{
                    prvevious=temp;
                    temp = temp->next;
                }  
            }
            return false;   
        }
    }else{
        return false;
    }
}
Binding_t* find(HashTable_t* table, const char* key){
   int hash_value = hash(key);
   if(table->buckets[hash_value]!=NULL){
       if(table->buckets[hash_value]->key==key){
           return table->buckets[hash_value];
       }
       else if(table->buckets[hash_value]->next!=NULL){
           Binding_t *temp = table->buckets[hash_value]->next;
           while (temp!=NULL)
           {
            if((temp->key)==key){
                return temp;
            }else{
                temp = temp->next;
            }  
           }
           return NULL;   
       }
   }else{
       return NULL;
   }
}
