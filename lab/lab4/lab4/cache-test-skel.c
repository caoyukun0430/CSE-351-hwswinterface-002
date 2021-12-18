/*
CSE 351 Lab 4, Part 1 - Mystery Caches
*/

#include <stdlib.h>
#include <stdio.h>

#include "support/mystery-cache.h"

/*
 * NOTE: When using access_cache() you do not need to provide a "real" memory
 * addresses. You can use any convenient integer value as a memory address,
 * you should not be able to cause a segmentation fault by providing a memory
 * address out of your programs address space as the argument to access_cache.
 */

/*
   Returns the size (in B) of each block in the cache.
*/
// Yukun: refer https://blog.csdn.net/fang92/article/details/46446467
int get_block_size(void) {
  int start_addr = 0;
  flush_cache();
  // first access location 0 to store into cache.
  access_cache(start_addr);
  // keeping hit until the next block
  while(access_cache(start_addr)){
    start_addr++;
  }
  return start_addr;
}

/*
   Returns the size (in B) of the cache.
*/
int get_cache_size(int block_size) {
  int num_of_blocks = 1;
  int start_addr = 0;
  // loop over all blocks 1st byte until addr 0 is overwritten
  while (1){
    for (int i = 0; i < num_of_blocks; i++){
      access_cache(i*block_size);
    }
      if (!access_cache(start_addr)) {
        return (num_of_blocks - 1) * block_size;
      }
      num_of_blocks++;
  }
}

/*
   Returns the associativity of the cache.
*/
int get_cache_assoc(int cache_size) {
  /* always write to addr 0's set, 0, cache_size, 2*cache_size,...
     until addr 0 is overwritten */
  int start_addr = 0;
  int assoc = 1;
  while (1){
    for (int i = 0; i < assoc; i++){
      access_cache(i*cache_size);
    }
      if (!access_cache(start_addr)) {
        return (assoc - 1);
      }
      assoc++;
  }
}

int main(void) {
  int size;
  int assoc;
  int block_size;

  cache_init(0, 0);

  block_size = get_block_size();
  size = get_cache_size(block_size);
  assoc = get_cache_assoc(size);

  printf("Cache block size: %d bytes\n", block_size);
  printf("Cache size: %d bytes\n", size);
  printf("Cache associativity: %d\n", assoc);

  return EXIT_SUCCESS;
}
