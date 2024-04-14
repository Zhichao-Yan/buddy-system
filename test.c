#include <stdio.h>
#include <stdlib.h>
#include "buddy.h"


int main()
{
    buddy_init();
    printBuddyLists();
    size_t size = 876;
    void *a = buddy_malloc(size*sizeof(char));
    printBuddyLists();
    if(a == NULL)
        return 0;
    buddy_free(a);
    printBuddyLists();
    buddy_shutdown();
    return 0;
}