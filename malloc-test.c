#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_REQUEST 4096
#define MAX_ITEMS 100

#define SILENT 0
#define TERSE  1
#define VERBOSE  2
#define INTERACTIVE 3

int verbosity = TERSE;

struct element {
	char *ptr;
	size_t size;
};

int main(int argc, char *argv[])
{
	int i;
	char ch;
	int count;
	unsigned long int seed;
	size_t size;
	struct element x[MAX_ITEMS];
	int loc;

	if (argc < 2) {
		fprintf(stderr, "Usage: %s <num of tests> [random seed] [silent|terse|verbose|interactive]\n", argv[0]);
		exit(1);
	}
	count = atol(argv[1]);
	if (argc == 3) {
		seed = atol(argv[2]);
		srand(seed);
	}
	if (argc == 4) {
		if (argv[3][0] == 's') {
			verbosity = SILENT;
		} else if (argv[3][0] == 't') {
			verbosity = TERSE;
		} else if (argv[3][0] == 'v') {
			verbosity = VERBOSE;
		} else if (argv[3][0] == 'i') {
			verbosity = INTERACTIVE;
			setvbuf(stdin, NULL, _IONBF, 0);
		}
	}
	if (verbosity > TERSE)
	{
		int system_ret = system("clear");
		if(system_ret == -1) {
			perror("system call failed\n");
		}
	}

	for (i = 0; i < MAX_ITEMS; i++) {
		x[i].ptr = NULL;
		x[i].size = 0;
	}
	
	for (i=0; i < count; i++) {
		loc = rand() % MAX_ITEMS; // where to put in our table
		if (x[loc].ptr) {
			free(x[loc].ptr);
			if (verbosity > SILENT) 
				printf("freed address %p of size %lu  in x[%d]\n", x[loc].ptr, x[loc].size, loc);
			x[loc].ptr = NULL;
			x[loc].size = 0;
		} else {
			size = rand() % MAX_REQUEST + 1; // how big a request
			x[loc].ptr = (char *) malloc(size*sizeof(char));
			if (x[loc].ptr == NULL) {
				perror("TestMalloc:");
				exit(1);
			}
			x[loc].size = size*sizeof(char);
			memset(x[loc].ptr, '1', x[loc].size);
			if (verbosity > SILENT)
				printf("malloced %zd bytes and stored address %p at x[%d]\n", size*sizeof(char), x[loc].ptr, loc);
		}
		
		if (verbosity == INTERACTIVE) {
			ch = getchar();
			int system_ret = system("clear");
			if(system_ret == -1) {
				perror("system call failed\n");
			}
			if (ch == 'q')
				exit(0); 
		}
		
	}
	
	for (i = 0; i < MAX_ITEMS; i++) {
        if (x[i].ptr) 
			free(x[i].ptr);
    }
	exit(0);	
}