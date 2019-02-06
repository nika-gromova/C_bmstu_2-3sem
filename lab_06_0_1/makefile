CC := gcc
PARAMS := -std=c99 -Wall -Werror
OBJ := io.o get_max.o

ifeq ($(mode), debug)
    PARAMS += -g3
endif
ifeq ($(mode), release)
    PARAMS += -DNDEBUG -g0
endif

get_max_sum.exe : io.o get_max.o main.o
	$(CC) $(PARAMS) -o $@ $^
io.o : io.c
	$(CC) $(PARAMS) -c $<
get_max.o : get_max.c
	$(CC) $(PARAMS) -c $<
main.o : main.c
	$(CC) $(PARAMS) -c $<
clean :
	rm *.o *.exe
