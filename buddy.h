#ifndef BUDDY_H_
#define BUDDY_H_

#define _XOPEN_SOURCE 600
#include <stdio.h>	/* for printf() */
#include <unistd.h>	/* for sbrk() */
#include <stdint.h>
#include <stdlib.h>


#define TRUE 1
#define FALSE 0

/* the header for an available block */
struct block_header {
    short tag;
    short kval;
    struct block_header *next;
    struct block_header *prev;
};

/**
 * Initialize the buddy system to the default size 
 *
 * @return  TRUE if successful, FALSE otherwise.
 */
int buddy_init(void);

/**
 * Allocate dynamic memory. Rounds up the requested size to next power of two.
 * Returns a pointer that should be type casted as needed.
 * @param size  The amount of memory requested
 * @return Pointer to new block of memory of the specified size.
 */
void *buddy_malloc(size_t size);

/**
 * buddy_free() frees the memory space pointed to by ptr, which must have been returned 
 * by a previous call to buddy_malloc(), buddy_calloc() or buddy_realloc(). Otherwise, 
 * or if buddy_free(ptr) has already been called before, undefined behaviour occurs. If 
 * ptr is NULL, no operation is performed. 
 * @param ptr Pointer to memory block to be freed
 */
void buddy_free(void *ptr);

/**
 * Prints out all the lists of available blocks in the Buddy system.
 */
void printBuddyLists(void);

void buddy_shutdown(void);

#endif /*BUDDY_H_*/