#include <stdio.h>
#include <stdlib.h>


int buddy_init(void);
void *buddy_malloc(size_t size);
void buddy_free(void *ptr);
void printBuddyLists(void);


int main()
{
    buddy_init();
    int *a = (int*)buddy_malloc(sizeof(int));
    printBuddyLists();
    if(a == NULL)
        return 0;
    *a = 100;
    printf("number:%d\n",*a);
    buddy_free(a);
    return 0;
}