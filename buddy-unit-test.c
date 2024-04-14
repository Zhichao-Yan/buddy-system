#include <stdio.h>
#include <stdlib.h>
#include "buddy.h"

#define MAX_REQUEST 4096
#define MAX_ITEMS 100

#define SILENT 0
#define TERSE  1
#define VERBOSE  2
#define INTERACTIVE 3


int verbosity = TERSE;

static void 
printAndClear(void)
{
	printBuddyLists();
	char ch = getchar();
	int system_ret = system("clear");
	if(system_ret == -1) {
		perror("system call failed\n");
	}
	if (ch == 'q')
		exit(0);
}

void simpleFreeTest(void)
{
	char *x;
	
	// buddy_malloc one byte to make buddy system
	// split all the way down
	x = (char *) buddy_malloc(sizeof(char));
	if (x == NULL) {
		fprintf(stderr,"ERROR! Buddy system failed to allocate 1 byte.\n");
		exit(1);
	}
	if (verbosity > 0) {
		printf("Buddy system succeeding in allocating 1 byte.\n");
	}
	if (verbosity > 1) {
		printf("Buddy system lists after malloc'ing 1 byte.\n");
		printAndClear();
	}

	// buddy_free should make all the blocks merge back into one block
	buddy_free(x);
	if (verbosity > 0) {
		printf("Buddy system succeeding in free'ing 1 byte.\n");
	}
	if (verbosity > 1) {
		printf("Buddy system lists after free'ing the 1 byte.\n");
		printAndClear();
	}
}

void notsimpleFreeTest(void)
{
        char *x;
        char *y;

        // buddy_malloc one byte
        x = (char *) buddy_malloc(sizeof(char));
        if (x == NULL) {
                fprintf(stderr,"ERROR! Buddy system failed to allocate 1 byte.\n");
                exit(1);
        }
        if (verbosity > 0) {
                printf("Buddy system succeeding in allocating 1 byte.\n");
        }
        if (verbosity > 1) {
                printf("Buddy system lists after malloc'ing 1 byte.\n");
                printAndClear();
        }

        // buddy_malloc two bytes
        y = (char *) buddy_malloc(2 * sizeof(char));
        if (y == NULL) {
                fprintf(stderr,"ERROR! Buddy system failed to allocate 2 bytes.\n");
                exit(1);
        }
        if (verbosity > 0) {
                printf("Buddy system succeeding in allocating 2 bytes.\n");
        }
        if (verbosity > 1) {
                printf("Buddy system lists after malloc'ing 2 bytes.\n");
                printAndClear();
        }

	/* free the one byte */
        buddy_free(x);
        if (verbosity > 0) {
                printf("Buddy system succeeding in free'ing 1 byte.\n");
        }
        if (verbosity > 1) {
                printf("Buddy system lists after free'ing 1 byte.\n");
                printAndClear();
        }

	/* free the two bytes */
        buddy_free(y);
        if (verbosity > 0) {
                printf("Buddy system succeeding in free'ing 2 bytes.\n");
        }
        if (verbosity > 1) {
                printf("Buddy system lists after free'ing 2 bytes.\n");
                printAndClear();
        }
}

void maxAllocationTest(void)
{
	void *ptr;
	size_t count;
	
	//buddy_malloc larger and larger blocks until memory is exhausted
	count = 1;
	for (;;) {
		ptr = buddy_malloc(count);
		if (ptr == NULL) {
			if (verbosity > 0) 
				printf("ERROR! buddy_malloc failed to allocate a block of size %lu\n", count);
			if (verbosity > 1) printAndClear();
			return;
		} else {
			if (verbosity > 0) 
				printf("buddy_malloc'd a block of size %lu\n", count);
			if (verbosity > 1) printAndClear();
		}
		count = count * 10;
	}	
}

int main(int argc, char *argv[])
{
	if (argc < 2) {
		fprintf(stderr, "Usage: %s {silent|terse|verbose|interactive}\n", argv[0]);
		exit(1);
	}
	if (argv[1][0] == 's') {
		verbosity = SILENT;
	} else if (argv[1][0] == 't') {
		verbosity = TERSE;
	} else if (argv[1][0] == 'v') {
		verbosity = VERBOSE;
	} else if (argv[1][0] == 'i') {
		verbosity = INTERACTIVE;
		setvbuf(stdin, NULL, _IONBF, 0);
	}
	 
	int system_ret = system("clear");
	if(system_ret == -1) {
		perror("system call failed\n");
	}

	buddy_init();	
	if (verbosity > 0) {
		printf("Buddy system initialized.\n");
	}
	if (verbosity > 1) {
		printf("Buddy system lists after initialization.\n");
		printAndClear();
	}
	
	simpleFreeTest();

	notsimpleFreeTest();
	
	maxAllocationTest();
	

	buddy_shutdown();
	exit(0);	
}