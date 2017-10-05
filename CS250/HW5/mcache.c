#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <inttypes.h>
#include <string.h>

#define MEMORY 4096

int main_mem[MEMORY][MEMORY];
int lru_count = 0;

void mem_create() {
  int MEMORY = 4096;
  for(int i = 0; i < MEMORY; i++) {
      for(int j = 0; j < MEMORY; j++) {
        main_mem[i][j] = 0;
      }
  }
}

int main(int argc, char *argv[]) {
  int cacheSize = atoi(argv[2]);
  int assoc = atoi(argv[3]);
  int blockSize = atoi(argv[4]);
  int num_of_blocks = cacheSize / blockSize;
  int num_of_sets = cacheSize / (blockSize * assoc);
  int cache[num_of_sets][assoc] = (int);
  for(int i = 0; i < num_of_sets; i++) {
    for(int j =  0; j < assoc; j++) {
      cache[i][j] = 0;
    }
  }
}

void cache_create(int csize, int associativity, int bsize) {
  int cache = []
}

void cache_create(int csize, int associativity, int bsize) {
  cache_sim = (CACHE*)malloc(sizeof(CACHE));
  cache_sim->cache_size = csize;
  cache_sim->block_size = bsize;
  cache_sim->set_size = associativity;
  cache_sim->num_of_blocks = cache_sim->cache_size / cache_sim->block_size;
  cache_sim->num_of_lines = cache_sim->cache_size / (cache_sim->block_size * cache_sim->set_size);
  cache_sim->cache_lines = (CACHE_LINE*) calloc(cache_sim->num_of_lines, sizeof(CACHE_LINE));
  for (int i = 0; i < cache_sim->num_of_lines; i++) {
    cache_sim[i]
  }
}








void cache_access(char* which_act, int address) {
  int index = getIndex(address);
  int tag = getTag(address);
  CACHE_LINE *curr_line = (cache_sim->cache_lines + index);
  int found = 0;
  for (int i = 0; i < cache_sim->set_size && !found; i++) {
    CACHE_BLOCK *curr_block = curr_line->cache_blocks + i;
    if (curr_block->valid == 1 && curr_block->tag == tag) {
      if (strcmp(which_act,"store") == 0) {
        curr_block->dirty = 1;
      }
      curr_block->lru = lru_count;
      found = 1;
      break;
    }
  }
  if (!found) {
    CACHE_BLOCK *mem_block;
    for (int j = 0; j < cache_sim->set_size && !found; j++) {
      CACHE_BLOCK *curr_block = curr_line->cache_blocks + j;
      if (!curr_block->valid) {
        mem_block = curr_block;
        found = 1;
        break;
      }
    }
    if (!found) {
      CACHE_BLOCK *lru_block = curr_line->cache_blocks;
      int least = lru_block->lru;
      for (int k = 0; k < cache_sim->set_size && !found; k++) {
        CACHE_BLOCK *current_block = curr_line->cache_blocks + k;
        if (current_block->lru < least) {
          lru_block = current_block;
          least = current_block->lru;
        }
      }
      mem_block = lru_block;
    }
    if (mem_block->dirty == 1) {
      mem_block->dirty = 0;
    }
    if (strcmp(which_act,"store") == 0) {
      mem_block->dirty = 1;
    }
    mem_block->valid = 1;
    mem_block->lru = lru_count;
    mem_block->tag = tag;
  }
  lru_count++;
}

















for(int j = 0; j < 16777216 && !found; j++) {
  if (address == j) {
    int memData = main_mem[j];
    CACHE_BLOCK *lru_block = curr_line->cache_blocks;
    for(int k = 0; k < cache_sim->set_size; k++) {
      CACHE_BLOCK *current_block = curr_line->cache_blocks + k;
      int least = lru_block->lru;
      if(current_block->lru < least) {
        lru_block = current_block;
        least = current_block->lru;
      }
    }
    if(lru_block->dirty == 1) {
      main_mem[j] = lru_block->data;
    }
    lru_block->data = memData;
    lru_block->data = toStore;
    lru_block->dirty = 1;
    lru_block->lru = lru_count;
    found = 1;
    printf("store 0x%06x miss\n", address);
    break;
  }
}


for(int j = 0; j < 16777216 && !found; j++) {
  if (address == j) {
    int memData = main_mem[j];
    CACHE_BLOCK *lru_block = curr_line->cache_blocks;
    for(int k = 0; k < cache_sim->set_size; k++) {
      CACHE_BLOCK *current_block = curr_line->cache_blocks + k;
      int least = lru_block->lru;
      if(current_block->lru < least) {
        lru_block = current_block;
        least = current_block->lru;
      }
    }
    if(lru_block->dirty == 1) {
      main_mem[j] = lru_block->data;
    }
    lru_block->data = memData;
    lru_block->dirty = 0;
    lru_block->lru = lru_count;
    found = 1;
    printf("load 0x%06x miss %x\n", address, lru_block->data);
  }
}
}
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
      char byte[2];
      for(int j = 0; j < toGet; j=j+2) {
        curr_block->data[temp] = sprintf(byte, "%c %c", store[j], store[j+1]);
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
    int area = (int)(address / n);
    int begin = area * n;
    char memData[n];
    int z = 0;
    for (int l = begin; l < begin + y && l < 16777216; l++) {
      memData[z] = main_mem[l];
      if(lru_block->dirty == 1) {
        main_mem[l] = lru_block->data[z];
      }
      z++;
    }
    for(int m = 0; m < y; m++) {
      lru_block->data[m] = memData[m];
    }
    int temp2 = bOff;
    char bytez[2];
    for(int n = 0; n < toGet; n=n+2) {
      lru_block->data[temp2] = sprintf(bytez, "%c %c", store[n], store[n+1]);
      temp++;
    }
    lru_block->tag = tag;
    lru_block->dirty = 1;
    lru_block->valid = 1;
    lru_block->lru = lru_count;
    found = 1;
    printf("store 0x%06x miss\n", address);
  }
  lru_count++;
}














int y = sizeof(lru_block->data) / sizeof(lru_block->data[0]);
char memData[y];
int z = 0;
for (int l = address; l < address + y && l < 16777216; l++) {
  memData[z] = main_mem[l];
}
if(lru_block->dirty == 1) {
    for (int l = 0; l < y; l++) {
      lru_block->data[]
    }
}
//    int y = sizeof(lru_block->data) / sizeof(lru_block->data[0]);
//    int area = (int)(address / y);
//    int begin = area * y;
//    char memData[y];
//    int z = 0;
//    for (int l = begin; l < begin + y && l < 16777216; l++) {
//      memData[z] = main_mem[l];
//      if(lru_block->dirty == 1) {
//        main_mem[l] = lru_block->data[z];
//      }
//      z++;
//    }

for(int m = 0; m < y; m++) {
  lru_block->data[m] = memData[m];
}
int temp2 = bOff;
char bytez[2];
for(int n = 0; n < toGet; n=n+2) {
  lru_block->data[temp2] = sprintf(bytez, "%c %c", store[n], store[n+1]);
  temp2++;
}
lru_block->tag = tag;
lru_block->dirty = 1;
lru_block->valid = 1;
lru_block->lru = lru_count;
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
      char byte[size_access];
      for (int j = 0; j < size_access; j=j+2) {
        byte[j] = curr_block->data[temp];
        temp++;
      }
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
    int area = (int)(address / y);
    int begin = area * y;
    char memData[y];
    int z = 0;
    for (int l = begin; l < begin + y && l < 16777216; l++) {
      memData[z] = main_mem[l];
      if(lru_block->dirty == 1) {
        main_mem[l] = lru_block->data[z];
      }
      z++;
    }
    for (int m = 0; m < y; m++) {
      lru_block->data[m] = memData[m];
    }
    lru_block->dirty = 0;
    lru_block->lru = lru_count;
    found = 1;
    int temp2 = bOff;
    char bytez[size_access];
    for (int n = 0; n < size_access; n=n+2) {
      bytez[n] = lru_block->data[temp2];
      temp2++;
    }
    printf("load 0x%06x miss %s\n", address, bytez);
  }
  lru_count++;
}


int getTag(int address) {
  int indexSize = getIndex(address);
  int bOSize = getBlockOffset(address);
  int toReturn = 24 - (indexSize + bOSize);
  return toReturn;
}
