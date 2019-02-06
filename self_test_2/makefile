CC := gcc
FLAGS := -std=c99 -Wall -Werror
OBJ := io.o process.o

ifeq ($(mode), debug)
	PARAMS += -g3
endif
ifeq ($(mode), release)
	PARAMS += -DNDEBUG -g0
endif

self_test_2.exe: $(OBJ) main.o
	$(CC) -o $@ $^
	
io.o: io.c io.h defines.h
	$(CC) $(FLAGS) -c $<

process.o: process.c defines.h process.h
	$(CC) $(FLAGS) -c $<
	
main.o: main.c io.h defines.h
	$(CC) $(FLAGS) -c $<

clean:
	rm *.o *.exe