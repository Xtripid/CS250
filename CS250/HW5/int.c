#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <inttypes.h>
#include <string.h>

typedef struct cache_block {
  int tag;
  int lru;
  int valid;
  int dirty;
  char *data;
} CACHE_BLOCK;

typedef struct {
  CACHE_BLOCK *cache_blocks;
} CACHE_LINE;

typedef struct cache {
  int cache_size;
  int set_size;
  int block_size;
  int num_of_blocks;
  int num_of_lines;
  CACHE_LINE *cache_lines;
} CACHE;

CACHE *cache_sim;
int lru_count = 0;
char main_mem[16777216];

void mem_create() {
  for(int i = 0; i < 16777216; i++) {
    main_mem[i] = '0';
  }
}

void cache_create(int csize, int associativity, int bsize) {
  cache_sim = (CACHE*)malloc(sizeof(CACHE));
  cache_sim->cache_size = csize * 1024;
  cache_sim->block_size = bsize;
  cache_sim->set_size = associativity;
  cache_sim->num_of_blocks = cache_sim->cache_size / cache_sim->block_size;
  cache_sim->num_of_lines = cache_sim->cache_size / (cache_sim->block_size * cache_sim->set_size);
  cache_sim->cache_lines = (CACHE_LINE*) malloc(cache_sim->num_of_lines * sizeof(CACHE_LINE));
  for (int i = 0; i < cache_sim->num_of_lines; i++) {
    CACHE_LINE *curr_line = (cache_sim->cache_lines + i);
    curr_line->cache_blocks = (CACHE_BLOCK*) malloc(cache_sim->set_size * sizeof(CACHE_BLOCK));
    for(int j = 0; j < cache_sim->set_size; j++) {
      CACHE_BLOCK *curr_block = curr_line->cache_blocks + j;
      curr_block->data = (char*)malloc((sizeof(char) + sizeof(char)) * cache_sim->block_size);
    }
  }
}

int getIndex(int address) {
  int num_of_sets = (cache_sim->cache_size)/((cache_sim->block_size)*(cache_sim->set_size));
  int index_bits = (int)log2(num_of_sets);
//  if(index_bits == 0) {
//    index_bits = 1;
//  }
  return index_bits;
}
int getBlockOffset(int address) {
  return (int)log2(cache_sim->block_size);
}

void cache_store(int address, int size_access, char *store) {
  int a = pow(2,getBlockOffset(address))-1;
  int b = pow(2,getIndex(address))-1;
  int c = getBlockOffset(address);
  int index = (address >> c) & b;
  int bOff = address & a;
  int tag = (address >> getBlockOffset(address)) >> getIndex(address);
  int toGet = size_access * 2;
  CACHE_LINE *curr_line = (cache_sim->cache_lines + index);
  int found = 0;
  for (int i = 0; i < cache_sim->set_size && !found; i++) {
    CACHE_BLOCK *curr_block = curr_line->cache_blocks + i;
    if (curr_block->valid == 1 && curr_block->tag == tag) {
      int temp = bOff;
      for(int j = 0; j < toGet; j=j+2) {
        char twoBytes = (store[j] << 2) | store[j+1];
        printf("%s\n", twoBytes);
        curr_block->data[temp] = twoBytes;
        temp++;
      }
      curr_block->dirty = 1;
      curr_block->lru = lru_count;
      found = 1;
      printf("store 0x%06x hit\n", address);
      break;
    }
  }
  if(!found) {
    CACHE_BLOCK *lru_block = curr_line->cache_blocks;
    for(int k = 0; k < cache_sim->set_size; k++) {
      CACHE_BLOCK *current_block = curr_line->cache_blocks + k;
      int least = lru_block->lru;
      if(current_block->lru < least) {
        lru_block = current_block;
        least = current_block->lru;
      }
    }
    int y = sizeof(lru_block->data) / sizeof(lru_block->data[0]);
    int z = 0;
    if(lru_block->dirty == 1) {
      int placeInMem = (address >> getBlockOffset(address));
      for(int l = placeInMem; l < placeInMem + y; l++) {
        main_mem[l] = lru_block->data[z];
        z++;
      }
    }
    int x = 0;
    for(int m = address; m < address + y; m++) {
      lru_block->data[x] = main_mem[m];
      x++;
    }
    int temp = bOff;
    for(int j = 0; j < toGet; j=j+2) {
      char twoBytes = (store[j] << 4) | store[j+1];
      lru_block->data[temp] = twoBytes;
      temp++;
    }
    lru_block->dirty = 1;
    lru_block->valid = 1;
    lru_block->lru = lru_count;
    lru_block->tag = tag;
    found = 1;
    printf("store 0x%06x miss\n", address);
  }
  lru_count++;
}

void cache_load(int address, int size_access) {
  int a = pow(2,getBlockOffset(address))-1;
  int b = pow(2,getIndex(address))-1;
  int c = getBlockOffset(address);
  int index = (address >> c) & b;
  int bOff = address & a;
  int tag = (address >> getBlockOffset(address)) >> getIndex(address);
  int toGet = size_access * 2;
  CACHE_LINE *curr_line = (cache_sim->cache_lines + index);
  int found = 0;
  for (int i = 0; i < cache_sim->set_size && !found; i++) {
    CACHE_BLOCK *curr_block = curr_line->cache_blocks + i;
    if (curr_block->valid == 1 && curr_block->tag == tag) {
      int temp = bOff;
      char byte[size_access + 1];
      memcpy(byte, curr_block->data + temp, size_access);
      byte[size_access] = '\0';
      //for (int j = 0; j < size_access; j++) {
      //  strcat(byte, curr_block->data[temp]);
      //  temp++;
      //}
      found = 1;
      curr_block->lru = lru_count;
      printf("load 0x%06x hit %s\n", address, byte);
      break;
    }
  }
  if(!found) {
    CACHE_BLOCK *lru_block = curr_line->cache_blocks;
    for(int k = 0; k < cache_sim->set_size; k++) {
      CACHE_BLOCK *current_block = curr_line->cache_blocks + k;
      int least = lru_block->lru;
      if(current_block->lru < least) {
        lru_block = current_block;
        least = current_block->lru;
      }
    }
    int y = sizeof(lru_block->data) / sizeof(lru_block->data[0]);
    int z = 0;
    if(lru_block->dirty == 1) {
      int placeInMem = (address >> getBlockOffset(address));
      for(int l = placeInMem; l < placeInMem + y; l++) {
        main_mem[l] = lru_block->data[z];
        z++;
      }
    }
    int x = 0;
    for(int m = address; m < address + y; m++) {
      lru_block->data[x] = main_mem[m];
      x++;
    }
    int temp = bOff;
    char byte[size_access + 1];
    memcpy(byte, lru_block->data + temp, size_access);
    byte[size_access] = '\0';
    found = 1;
    lru_block->lru = lru_count;
    lru_block->dirty = 0;
    lru_block->tag = tag;
    lru_block->valid = 1;
    printf("load 0x%06x miss %s\n", address, byte);
  }
}

int main(int argc, char *argv[]) {
  int cacheSize = atoi(argv[2]);
  int assoc = atoi(argv[3]);
  int blockSize = atoi(argv[4]);
  mem_create();
  cache_create(cacheSize, assoc, blockSize);
  FILE *file = fopen(argv[1], "r");
  if (file != NULL) {
    char file_line[256];
    const char s[2] = " ";
    char *token;
    while (fgets(file_line, sizeof(file_line), file) != NULL) {
      token = strtok(file_line, s);
      int num = 0;
      char *action;
      char *address;
      char *aSize;
      char *val;
      while (token != NULL) {
        if (num == 0) {
          action = token;
        }
        else if (num == 1) {
          address = token;
        }
        else if (num == 2) {
          aSize = token;
        }
        else if (num == 3) {
          val = token;
          char *pos;
          if((pos = strchr(val, '\n')) != NULL) {
            *pos = '\0';
          }
        }
        token = strtok(NULL, s);
        num++;
      }
      int addressInt = strtol(address, NULL, 16);
      int aSizeInt = atoi(aSize);
      if (strcmp(action, "store") == 0) {
        cache_store(addressInt, aSizeInt, val);
      }
      else if (strcmp(action, "load") == 0) {
        cache_load(addressInt, aSizeInt);
      }
    }
  }
  else {
    perror ("Error in opening file\n");
  }
}
