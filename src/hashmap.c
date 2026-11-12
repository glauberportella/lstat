#include "hashmap.h"
#include "types.h"
#include <errno.h>
#include <stdio.h>

// implemente hash functions aqui para uso no hashmap_hash

size_t _modulo_hash(const hashmap_t* hashmap, const void* value) {
  printf(">> _modulo_hash: value %zu, size: %zu\n", *(size_t*)value, hashmap->size);
  size_t hash = *(size_t*)value % hashmap->size;
  return hash;
}

////////////

hashmap_t* hashmap_init(size_t size) {
  hashmap_t* h = (hashmap_t*)malloc(sizeof(hashmap_t));
  if (h == NULL) {
    errno = EALLOCATION;
    return NULL;
  }

  h->size = size;
  h->items = (hashmap_item_t*)calloc(size, sizeof(hashmap_item_t));
  
  return h;
}

void hashmap_destroy(hashmap_t* hashmap) {
  if (hashmap != NULL) {
    free(hashmap->items);
    hashmap->items = NULL;
  }
}

size_t hashmap_hash(hashmap_t* hashmap, const void* key, size_t (*hashkeyfunc)(const hashmap_t*, const void*)) {
  if (hashkeyfunc == NULL) {
    hashkeyfunc = _modulo_hash;
  }

  return hashkeyfunc(hashmap, (size_t*)key);
}

bool hashmap_set(hashmap_t* hashmap, void* key, void* value) {  
  hashmap_item_t* item = hashmap_get(hashmap, key);
  if (item != NULL) {
    item->value = value;
  } else {
    hashmap_item_t* newitems = (hashmap_item_t*)realloc(hashmap->items, (++hashmap->size) * sizeof(hashmap_item_t));
    if (newitems == NULL) {
      errno = EHASHMAPALLOCATION;
      return false;
    }
    hashmap->items = newitems;

    size_t hash = hashmap_hash(hashmap, key, _modulo_hash);
    hashmap->items[hash] = (hashmap_item_t){
      .hash = hash,
      .key = key,
      .value = value,
      .state = HASHMAP_OCCUPIED
    };
  }

  return true;
}

hashmap_item_t* hashmap_get(hashmap_t* hashmap, const void* key) {
  if (hashmap->size == 0) {
    return NULL;
  }

  size_t hash = hashmap_hash(hashmap, key, _modulo_hash);
  printf(">> HASH: %zu\n", hash);

  if (hashmap->items[hash].state != HASHMAP_OCCUPIED) {
    return NULL;
  }
  
  return hashmap->items + hash;
}
