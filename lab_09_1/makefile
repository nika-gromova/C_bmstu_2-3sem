CC := gcc
PARAMS := -std=c99 -Wall -Werror -pedantic

ifeq ($(mode), debug)
	PARAMS += -g3
endif

test.exe: test.o process.o
	$(CC) -o $@ $^

test.o: test.c process.h
	$(CC) $(PARAMS) -c $<

process.o: process.c process.h
	$(CC) $(PARAMS) -c $<
	
clean:
	rm *.o *.exe