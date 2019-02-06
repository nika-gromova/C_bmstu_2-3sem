OBJ := io.o get_max.o
CC := gcc
PARAMS := -std=c99 -Wall -Werror

ifeq ($(mode), debug)
    PARAMS += -g3
endif
ifeq ($(mode), release)
    PARAMS += -DNDEBUG -g0
endif

get_max_sum.exe : $(OBJ) main.o
	$(CC) -o $@ $^
io.o : io.c io.h
	$(CC) $(PARAMS) -c $<
get_max.o : get_max.c get_max.h
	$(CC) $(PARAMS) -c $<
main.o : main.c io.h get_max.h
	$(CC) $(PARAMS) -c $<
clean :
	rm *.o *.exe
