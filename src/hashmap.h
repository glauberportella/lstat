#ifndef _HASHMAP_H_
#define _HASHMAP_H_

#include <stdlib.h>
#include <stdbool.h>

#define EHASHMAPALLOCATION 0x2000

typedef enum {
  HASHMAP_EMPTY = 0,
  HASHMAP_OCCUPIED,
  HASHMAP_DELETED
} hashmap_state_t;

typedef struct {
  void* key;
  void* value;
  size_t hash;
  hashmap_state_t state;
} hashmap_item_t;

typedef struct {
  hashmap_item_t* items; 
  size_t size;
} hashmap_t;

hashmap_t* hashmap_init(size_t size);
void hashmap_destroy(hashmap_t* hashmap);

/**
 * @brief Função de hash para nosso little hashmap
 * 
 * @param hashmap 
 * @param key 
 * @param hashkeyfunc Se NULL assumimos que key é um size_t
 * @return size_t 
 */
size_t hashmap_hash(hashmap_t* hashmap, const void* key, size_t (*hashkeyfunc)(const hashmap_t*, const void*));

/**
 * @brief Guarda um valor no Hashmap
 * 
 * @param hashmap 
 * @param key 
 * @param value 
 */
bool hashmap_set(hashmap_t* hashmap, void* key, void* value);

/**
 * @brief Obtem um valor do hashmap
 * 
 * @param hashmap 
 * @param key 
 * @return hashmap_item_t
 */
hashmap_item_t* hashmap_get(hashmap_t* hashmap, const void* key);

#endif
