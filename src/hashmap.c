#include "hashmap.h"
#include <errno.h>

// implemente hash functions aqui para uso no hashmap_hash

size_t _modulo_hash(const hashmap_t* hashmap, const void* value) {
  size_t hash = *(size_t*)value % hashmap->size;
  return hash;
}

////////////

size_t hashmap_hash(hashmap_t* hashmap, const void* key, size_t (*hashkeyfunc)(const hashmap_t*, const void*)) {
  if (hashkeyfunc == NULL) {
    hashkeyfunc = _modulo_hash;
  }

  return hashkeyfunc(hashmap, key);
}

bool hashmap_set(hashmap_t* hashmap, void* key, void* value) {
  hashmap_item_t* item = hashmap_get(hashmap, key);
  
  if (item != NULL) {
    item->value = value;
  } else {
    hashmap_item_t* newitems = (hashmap_item_t*)realloc(hashmap->items, (hashmap->size + 1) * sizeof(hashmap_item_t));
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

    hashmap->size++;
  }

  return true;
}

hashmap_item_t* hashmap_get(hashmap_t* hashmap, const void* key) {
  if (hashmap->size == 0) {
    return NULL;
  }

  size_t hash = hashmap_hash(hashmap, key, _modulo_hash);

  if (hashmap->items[hash].state != HASHMAP_OCCUPIED) {
    return NULL;
  }
  
  return hashmap->items + hash;
}
