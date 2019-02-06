CC := gcc
PARAMS := -std=c99 -Wall -Werror -pedantic

ifeq ($(mode), debug)
	PARAMS += -g3
endif
ifeq ($(mode), release)
	PARAMS += -DNDEBUG -g0
endif
ifeq ($(mode), drmemory)
	PARAMS += -ggdb
endif

app.exe: io.o reverse.o allocate.o operations.o main.o
	$(CC) -o $@ $^
	
test.exe: io.o reverse.o allocate.o operations.o test.o
	$(CC) -o $@ $^
	
main.o: main.c io.h defines.h operations.h allocate.h
	$(CC) $(PARAMS) -c $<
	
test.o: test.c io.h defines.h operations.h allocate.h
	$(CC) $(PARAMS) -c $<
	
io.o: io.c io.h defines.h allocate.h
	$(CC) $(PARAMS) -c $<
	
reverse.o: reverse.c reverse.h
	$(CC) $(PARAMS) -c $<
	
allocate.o: allocate.c allocate.h
	$(CC) $(PARAMS) -c $<

operations.o: operations.c operations.h defines.h allocate.h
	$(CC) $(PARAMS) -c $<
	
clean:
	rm *.o *.exe