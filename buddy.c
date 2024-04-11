/**
 * Implementation of a memory allocator based on the Buddy System.
 */
 
#include "buddy.h"


static size_t ceiling_log(size_t size)
{
    size_t lgsize = 0;
    size=size-1;
    while(size>0){
        size=size>>1;
        lgsize++;
    }
    return lgsize;
}
static void insert(struct block_header * head,struct block_header * node)
{
    head->next->prev = node;
    node->next = head->next;
    head->next = node;
    node->prev = head;
}
static void delete(struct block_header * node)
{
    node->next->prev = node->prev;
    node->prev->next = node->next;
}

int buddy_init(void) 
{ 
    for(int i = 0; i <= max_kval; ++i)
    {
        avail[i].kval = i;
        avail[i].tag = UNUSED;
        avail[i].next = &avail[i];
        avail[i].prev = &avail[i];
    }
    base = sbrk(DEFAULT_MAX_MEM_SIZE);
    if(base == (void *)-1)
    {
        return FALSE;
    }
    struct block_header *bk = (struct block_header*)base;
    bk->kval = 29;
    bk->tag = FREE;
    bk->prev = &avail[bk->kval];
    bk->next = &avail[bk->kval];
    avail[bk->kval].next = bk;
    avail[bk->kval].prev = bk;
	return TRUE;
}

void *buddy_malloc(size_t size)
{
    size_t total = sizeof(struct block_header) + size;
    size_t k = ceiling_log(total);
    for(int index = k; index <= max_kval; ++index)
    {
        // circular doubly linked list is not empty
        if(avail[index].next != &avail[index])
        {
            // acquire a memory block in double linklist
            struct block_header *bk = avail[index].next;
            // delete bk from the linklist
            delete(bk);
            // recursively split the bk until index == k
            while(index != k)
            {
                --index;
                size_t half_size = (1ULL<<(index));
                struct block_header *bk1 = (struct block_header *)((uintptr_t)bk + half_size);
                bk1->kval = index;
                bk1->tag = FREE;
                insert(&avail[bk1->kval],bk1);      // insert bk1
            }
            bk->tag = RESERVED;
            bk->kval = k;
            bk->next = NULL;
            bk->prev = NULL;
            return (void*)((char*)bk + sizeof(struct block_header));
        }
    }
	return NULL;
}

void buddy_free(void *ptr) 
{
    if(ptr == NULL)
        return;
    struct block_header *bk = (struct block_header *)((char*)ptr - sizeof(struct block_header));
    bk->tag = FREE;
    while(1)
    {
        struct block_header *buddy = (struct block_header *)((uintptr_t)bk ^ (1ULL<<(bk->kval)));
        if(buddy->tag == RESERVED) 
            break;
        else{
            // 选择起始地址较小的块作为合并后的块
            struct block_header *merged_block = (bk < buddy) ? bk : buddy; 
            merged_block->kval++; 
            bk = merged_block;
            delete(buddy);
        }
    }
    insert(&avail[bk->kval],bk);    // 插入释放的最后合并完成的空闲块
    return;
}

void printBuddyLists(void)
{
    size_t cnt = 0;
    for(int i = 0; i <= max_kval; ++i)
    {
        struct block_header *head = &avail[i],*bk = head;
        printf("List %d: head = %p ",i,head);
        while(1)
        {
            bk = bk->next;
            if(bk == head)
            {
                printf("--> head = %p\n",bk);
                break;
            }else{
                ++cnt;
                printf("--> [tag=%d,kval=%d,addr=%p] ",bk->tag,bk->kval,bk);
            }
        }
    }
    printf("Number of available blocks = %zd",cnt);
    return;
}

/* vim: set ts=4: */