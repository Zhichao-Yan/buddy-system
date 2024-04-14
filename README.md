## Project: buddy system allocator

* Author: zhichao-yan
* Class: CS452/CS552 [Operating Systems] 

## Overview

This is allocator with buddy memory allocation algorithm.

## Manifest

* buddy.c: source file
* buddy.h: head file 
* buddy-unit-test.c: for unit test
* buddy-test.c: for test in order to compare with malloc/free allocator as blow
* malloc-test.c: malloc/free test


## Building the project

1. `make`
2. `export LD_LIBRARY_PATH = .`
3. `./buddy-test 100 1234 s`or `./buddy-unit-test s`


## Testing
1. buddy unit test(Malloc and free 1 byte)
`./buddy-unit-test v`
2. Stability test: run successfully without crashing 
`./buddy-test 20000000 1234 s`
3. Performance: better than malloc/free allocator
```sh
root@iZbp19rh4d6jcag5epp4hrZ:~/buddy-system# time ./buddy-test 20000000 1234 s

real    0m1.149s
user    0m1.147s
sys     0m0.000s
root@iZbp19rh4d6jcag5epp4hrZ:~/buddy-system# time ./malloc-test 20000000 1234 s  

real    0m1.782s
user    0m1.780s
sys     0m0.000s
```

## Known Bugs
bug all fixed.
1. need to notice the conditions when the buddy is mergeable.**buddy must be free and in the same block size**

2. sbrk() function cannot give you an aligned address,in this case,you cannot use below way to find corresponding buddy,you need to do alignment by yourself or use other functions  e.g. `int posix_memalign(void **memptr, size_t alignment, size_t size);`
> your_buddy_address = your_address^(1ULL<<your_kval));


## cites
1. [github](https://github.com/jidongbsu/cs452-buddy-system)