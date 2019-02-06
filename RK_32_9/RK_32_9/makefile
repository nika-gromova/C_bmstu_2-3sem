CC := gcc
PARAMS := -std=c99 -Wall -Werror -pedantic

ifeq ($(mode), debug)
	PARAMS += -g3
endif
ifeq ($(mode), drmemory)
	PARAMS += -ggdb
endif

app.exe: main.o list.o
	$(CC) -o $@ $^
	
test.exe: test.o list.o
	$(CC) -o $@ $^
	
main.o: main.c my_struct.h list.h
	$(CC) $(PARAMS) -c $<
	
test.o: test.c my_struct.h list.h
	$(CC) $(PARAMS) -c $<
	
list.o: list.c my_struct.h list.h
	$(CC) $(PARAMS) -c $<
	
clean:
	rm *.o *.exe