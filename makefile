CC:=gcc
AR:=ar
LD:=ld
CFLAGS=-fPIC -g -O2 -std=c99 -Wall -MMD 
LDFLAGS:=-shared
LIB:=-L. -lbuddy
OBJ:=buddy.o

all: libbuddy.so libbuddy.a buddy-test malloc-test buddy-unit-test

$(OBJ): buddy.c
	$(CC) $(CFLAGS) -c $^ -o $@ 

libbuddy.so: $(OBJ)
	$(LD) $(LDFLAGS) $^ -o $@ 

libbuddy.a: $(OBJ)
	$(AR)  -rcv $@ $(OBJ)

buddy-unit-test: buddy-unit-test.c
	$(CC) $(CFLAGS) $^ $(LIB) -o $@ 

buddy-test: buddy-test.c
	$(CC) $(CFLAGS) $^ $(LIB) -o $@ 

malloc-test: malloc-test.c
	$(CC) $(CFLAGS) $^ $(LIB) -o $@ 

clean:	
	rm -f *.o *.d buddy-test malloc-test libbuddy.* buddy-unit-test