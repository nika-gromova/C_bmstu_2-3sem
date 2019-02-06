CC := gcc
PARAMS := -std=c99 -Wall -Werror -pedantic -ggdb

ifeq ($(mode), debug)
	PARAMS += -g3
endif
ifeq ($(mode), release)
	PARAMS += -DNDEBUG -g0
endif
ifeq ($(mode), drmemory)
	PARAMS += -ggdb
endif

main.exe: sort.o main.o
	$(CC) -o $@ $^

main.o: main.c sort.h
	$(CC) $(PARAMS) -c $<
	
sort.o: sort.c sort.h
	$(CC) $(PARAMS) -c $<
	
clean:
	rm *.o *.exe q_sort.txt my_sort.txt